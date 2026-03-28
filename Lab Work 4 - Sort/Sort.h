#pragma once

#include <utility> // std::swap

#pragma region mergeSort

/// <summary>
/// Шаблонная функция слияния двух отсортированных подмассивов.
/// Сложность по времени: O(n). Дополнительная память: O(n).
/// </summary>
/// <typeparam name="T">Тип элементов массива (должен поддерживать сравнение и присваивание)</typeparam>
/// <param name="arr">Массив элементов</param>
/// <param name="left">Индекс первого элемента левого подмассива</param>
/// <param name="mid">Индекс последнего элемента левого подмассива</param>
/// <param name="right">Индекс последнего элемента правого подмассива</param>
template <typename T>
void merge(T arr[], int left, int mid, int right)
{
    // Длины левого и правого подмассивов
    size_t n1 = static_cast<size_t>(mid - left + 1);
    size_t n2 = static_cast<size_t>(right - mid);

    // Временные массивы под копии
    T* L = new T[n1];
    T* R = new T[n2];

    // Копируем данные во временные массивы
    for (size_t i = 0; i < n1; ++i)
        L[i] = arr[left + static_cast<int>(i)];
    for (size_t j = 0; j < n2; ++j)
        R[j] = arr[mid + 1 + static_cast<int>(j)];

    // Индексы для слияния
    size_t i = 0; // текущая позиция в L
    size_t j = 0; // текущая позиция в R
    int    k = left; // текущая позиция в исходном массиве arr

    // Пока в обоих подмассивах есть элементы — выбираем минимальный
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            ++i;
        }
        else
        {
            arr[k] = R[j];
            ++j;
        }
        ++k;
    }

    // Добрасываем хвост левого подмассива (если остался)
    while (i < n1)
    {
        arr[k] = L[i];
        ++i;
        ++k;
    }

    // Добрасываем хвост правого подмассива (если остался)
    while (j < n2)
    {
        arr[k] = R[j];
        ++j;
        ++k;
    }

    delete[] L;
    delete[] R;
}

/// <summary>
/// Шаблонная рекурсивная функция сортировки массива  по возраставнию на отрезке [left; right].
/// Сложность по времени (лучший/средний/худший случай): O(n log n).
/// Дополнительная память: O(n) на временные массивы + O(log n) на стек.
/// </summary>
/// <typeparam name="T">Тип элементов массива (должен поддерживать сравнение и присваивание)</typeparam>
/// <param name="arr">Массив элементов</param>
/// <param name="left">Левая граница сортируемого отрезка</param>
/// <param name="right">Правая граница сортируемого отрезка</param>
template <typename T>
void mergeSort(T arr[], int left, int right)
{
    // База рекурсии: 0 или 1 элемент — уже отсортировано
    if (left >= right)
        return;

    int mid = left + (right - left) / 2;

    // Рекурсивно сортируем левую и правую части
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);

    // Сливаем два отсортированных подмассива
    merge(arr, left, mid, right);
}

#pragma endregion

#pragma region bubbleSort

/// <summary>
/// Шаблонная пузырьковая сортировка массива по возрастанию.
/// Сложность по времени: лучший случай O(n) (массив уже отсортирован),
/// средний и худший случаи — O(n^2).
/// Дополнительная память: O(1).
/// </summary>
/// <typeparam name="T">Тип элементов массива (должен поддерживать сравнение и присваивание)</typeparam>
/// <param name="arr">Массив элементов</param>
/// <param name="n">Количество элементов массива</param>
template <typename T>
void bubbleSort(T arr[], int n)
{
    // Внешний цикл — количество проходов по массиву
    for (size_t i = 0; i + 1 < static_cast<size_t>(n); ++i)
    {
        bool swapped = false; // флаг: был ли обмен на этом проходе

        // Внутренний цикл — попарное сравнение соседних элементов
        for (size_t j = 0; j + 1 + i < static_cast<size_t>(n); ++j)
        {
            if (arr[j] > arr[j + 1])
            {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // Если за проход не было ни одного обмена — массив уже отсортирован
        if (!swapped)
            break;
    }
}

#pragma endregion

#pragma region quickSort

/// <summary>
/// Шаблонная функция разбиения массива относительно опорного элемента.
/// Сложность по времени: O(n). Дополнительная память: O(1).
/// </summary>
/// <typeparam name="T">Тип элементов массива (должен поддерживать сравнение и присваивание)</typeparam>
/// <param name="arr">Массив элементов</param>
/// <param name="low">Левая граница подмассива</param>
/// <param name="high">Правая граница подмассива</param>
/// <returns>Индекс позиции опорного элемента после разбиения</returns>
template <typename T>
int partition(T arr[], int low, int high)
{
    T pivot = arr[high]; // опорный элемент
    int i = low - 1; // индекс последнего элемента, меньшего pivot

    // По элементам массива
    for (int j = low; j < high; ++j)
    {
        if (arr[j] < pivot)
        {
            ++i;
            std::swap(arr[i], arr[j]);
        }
    }

    // Ставим опорный элемент сразу после элементов, меньших pivot
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/// <summary>
/// Шаблонная рекурсивная функция быстрой сортировки массива по возрастанию.
/// Сложность по времени: в среднем и в лучшем случае O(n log n),
/// в худшем случае — O(n^2).
/// Дополнительная память: в среднем O(log n) на стек рекурсии, в худшем случае — O(n).
/// </summary>
/// <typeparam name="T">Тип элементов массива (должен поддерживать сравнение и присваивание)</typeparam>
/// <param name="arr">Массив элементов</param>
/// <param name="low">Левая граница сортируемого подмассива</param>
/// <param name="high">Правая граница сортируемого подмассива</param>
template <typename T>
void quickSort(T arr[], int low, int high)
{
    // База рекурсии: пустой подмассив или один элемент
    if (low >= high)
        return;

    // Разбиваем массив и получаем позицию опорного элемента
    int pivotIndex = partition(arr, low, high);

    // Рекурсивно сортируем левую и правую части
    quickSort(arr, low, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, high);
}

#pragma endregion