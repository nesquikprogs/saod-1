#include <gtest/gtest.h>  // Google Test
#include "../array_utils.h"  
#include "../time_utils.h"

#include <sstream>
#include <fstream>
#include <string>
#include <cstdio>
#include <thread>
#include <chrono>

#pragma region SortCheck

#pragma region SortCheck_Success

// Тест на наличие элементов в массиве
TEST(IsSorted, EmptyArray)
{
    EXPECT_TRUE(is_sorted(nullptr, 0));
}

// Тест на массив из одного элемента
TEST(IsSorted, SingleElement)
{
    int arr[] = { 42 };
    EXPECT_TRUE(is_sorted(arr, 1));
}

// Тест на отсортированный массив с дубликатами
TEST(IsSorted, SortedWithDuplicates)
{
    int arr[] = { 1, 3, 3, 5, 8, 10 };
    EXPECT_TRUE(is_sorted(arr, 6));
}

// Тест на строгое возрастание с переходом через 0
TEST(IsSorted, Transition0)
{
    int arr[] = { -10, -2, 0, 7, 100 };
    EXPECT_TRUE(is_sorted(arr, 5));
}

// Тест на массив с равными значениями
TEST(IsSorted, AllEqual)
{
    int arr[10];
    for (int i = 0; i < 10; ++i) arr[i] = 13;
    EXPECT_TRUE(is_sorted(arr, 10));
}

#pragma endregion

#pragma region SortCheck_Fail

// Тест на массив с нарушением сортировки в середине
TEST(IsSorted, NotSortedMiddle)
{
    int arr[] = { 1, 4, 3, 7, 9 };
    EXPECT_FALSE(is_sorted(arr, 5));
}

// Тест на массив с нарушением сортировки в начале
TEST(IsSorted, NotSortedBeginning)
{
    int arr[] = { 5, 1, 2, 3 };
    EXPECT_FALSE(is_sorted(arr, 4));
}

// Тест на массив с нарушением сортировки в конце
TEST(IsSorted, NotSortedEnd)
{
    int arr[] = { 1, 2, 3, 0 };
    EXPECT_FALSE(is_sorted(arr, 4));
}

#pragma endregion

#pragma endregion 

#pragma region CreateRandomArray

#pragma region CreateRandomArray_Success

// Массив создается и значения лежат в заданном диапазоне
TEST(CreateRandomArray, ValidRange)
{
    const size_t size = 100;
    const int min_val = 10;
    const int max_val = 20;

    int* arr = create_random_array(size, min_val, max_val);
    ASSERT_NE(arr, nullptr);

    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_GE(arr[i], min_val);
        EXPECT_LE(arr[i], max_val);
    }

    delete[] arr;
}

// При некорректном диапазоне функция все равно возвращает рабочий массив
TEST(CreateRandomArray, InvalidRange)
{
    const size_t size = 10;
    const int min_val = 5;
    const int max_val = 3; // min > max

    int* arr = create_random_array(size, min_val, max_val);
    ASSERT_NE(arr, nullptr);

    delete[] arr;
}

#pragma endregion

#pragma region CreateRandomArray_Fail

// Нулевой размер массива
TEST(CreateRandomArray, ZeroSize)
{
    int* arr = create_random_array(0, 0, 10);
    EXPECT_EQ(arr, nullptr);
}

#pragma endregion

#pragma endregion 

#pragma region CreateSortedRandomArray

#pragma region CreateSortedRandomArray_Success

// Массив создается, значения в диапазоне и неубывают
TEST(CreateSortedRandomArray, ValidRange)
{
    const size_t size = 100;
    const int min_val = 1;
    const int max_val = 500;

    int* arr = create_sorted_random_array(size, min_val, max_val);
    ASSERT_NE(arr, nullptr);

    // Проверяем диапазон значений
    for (size_t i = 0; i < size; ++i)
    {
        EXPECT_GE(arr[i], min_val);
        EXPECT_LE(arr[i], max_val);
    }

    // Проверяем, что массив неубывает
    EXPECT_TRUE(is_sorted(arr, size));

    delete[] arr;
}

#pragma endregion

#pragma region CreateSortedRandomArray_Fail

// Нулевой размер массива
TEST(CreateSortedRandomArray, ZeroSize)
{
    int* arr = create_sorted_random_array(0, 0, 10);
    EXPECT_EQ(arr, nullptr);
}

#pragma endregion

#pragma endregion 

#pragma region PrintArray

#pragma region PrintArray_Success

// Вывод непустого массива в поток
TEST(PrintArray, NonEmpty)
{
    std::ostringstream out;
    int arr[] = { 1, 2, 3, 4, 5 };

    print_array(out, arr, 5);

    std::string result = out.str();
    // Проверяем, что в строке есть хотя бы одно число
    EXPECT_NE(result.find("1"), std::string::npos);
}

#pragma endregion

#pragma region PrintArray_Fail

// Пустой массив или нулевой указатель
TEST(PrintArray, EmptyArray)
{
    std::ostringstream out;
    print_array(out, nullptr, 0);
    std::string result = out.str();
    // Проверяем, что что-то напечатано (ветка пустого массива сработала)
    EXPECT_FALSE(result.empty());
}

#pragma endregion

#pragma endregion 

#pragma region SaveArrayToFile

#pragma region SaveArrayToFile_Success

// Корректная запись массива в файл
TEST(SaveArrayToFile, ValidInput)
{
    const char* filename = "test_array_output.txt";
    int arr[] = { 10, 20, 30 };

    EXPECT_TRUE(save_array_to_file(filename, arr, 3));

    std::ifstream fin(filename);
    ASSERT_TRUE(fin.is_open());

    int v1 = 0, v2 = 0, v3 = 0;
    fin >> v1 >> v2 >> v3;
    EXPECT_EQ(v1, 10);
    EXPECT_EQ(v2, 20);
    EXPECT_EQ(v3, 30);

    fin.close();
    std::remove(filename);
}

#pragma endregion

#pragma region SaveArrayToFile_Fail

// Некорректные входные данные
TEST(SaveArrayToFile, NullFilename)
{
    int arr[] = { 1, 2, 3 };
    EXPECT_FALSE(save_array_to_file(nullptr, arr, 3));
}

TEST(SaveArrayToFile, NullArray)
{
    EXPECT_FALSE(save_array_to_file("test.txt", nullptr, 3));
}

TEST(SaveArrayToFile, ZeroSize)
{
    int arr[] = { 1, 2, 3 };
    EXPECT_FALSE(save_array_to_file("test.txt", arr, 0));
}

#pragma endregion

#pragma endregion 

#pragma region LinearSearch

#pragma region LinearSearch_Success

// Элемент найдён в начале массива
TEST(LinearSearch, FoundAtBeginning)
{
    int arr[] = { 5, 1, 2, 3 };
    size_t idx = linear_search(arr, 4, 5);
    EXPECT_EQ(idx, 0u);
}

// Элемент найдён в середине массива
TEST(LinearSearch, FoundInMiddle)
{
    int arr[] = { 1, 2, 42, 3 };
    size_t idx = linear_search(arr, 4, 42);
    EXPECT_EQ(idx, 2u);
}

// Элемент найден в конце массива
TEST(LinearSearch, FoundAtEnd)
{
    int arr[] = { 1, 2, 3, 99 };
    size_t idx = linear_search(arr, 4, 99);
    EXPECT_EQ(idx, 3u);
}

// При наличии дубликатов возвращается индекс первого вхождения
TEST(LinearSearch, Duplicates)
{
    int arr[] = { 1, 2, 2, 2, 3 };
    size_t idx = linear_search(arr, 5, 2);
    EXPECT_EQ(idx, 1u);
}

// Шаблонная функция работает и для строк
TEST(LinearSearch, StringArray)
{
    std::string arr[] = { "cat", "dog", "bird" };
    size_t idx = linear_search(arr, 3, std::string("dog"));
    EXPECT_EQ(idx, 1u);
}

#pragma endregion

#pragma region LinearSearch_Fail

// Элемент отсутствует в массиве
TEST(LinearSearch, NotFound)
{
    int arr[] = { 1, 2, 3, 4 };
    size_t idx = linear_search(arr, 4, 99);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

// Пустой массив
TEST(LinearSearch, EmptyArray)
{
    int arr[] = { 1, 2, 3 };
    size_t idx = linear_search(arr, 0, 1);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

// Нулевой указатель массива
TEST(LinearSearch, NullArray)
{
    const int* arr = nullptr;
    size_t idx = linear_search(arr, 10, 5);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

#pragma endregion

#pragma endregion

#pragma region BinarySearch

#pragma region BinarySearch_Success

// Элемент найден в начале отсортированного массива
TEST(BinarySearch, FoundAtBeginning)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t idx = binary_search(arr, 5, 1);
    EXPECT_EQ(idx, 0u);
}

// Элемент найден в середине отсортированного массива
TEST(BinarySearch, FoundInMiddle)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t idx = binary_search(arr, 5, 3);
    EXPECT_EQ(idx, 2u);
}

// Элемент найден в конце отсортированного массива
TEST(BinarySearch, FoundAtEnd)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t idx = binary_search(arr, 5, 5);
    EXPECT_EQ(idx, 4u);
}

// При наличии дубликатов может быть найден любой индекс с этим значением
TEST(BinarySearch, Duplicates)
{
    int arr[] = { 1, 2, 2, 2, 3 };
    size_t idx = binary_search(arr, 5, 2);
    EXPECT_TRUE(idx == 1u || idx == 2u || idx == 3u);
}

// Шаблонная функция бинарного поиска работает и для строк
TEST(BinarySearch, StringArray)
{
    std::string arr[] = { "apple", "banana", "cherry" };
    size_t idx = binary_search(arr, 3, std::string("banana"));
    EXPECT_EQ(idx, 1u);
}

#pragma endregion

#pragma region BinarySearch_Fail

// Элемент отсутствует в отсортированном массиве
TEST(BinarySearch, NotFound)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    size_t idx = binary_search(arr, 5, 99);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

// Пустой массив
TEST(BinarySearch, EmptyArray)
{
    int arr[] = { 1, 2, 3 };
    size_t idx = binary_search(arr, 0, 1);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

// Нулевой указатель массива
TEST(BinarySearch, NullArray)
{
    const int* arr = nullptr;
    size_t idx = binary_search(arr, 10, 5);
    EXPECT_EQ(idx, static_cast<size_t>(-1));
}

#pragma endregion

#pragma endregion

#pragma region MeasureTime

// Выполнение пустой лямбды занимает неотрицательное время
TEST(MeasureTime, EmptyLambda)
{
    auto ms = measure_time_ms([]() {});
    EXPECT_GE(ms, 0);
}

// Лямбда с простой работой (цикл) тоже отрабатывает без ошибок
TEST(MeasureTime, SimpleLoop)
{
    auto ms = measure_time_ms([]() {
        volatile long long sum = 0;
        for (int i = 0; i < 100000; ++i)
        {
            sum += i;
        }
    });

    EXPECT_GE(ms, 0);
}

// Лямбда с задержкой занимает заметное время (хотя бы 1 мс)
TEST(MeasureTime, Sleep_Millisecond)
{
    using namespace std::chrono_literals;

    auto ms = measure_time_ms([]() {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    });

    EXPECT_GE(ms, 1);
}

#pragma endregion
