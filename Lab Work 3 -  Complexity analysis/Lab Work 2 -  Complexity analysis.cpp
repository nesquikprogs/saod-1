#include "ComplexityModule.h"

#include <iostream>
#include <clocale>
#include <windows.h>

using namespace std;

int main()
{
    
    #pragma region RusLoc

    SetConsoleCP(65001);
    SetConsoleOutputCP(65001);
    setlocale(LC_ALL, ".UTF-8");


    #pragma endregion
    
    RunTestsToFile("test_results.txt"); // завпуск тестов в файл

    // Ввод чисел пользователем
    cout << "Введите числа через пробел:\n";
    vector<int> numbers = ReadNumbers();

    // Проверка что введеный список элементов не пуст
    if (numbers.empty())
    {
        cout << "Список пуст.\n";
        return 0;
    }

    // Ввод среднего
    cout << "Введите среднее значение: ";
    double avg = 0; // изначальное обнуление среднего
    cin >> avg;

    // Анализ + вывод кол-ва просмотренных элементов
    int checked = 0;
    string answer = Analyze(numbers, avg, checked);

    cout << answer << "\n";
    cout << "Обработано элементов: " << checked << " из " << numbers.size() << "\n";
    cout << "Результаты тестов сохранены в test_results.txt\n";

    return 0;
}
