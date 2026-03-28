#include "array_utils.h"   // функции для работы с массивами

#include <cstdlib>         
#include <ctime>           
#include <fstream>         
#include <iostream>
#include <iomanip>

using namespace std;

#pragma region ArraysAndIsSorted

/// <summary>
/// Функция для создания массива и заполнения его случайными числами в заданном диапазоне
/// </summary>
/// <param name="size">Количество элементов</param>
/// <param name="min_val">Минимальное значнеие диапазона</param>
/// <param name="max_val">Максмальноезначнеие диапазона</param>
/// <returns>Указатель на начало динамического массива</returns>
int* create_random_array(size_t size, int min_val, int max_val)
{
    // Проверяем корректность размера
    if (size == 0) return nullptr;

    // Выделяем память под массив
    int* arr = new (nothrow) int[size];
    if (!arr) return nullptr;

    // Вычисляем ширину диапазона
    int range = max_val - min_val + 1;
    if (range <= 0) range = 1;  // защита от некорректного диапазона

    // Заполняем массив
    for (size_t i = 0; i < size; ++i)
    {
    arr[i] = min_val + (rand() % range); // генерируем случайное число в диапазоне [min_val, max_val]
    }
    return arr;
}

/// <summary>
/// Функция для создания массива и заполнения возрастающей последовательностью случайных чисел в заданном диапазоне
/// </summary>
/// <param name="size">Количество элементов</param>
/// <param name="min_val">Минимальное значение диапазона</param>
/// <param name="max_val">Максимальное значение диапазона</param>
/// <returns>Указатель на начало массива</returns>
int* create_sorted_random_array(size_t size, int min_val, int max_val)
{
    // Проверяем корректность размера
    if (size == 0) return nullptr;

    // Выделяем память под массив
    int* arr = new (nothrow) int[size];
    if (!arr) return nullptr;

    // Вычисляем ширину диапазона
    int range = max_val - min_val + 1;
    if (range <= 0) range = 1;

    // Создаем первое значение в диапазоне 
    arr[0] = min_val + (rand() % range);

    // Каждое следующее значение больше предыдущего
    for (size_t i = 1; i < size; ++i)
    {
        // Прирост для следующего элемента (от 1 до 10)
        int step = (rand() % 11); 

        // Потенциальный кандидат для следующего элемента
        int candidate = arr[i - 1] + step;

        // Проверка, не превышает ли кандидат максимальное значение диапазона
        arr[i] = (candidate <= max_val) ? candidate : max_val;
    }

    return arr;
}

/// <summary>
/// Функция для проверки, отсортирован ли массив по возрастанию
/// </summary>
/// <param name="arr">Указатель на начало массива</param>
/// <param name="size">Количество элементов масссива</param>
/// <returns>bool успех/провал</returns>
bool is_sorted(const int* arr, size_t size)
{
    // Пустой массив или массив из одного элемента всегда считается отсортированным
    if (!arr || size <= 1) return true;

	// Проверяем каждую пару соседних элементов
    for (size_t i = 0; i < size - 1; ++i)
    {
        if (arr[i] > arr[i + 1])
        {
            return false;
        }
    }

    return true;
}

#pragma endregion

#pragma region PrintArrayRegion

/// <summary>
/// Функция для вывода массива в любой поток (консоль или файл)
/// </summary>
/// <param name="out">Куда выводить</param>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
void print_array(ostream& out, const int* arr, size_t size)
{
	// Проверяем, что массив не пустой
    if (!arr || size == 0)
    {
        out << "(пустой массив)\n";
        return;
    }

	const int WIDTH = 6;  // для выравнивания чисел в столбцы 

	// Выводим элементы массива с выравниванием
    for (size_t i = 0; i < size; ++i)
    {
		out << setw(WIDTH) << arr[i]; // выводим число с заданной шириной поля для выравнивания

        // Перенос строки каждые 10 элементов для удобства чтения
        if ((i + 1) % 10 == 0) out << '\n';
    }

    // Если последняя строка неполная — добавляем перевод строки
    if (size % 10 != 0) out << '\n';
}

#pragma endregion

#pragma region SaveArrayToTextFile

/// <summary>
/// Функция для сохранения массива в текстовый файл
/// </summary>
/// <param name="filename">Имя файла</param>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
/// <returns>bool успех/провал</returns>
bool save_array_to_file(const char* filename, const int* arr, size_t size)
{
    // Проверяем корректность входных данных
    if (!filename || !arr || size == 0) return false;

	// Открываем файл для записи
    ofstream fout(filename);
	if (!fout.is_open()) return false; // проверяем, что файл успешно открыт

    // Записываем каждое число в отдельной строке
    for (size_t i = 0; i < size; ++i)
    {
        fout << arr[i] << '\n';
    }

    // Проверяем, успешно ли завершена запись
    return fout.good();
}

#pragma endregion




