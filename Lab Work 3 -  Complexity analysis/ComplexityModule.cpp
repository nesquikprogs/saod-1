#include "ComplexityModule.h"

#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

/// <summary>
/// Формирует текстовый ответ на основе сравнения двух счетчиков.
/// </summary>
/// <param name="greaterCount">Количество элементов, больших среднего значения</param>
/// <param name="lessCount">Количество элементов, меньших среднего значения</param>
/// <returns>Строка с итогом сравнения</returns>
string GetAnswerText(int greaterCount, int lessCount)
{
    // Если больше больших среднего
    if (greaterCount > lessCount) 
    {
        return "Элементов больше среднего больше.";
    }

    // Если меньше меньших среднего
    if (lessCount > greaterCount) 
    {
        return "Элементов меньше среднего больше.";
    }

    // Оба счетчика равны
    return "Количество элементов больше и меньше среднего одинаково.";
}

/// <summary>
/// Сравнивает количество элементов больше и меньше среднего с ранней остановкой.
/// </summary>
/// <param name="numbers">Входной список целых чисел</param>
/// <param name="avg">Среднее значение, относительно которого выполняется сравнение</param>
/// <param name="checked">Количество элементов, обработанных алгоритмом</param>
/// <returns>Строка с результатом сравнения</returns>
string Analyze(const vector<int>& numbers, double avg, int& checked)
{
    int greaterCount = 0; // количество больших среднего
    int lessCount = 0; // количество меньших среднего
    const int n = static_cast<int>(numbers.size()); // размер списка

    for (int i = 0; i < n; ++i)
    {
        if (numbers[i] > avg) // если текущий элемент больше среднего
        {
            ++greaterCount;
        }
        else if (numbers[i] < avg) // если текущий элемент меньше среднего
        {
            ++lessCount;
        }

        const int remaining = n - i - 1; // количество непросмотренных элементов
        const int diff = greaterCount - lessCount; // перевес одной группы над другой

        // Когда больше больших элементов
        if (diff > remaining) // если впереди меньше чем текущий перевес
        {
            checked = i + 1;
            return "Элементов больше среднего больше.";
        }

        // Когда больше меньших элементов
        if (-diff > remaining) // если впереди меньше чем текущий перевес
        {
            checked = i + 1;
            return "Элементов меньше среднего больше.";
        }
    }

    checked = n; // если прошлись по всему списку
    return GetAnswerText(greaterCount, lessCount); // получаем готовую строку сравнения
}

/// <summary>
/// Считывает из консоли одну строку целых чисел, разделенных пробелами.
/// </summary>
/// <returns>Вектор считанных целых чисел</returns>
vector<int> ReadNumbers()
{
    vector<int> numbers; // вектор для складывания чисел по мере чтения
    string line; // строка целеком
    getline(cin, line); // читаем из консполи всю строку
    istringstream input(line); // новый поток
    int value = 0;

    while (input >> value) // чтение из потока
    {
        numbers.push_back(value); // добавление в конец списка очередного числа
    }

    return numbers; 
}

/// <summary>
/// Выполняет тестовые примеры и сохраняет результаты в текстовый файл.
/// </summary>
/// <param name="fileName">Имя файла для сохранения результатов тестирования</param>
void RunTestsToFile(const string& fileName)
{
    // Открытие файла и проверка на открытие
    ofstream out(fileName);
    if (!out.is_open())
    {
        cout << "Не удалось открыть файл " << fileName << "\n";
        return;
    }

    // Структура тестов
    struct Test
    {
        string name;
        vector<int> numbers;
        double avg;
        string expected;
    };

    // Набор тестов
    const vector<Test> tests = {
        { "Test1 Ранний выход", { 10, 10, 10, 0, 0 }, 5, "Элементов больше среднего больше." },
        { "Test2 Худший случай ничья", { 8, 6, 8, 6, 8, 6 }, 7, "Количество элементов больше и меньше среднего одинаково." },
        { "Test3 Больше меньших", { 8, 6, 8, 6, 6, 8, 6 }, 7, "Элементов меньше среднего больше." },
        { "Test4 Есть равные среднему", { 3, 5, 5, 7 }, 5, "Количество элементов больше и меньше среднего одинаково." },
        { "Test5 Все больше", { 11, 12, 13, 14 }, 10, "Элементов больше среднего больше." },
        { "Test6 Все меньше", { 1, 2, 3, 4 }, 10, "Элементов меньше среднего больше." }
    };

    int passed = 0; // счетчик пройденных тестов
    out << "Результаты тестирования\n";
    out << "\n";

    // Цикл выполнения всех test в наборе tests
    for (const Test& test : tests)
    {
        int checked = 0; // обнуление пройденных элементов
        const string actual = Analyze(test.numbers, test.avg, checked);
        const bool ok = (actual == test.expected); // проверка ожидание == текущий рез-т
        if (ok)
        {
            ++passed;
        }

        // Вывод тестов в поток
        out << test.name << "\n";
        out << "Ожидалось: " << test.expected << "\n";
        out << "Получено : " << actual << "\n";
        out << "Обработано элементов: " << checked << " из " << test.numbers.size() << "\n";
        out << "Статус: " << (ok ? "PASS" : "FAIL") << "\n";
        out << "\n";
    }

    out << "\nПройдено тестов: " << passed << " из " << tests.size() << "\n";
}
