#include "pch.h"
#include "..\\Sort.h"

#pragma region mergeSort

// Сортировка уже отсортированного массива 
TEST(MergeSort, SortedArray)
{
    // Исходный уже отсортированный массив 
    int arr[5] = { 1, 2, 3, 4, 5 };
    const int n = 5;

    // Вызываем сортировку
    mergeSort(arr, 0, n - 1);

    // Ожидаем тот же порядок элементов
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка убывающего массива
TEST(MergeSort, ReversedArray)
{
    // Массив в обратном порядке
    int arr[5] = { 5, 4, 3, 2, 1 };
    const int n = 5;

    // Сортируем весь массив
    mergeSort(arr, 0, n - 1);

    // Ожидаем возрастание
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива с повторяющимися элементами
TEST(MergeSort, Duplicates)
{
    // Массив с дубликатами
    int arr[7] = { 4, 2, 2, 5, 3, 3, 1 };
    const int n = 7;

    // Сортируем
    mergeSort(arr, 0, n - 1);

    // Проверяем, что элементы отсортированы и дубликаты на местах
    int expected[] = { 1, 2, 2, 3, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива из одного элемента
TEST(MergeSort, OneElement)
{
    // Один элемент
    int arr[1] = { 42 };

    // Сортировка диапазона из одного элемента
    mergeSort(arr, 0, 0);

    // Значение не должно измениться
    EXPECT_EQ(arr[0], 42);
}

// Пустой диапазон (левая граница больше правой)
TEST(MergeSort, EmptyRange)
{
    // Небольшой массив
    int arr[3] = { 1, 2, 3 };

    // Неправильно заданный диапазон (left > right)
    mergeSort(arr, 2, 1);

    // Массив должен остаться без изменений
    int expected[] = { 1, 2, 3 };
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

#pragma endregion

#pragma region bubbleSort

// Сортировка уже отсортированного массива
TEST(BubbleSort, SortedArray)
{
    // Уже отсортированный массив
    int arr[5] = { 1, 2, 3, 4, 5 };
    const int n = 5;

    // Вызываем bubbleSort
    bubbleSort(arr, n);

    // Порядок элементов не должен измениться
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка убывающего массива
TEST(BubbleSort, ReversedArray)
{
    // Массив в убывающем порядке
    int arr[5] = { 5, 4, 3, 2, 1 };
    const int n = 5;

    // Сортируем
    bubbleSort(arr, n);

    // Ожидаем возрастание
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива с повторяющимися элементами
TEST(BubbleSort, Duplicates)
{
    // Массив с дубликатами
    int arr[7] = { 4, 2, 2, 5, 3, 3, 1 };
    const int n = 7;

    // Сортируем
    bubbleSort(arr, n);

    // Ожидаемый отсортированный массив
    int expected[] = { 1, 2, 2, 3, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива из одного элемента
TEST(BubbleSort, OneElement)
{
    // Массив из одного элемента
    int arr[1] = { 42 };
    const int n = 1;

    // Сортируем
    bubbleSort(arr, n);

    // Значение не меняется
    EXPECT_EQ(arr[0], 42);
}

// Вызов bubbleSort для массива длины 0
TEST(BubbleSort, EmptyArray)
{
    // Пустой массив (указатель и длина)
    int* arr = nullptr;

    // Сортировка ничего не должна делать и не падать
    bubbleSort(arr, 0);
    EXPECT_EQ(arr, nullptr);
}

#pragma endregion

#pragma region quickSort

// Сортировка уже отсортированного массива
TEST(QuickSort, SortedArray)
{
    // Уже отсортированный массив
    int arr[5] = { 1, 2, 3, 4, 5 };
    const int n = 5;

    // Вызов quickSort на всём массиве
    quickSort(arr, 0, n - 1);

    // Ожидаем тот же порядок
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка убывающего массива
TEST(QuickSort, ReversedArray)
{
    // Массив в обратном порядке
    int arr[5] = { 5, 4, 3, 2, 1 };
    const int n = 5;

    // Сортируем
    quickSort(arr, 0, n - 1);

    // Ожидаем возрастание
    int expected[] = { 1, 2, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива с повторяющимися элементами
TEST(QuickSort, Duplicates)
{
    // Массив с повторяющимися значениями
    int arr[7] = { 4, 2, 2, 5, 3, 3, 1 };
    const int n = 7;

    // Сортируем
    quickSort(arr, 0, n - 1);

    // Проверяем результат
    int expected[] = { 1, 2, 2, 3, 3, 4, 5 };
    for (int i = 0; i < n; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

// Сортировка массива из одного элемента
TEST(QuickSort, OneElement)
{
    // Один элемент
    int arr[1] = { 42 };

    // Сортируем от 0 до 0
    quickSort(arr, 0, 0);

    // Значение не меняется
    EXPECT_EQ(arr[0], 42);
}

// Левая граница больше правой
TEST(QuickSort, EmptyRange)
{
    // Небольшой массив
    int arr[3] = { 1, 2, 3 };

    // Диапазон с low > high
    quickSort(arr, 2, 1);

    // Массив должен остаться прежним
    int expected[] = { 1, 2, 3 };
    for (int i = 0; i < 3; ++i)
    {
        EXPECT_EQ(arr[i], expected[i]);
    }
}

#pragma endregion
