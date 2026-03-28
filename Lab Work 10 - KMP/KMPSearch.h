#pragma once

#include <vector>
#include <cstddef>

namespace string_search
{

    #pragma region KmpPrefixFunction

    /// <summary>
    /// Строит массив префикс-функции p для шаблона.
    /// Big-O: O(m), где m — длина pattern.
    /// Big-O память: O(m), где m — длина pattern.
    /// </summary>
    /// <typeparam name="Seq">Тип последовательности с операцией индексирования и size()</typeparam>
    /// <param name="pattern">Шаблон, для которого вычисляется префикс-функция</param>
    /// <returns>Вектор значений p для каждой позиции шаблона</returns>
    template<typename Seq>
    std::vector<std::size_t> compute_prefix_function(const Seq& pattern)
    {
        const std::size_t m = pattern.size(); // размер шаблона
        std::vector<std::size_t> p(m, 0); // массив префикс функции

        std::size_t i = 1; // индекс текущего элемента в шаблоне
        std::size_t j = 0; // длина текущего совпадавшего префикса/индекс элемента который сравниваем с iтым элементом

        // Строим p слева направо, начиная со второй позиции
        while (i < m)
        {
            // Если текущие символы не равны
            if (pattern[i] != pattern[j])
            {
                // Длина префкиса 0(совпадений еще не было найдено)
                if (j == 0)
                {
                    p[i] = 0;
                    ++i;
                }
                // Длина уже не 0(совпадение ранее было)
                else
                {
                    j = p[j - 1];
                }
            }
            // Иначе символы равны
            else
            {
                p[i] = j + 1;
                ++i;
                ++j;
            }
        }

        return p;
    }

    #pragma endregion

    #pragma region KmpSearch

    /// <summary>
    /// Поиск всех вхождений шаблона в последовательности с использованием заранее вычисленной префикс-функции p
    /// Big-O: O(n + m), где n — длина text, m — длина pattern.
    /// Big-O память: O(k) на результат, плюс память под p учитывается снаружи.
    /// </summary>
    /// <typeparam name="Seq">Тип последовательности с операцией индексирования и size()</typeparam>
    /// <param name="text">Последовательность, в которой ищем</param>
    /// <param name="pattern">Шаблон, который ищем</param>
    /// <param name="p">Префикс-функция для pattern (размер должен равняться pattern.size())</param>
    /// <returns>Вектор индексов начала всех вхождений</returns>
    template<typename Seq>
    std::vector<std::size_t> kmp_search_with_prefix_function(
        const Seq& text,
        const Seq& pattern,
        const std::vector<std::size_t>& p)
    {
        // Массив всех позиций(индексов) найденных вхождений
        std::vector<std::size_t> result;

        const std::size_t n = text.size(); // размер текста
        const std::size_t m = pattern.size(); // размер шаблона

        // Пустой или слишком длинный шаблон нельзя найти
        if (m == 0 || n < m)
            return result;

        // p должен соответствовать длине pattern
        if (p.size() != m)
            return result;

        std::size_t k = 0; // индекс в тексте
        std::size_t l = 0; // индекс в шаблоне

        while (k < n)
        {
            // Если из текста и образа совпадают элементы
            if (text[k] == pattern[l])
            {
                // Переходим дальше по символам
                ++k;
                ++l;
            }

            // Если дошли до конца шаблона, найдено полное вхождение
            if (l == m)
            {
                result.push_back(k - l);
                // Продолжаем поиск, используя информацию из p
                l = p[l - 1];
            }
            // Несовпадение после нескольких совпавших символов
            else if (k < n && text[k] != pattern[l])
            {
                // l - индекс НЕ самого левого элемента
                if (l != 0)
                {
                    // Откатываемся по шаблону без возврата по тексту
                    l = p[l - 1];
                }
                else
                {
                    // Совпадений ещё не было, просто двигаемся по тексту
                    ++k;
                }
            }
        }

        // Возвращаем все найденные позиции
        return result;
    }

    /// <summary>
    /// Поиск всех вхождений шаблона в последовательности с помощью алгоритма Кнута–Морриса–Пратта
    /// Big-O: O(n + m), где n — длина text, m — длина pattern.
    /// Big-O память: O(m + k), где m — длина pattern, k — число найденных вхождений.
    /// </summary>
    /// <typeparam name="Seq">Тип последовательности с операцией индексирования и size()</typeparam>
    /// <param name="text">Последовательность, в которой ищем</param>
    /// <param name="pattern">Шаблон, который ищем</param>
    /// <returns>Вектор индексов начала всех вхождений</returns>
    template<typename Seq>
    std::vector<std::size_t> kmp_search(const Seq& text, const Seq& pattern)
    {
        // Массив всех позиций(индексов) найденных вхождений
        std::vector<std::size_t> result;

        const std::size_t n = text.size(); // размер текста
        const std::size_t m = pattern.size(); // размер шаблона

        // Пустой или слишком длинный шаблон нельзя найти
        if (m == 0 || n < m)
            return result;

        // Создание массива преффиекс функций для шаблона
        const auto p = compute_prefix_function(pattern);

        std::size_t k = 0; // индекс в тексте 
        std::size_t l = 0; // индекс в шаблоне

        // Основной проход по тексту
        while (k < n)
        {
            // Если из строки и образа совпадают элементы
            if (text[k] == pattern[l])
            {
                // Переходим дальше по символам 
                ++k;
                ++l;
            }

            // Если дошли до конца шаблона, найдено полное вхождение
            if (l == m)
            {
                result.push_back(k - l);
                // Продолжаем поиск, используя информацию из p
                l = p[l - 1];
            }
            // Несовпадение после нескольких совпавших символов
            else if (k < n && text[k] != pattern[l])
            {
                // l - индекс НЕ самого левого элемента
                if (l != 0)
                {
                    // Откатываемся по шаблону без возврата по тексту
                    l = p[l - 1];
                }
                // l - индекс самого левого элемента
                else
                {
                    // Совпадений ещё не было, просто двигаемся по тексту
                    ++k;
                }
            }
        }

        // Возвращаем все найденные позиции
        return result;
    }

    #pragma endregion

}

