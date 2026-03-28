#ifndef ARRAY_UTILS_H
#define ARRAY_UTILS_H

#include <cstddef>  // для size_t
#include <ostream>  // для потоков вывода(в консоль, в файл)

/// <summary>
/// Объявление функции для создания массива и заполнения его случайными числами в заданном диапазоне
/// </summary>
/// <param name="size">Количество элементов</param>
/// <param name="min_val">Минимальное значение диапазона</param>
/// <param name="max_val">Максимальное значение диапазона</param>
/// <returns>Указатель на начало динамического массива</returns>
int* create_random_array(size_t size, int min_val, int max_val);

/// <summary>
/// Объявление функции для создания массива и заполнения возрастающей последовательностью случайных чисел в заданном диапазоне
/// </summary>
/// <param name="size">Количество элементов</param>
/// <param name="min_val">Минимальное значение диапазона</param>
/// <param name="max_val">Максимальное значение диапазона</param>
/// <returns>Указатель на начало динамического массива</returns>
int* create_sorted_random_array(size_t size, int min_val, int max_val);

/// <summary>
/// Объявление функции для вывода массива в любой поток (консоль или файл)
/// </summary>
/// <param name="out">Куда выводить</param>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
void print_array(std::ostream& out, const int* arr, size_t size);

/// <summary>
/// Объявление функции для сохранения массива в текстовый файл 
/// </summary>
/// <param name="filename">Имя файла</param>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
/// <returns>bool успех/неудача</returns>
bool save_array_to_file(const char* filename, const int* arr, size_t size);

/// <summary>
/// Объявление функции для проверки, отсортирован ли массив по возрастанию
/// </summary>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
/// <returns>bool успех/неудача</returns>
bool is_sorted(const int* arr, size_t size);

/// <summary>
/// Шаблонная функция для последовательного (линейного) поиска элемента в массиве
/// </summary>
/// <typeparam name="T">Тип, который будет подставляться автоматическ</typeparam>
/// <param name="arr">Указатель на массив</param>
/// <param name="size">Количество элементов</param>
/// <param name="value">Искомое значение</param>
/// <returns>Индекс первого вхождения(искомый элемент)</returns>
template<typename T>
size_t linear_search(const T* arr, size_t size, const T& value)
{
    if (!arr || size == 0) {
		return static_cast<size_t>(-1); // возвращаем -1, если массив пустой или указатель некорректный
    }

    for (size_t i = 0; i < size; ++i) {
        if (arr[i] == value) {
			return i; // возвращаем индекс первого найденного элемента
        }
    }

	return static_cast<size_t>(-1); // возвращаем -1, если элемент не найден
}

/// <summary>
/// Шаблонная функция для бинарного поиска элемента в отсортированном по возрастанию массиве
/// </summary>
/// <typeparam name="T">Тип элементов массива</typeparam>
/// <param name="arr">Указатель на отсортированный массив</param>
/// <param name="size">Количество элементов</param>
/// <param name="value">Искомое значение</param>
/// <returns>Индекс найденного элемента или size_t(-1), если не найден</returns>
template<typename T>
size_t binary_search(const T* arr, size_t size, const T& value)
{
    if (!arr || size == 0) {
        return static_cast<size_t>(-1); // возвращаем -1, если массив пустой или указатель некорректный
    }
    
    size_t left = 0; // левая граница 
    size_t right = size - 1; // правая граница

    while (left <= right) // пока границы не зашли друг за друга
    {
        size_t mid = left + (right - left) / 2; // серединный элемент

        if (arr[mid] == value) {
            return mid; // если серединный совпадает с искомым то возвращаем
        }
        else if (arr[mid] < value) {
            left = mid + 1; // если искомое больше серединного, то убирем левую часть 
        }
        else {
            if (mid == 0) break; // защита от переполнения 
            right = mid - 1; // если искомое меньше середины, то убираем правую часть  
        }
    }

    return static_cast<size_t>(-1); // значение не найдено 
}

#endif




