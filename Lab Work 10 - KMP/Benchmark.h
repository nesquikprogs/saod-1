#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <fstream>

#include "NaiveSearch.h"
#include "KMPSearch.h"
#include "MeasureTime.h"

namespace benchmark
{

    using namespace std;
    using namespace string_search;

    #pragma region GenRandAndNutSTR

    /// <summary>
    /// Генерирует случайную строку заданной длины из указанного алфавита.
    /// Big-O: O(length), где length — длина строки.
    /// Big-O память: O(length), где length — длина строки.
    /// </summary>
    /// <param name="length">Длина генерируемой строки</param>
    /// <param name="alphabet">Набор допустимых символов</param>
    /// <returns>Случайная строка длины length</returns>
    inline string generate_random_string(size_t length, const string& alphabet)
    {
        // Источник случайности
        static random_device rd;
        static mt19937 gen(rd());

        // Равномерно выбираем индекс символа в алфавите
        uniform_int_distribution<size_t> dist(0, alphabet.size() - 1); // равномерно по целым
        string s; 
        s.reserve(length); // резервируем память под length
        for (size_t i = 0; i < length; ++i)
        {
            s.push_back(alphabet[dist(gen)]); // добавляем в строку символ текста с случайносгенерированным индексом
        }
        return s;
    }

    /// <summary>
    /// Генерирует текст, похожий на естественный язык, путём повторения базовой фразы.
    /// Big-O: O(length), где length — длина текста.
    /// Big-O память: O(length), где length — длина текста.
    /// </summary>
    /// <param name="length">Желаемая длина текста</param>
    /// <returns>Строка не меньше указанной длины, усечённая до length</returns>
    inline string generate_natural_text(size_t length)
    {
        // Базовый фрагмент, который повторяется до достижения нужной длины
        const string base =
            "I want to pass all my assignments and successfully defend my diploma. "
            "I will do whatever it takes. ";

        string result;
        result.reserve(length);
        while (result.size() < length)
        {
            // Добавляем ещё один фрагмент, пока не наберём нужную длину
            result += base;
        }
        // Обрезаем лишние символы, если немного перебрали
        result.resize(length);
        return result;
    }

    #pragma endregion

    #pragma region AvgTimeMeasure

    /// <summary>
    /// Усреднённое измерение времени выполнения произвольной функции
    /// Big-O: O(repeats * T(func)), где repeats — число повторов, T(func) — время одного вызова func.
    /// Big-O память: O(1), кроме памяти, которую использует сама func.
    /// </summary>
    /// <typeparam name="Func">Тип вызываемого объекта</typeparam>
    /// <param name="repeats">Сколько раз повторить замер</param>
    /// <param name="func">Функция или лямбда без аргументов</param>
    /// <returns>Среднее время выполнения в микросекундах</returns>
    template<typename Func>
    long long measure_average_time_microseconds(size_t repeats, Func&& func)
    {
        // Накопление суммарного времени всех повторов
        long long total = 0;
        for (size_t i = 0; i < repeats; ++i)
        {
            // Каждый раз вызываем общий измеритель из MeasureTime.h
            total += measure_time_ms(std::forward<Func>(func));
        }
        // Возвращаем среднее значение
        return total / static_cast<long long>(repeats);
    }

    #pragma endregion

    #pragma region RandomText

    /// <summary>
    /// Измеряет время работы алгоритмов на случайных строках из алфавита a-z
    /// </summary>
    inline void measure_for_random_sequences()
    {
        cout << "Random" << endl;
        cout << "length;naive_time;kmp_time" << endl;

        // Открываем CSV-файл для результатов по случайным строкам
        ofstream file("random_results.csv");
        if (file)
        {
            // Заголовок для удобной загрузки в Excel
            file << "length;naive_time;kmp_time" << endl;
        }

        const string alphabet = "abcdefghijklmnopqrstuvwxyz";

        // Набор длин, для которых проводим замеры
        vector<size_t> lengths = { 10000, 50000, 100000, 200000, 500000, 1000000 }; // n
        const size_t pattern_length = 20; // m

        for (size_t n : lengths)
        {
            // Генерируем случайный текст и выбираем шаблон как подстроку
            string text = generate_random_string(n, alphabet);
            string pattern = text.substr(n / 2, pattern_length); 

            // Считаем префикс-функцию один раз, чтобы замер включал только поиск по text
            const auto p = compute_prefix_function(pattern);

            // Замер наивного поиска
            auto naive_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = naive_search(text, pattern);
                    (void)res;
                });

            // Замер КМП
            auto kmp_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = kmp_search_with_prefix_function(text, pattern, p);
                    (void)res;
                });

            // Дублируем результат в консоль и файл
            cout << n << ";" << naive_time << ";" << kmp_time << endl;
            if (file)
            {
                file << n << ";" << naive_time << ";" << kmp_time << endl;
            }
        }
    }

    #pragma endregion

    #pragma region NaturalTextBench

    /// <summary>
    /// Измеряет время работы алгоритмов на тексте, похожем на естественный язык
    /// </summary>
    inline void measure_for_natural_text()
    {
        cout << endl << "Natural" << endl;
        cout << "length;naive_time;kmp_time" << endl;

        // Файл с результатами для текстов естественного языка
        ofstream file("natural_results.csv");
        if (file)
        {
            file << "length;naive_time;kmp_time" << endl;
        }

        // ТДлины
        vector<size_t> lengths = { 10000, 50000, 100000, 200000, 500000, 1000000 };
        // Фиксированный шаблон-слово/фраза, который ищем в тексте
        const string pattern = "pass all my assignments";
        const auto p = compute_prefix_function(pattern);

        for (size_t n : lengths)
        {
            // Генерируем длинный естественный текст повторением базовой фразы
            string text = generate_natural_text(n);

            // Наивный поиск этого шаблона
            auto naive_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = naive_search(text, pattern);
                    (void)res;
                });

            // Поиск тем же шаблоном с помощью КМП
            auto kmp_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = kmp_search_with_prefix_function(text, pattern, p);
                    (void)res;
                });

            // Выводим длину текста и времена обоих алгоритмов
            cout << n << ";" << naive_time << ";" << kmp_time << endl;
            if (file)
            {
                file << n << ";" << naive_time << ";" << kmp_time << endl;
            }
        }
    }

    #pragma endregion

    #pragma region FourSymbolTextBench

    /// <summary>
    /// Измеряет время работы алгоритмов на случайных строках из алфавита из четырёх символов
    /// </summary>
    inline void measure_for_four_symbol_sequences()
    {
        cout << endl << "4 symbols" << endl;
        cout << "length;naive_time;kmp_time" << endl;

        ofstream file("four_symbol_results.csv");
        if (file)
        {
            file << "length;naive_time;kmp_time" << endl;
        }

        const string alphabet = "ACGT";

        // Те же длины, но другой алфавит и длина шаблона
        vector<size_t> lengths = { 10000, 50000, 100000, 200000, 500000, 1000000 };
        const size_t pattern_length = 15;

        for (size_t n : lengths)
        {
            string text = generate_random_string(n, alphabet);
            string pattern = text.substr(n / 3, pattern_length);

            const auto p = compute_prefix_function(pattern);

            // Наивный поиск шаблона
            auto naive_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = naive_search(text, pattern);
                    (void)res;
                });

            // Поиск тем же шаблоном с помощью КМП
            auto kmp_time = measure_average_time_microseconds(
                100,
                [&]()
                {
                    volatile auto res = kmp_search_with_prefix_function(text, pattern, p);
                    (void)res;
                });

            // Сохраняем результаты для построения графиков
            cout << n << ";" << naive_time << ";" << kmp_time << endl;
            if (file)
            {
                file << n << ";" << naive_time << ";" << kmp_time << endl;
            }
        }
    }

    #pragma endregion

}

