#include <iostream>
#include "DynamicArray.h"

using namespace std;

int main() {
    #pragma region PushAndPrint

    // Создаём динамический массив с начальной ёмкостью 2
    DynamicArray<int> arr(2);

    // Добавляем несколько элементов и смотрим, как меняется size и capacity
    cout << "Add elements:\n";
    for (int i = 1; i <= 5; ++i) {
        arr.push_back(i * 10);
        cout << "size = " << arr.size()
             << ", capacity = " << arr.capacity()
             << ", added " << i * 10 << '\n';
    }

    // Выводим текущее содержимое массива
    cout << "\nArray contents: ";
    for (size_t i = 0; i < arr.size(); ++i) {
        cout << arr[i] << ' ';
    }
    cout << '\n';

    #pragma endregion

    #pragma region PopAndShrink

    // Удаляем элементы и наблюдаем изменение размера и ёмкости
    cout << "\nRemove elements:\n";
    while (arr.size() > 0) {
        cout << "size = " << arr.size()
             << ", capacity = " << arr.capacity()
             << " -> pop_back()\n";
        arr.pop_back();
    }

    #pragma endregion

    #pragma region DeepCopyDemo

    // Демонстрация глубокого копирования с помощью копирующего конструктора
    cout << "\nDeep copy demo:\n";
    DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DynamicArray<int> b = a;
    b[0] = 100;

    // Выводим исходный массив a
    cout << "a: ";
    for (size_t i = 0; i < a.size(); ++i) {
        cout << a[i] << ' ';
    }
    cout << "\n";

    // Выводим изменённую копию b
    cout << "b: ";
    for (size_t i = 0; i < b.size(); ++i) {
        cout << b[i] << ' ';
    }
    cout << "\n";

    #pragma endregion

    return 0;
}