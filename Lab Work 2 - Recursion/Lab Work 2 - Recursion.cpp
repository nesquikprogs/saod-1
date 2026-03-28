#include <iostream>
#include <clocale>
#include "AddRecursive.h"

using namespace std;

int main()
{
    // Задание значений по умолчанию корректными
    int a = 0;
    int b = 0;

    // Ввод значений пользователем
    cout << "Enter two int: ";
    cin >> a >> b;

    // Вывод полученной суммы
    cout << "Summ: " << AddRecursive(a, b) << '\n';
    
    return 0;
}
