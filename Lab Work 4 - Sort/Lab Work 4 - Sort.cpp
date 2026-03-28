#include <iostream>
#include <vector>
#include <fstream>
#include "Sort.h"
#include "MeasureTime.h"

using namespace std;

int main()
{
    // Включаем русскую локаль для корректного вывода текста в консоль
    setlocale(LC_ALL, "Russian");

    // Инициализируем простой генератор случайных чисел rand()
    srand(static_cast<unsigned int>(time(nullptr)));

    // Размеры массивов
    vector<int> sizes = { 1000, 2000, 5000, 10000, 20000 };

    // Открываем CSV-файл, куда будем записывать результаты измерений
    ofstream out("results.csv");
    if (!out.is_open())
    {
        cerr << "Не удалось открыть файл results.csv для записи.\n";
        return 1;
    }

    // Заголовок CSV-файла
    out << "n;merge_us;bubble_us;quick_us\n";

    // Сколько раз повторяем эксперимент для каждого n, чтобы усреднить результат
    const int runs = 100;

    for (int n : sizes)
    {
        // Накопленные суммы времени для каждой сортировки при данном n
        long long merge_sum = 0;
        long long bubble_sum = 0;
        long long quick_sum = 0;

        for (int r = 0; r < runs; ++r)
        {
            // Генерируем базовый случайный массив длины n (простым rand())
            vector<int> base(n);
            for (int i = 0; i < n; ++i)
                base[i] = rand() % 2000001 - 1000000; // диапазон [-1_000_000; 1_000_000]

            // Делаем копии базового массива для каждой сортировки отдельно
            vector<int> a = base; // для mergeSort
            vector<int> b = base; // для bubbleSort
            vector<int> c = base; // для quickSort

            // Измеряем время сортировки слиянием
            merge_sum += measure_time_ms(
                [](int* arr, int len)
                {
                    mergeSort(arr, 0, len - 1);
                },
                a.data(), n
            );

            // Измеряем время пузырьковой сортировки
            bubble_sum += measure_time_ms(
                [](int* arr, int len)
                {
                    bubbleSort(arr, len);
                },
                b.data(), n
            );

            // Измеряем время быстрой сортировки 
            quick_sum += measure_time_ms(
                [](int* arr, int len)
                {
                    quickSort(arr, 0, len - 1);
                },
                c.data(), n
            );
        }

        long long merge_avg = merge_sum / runs; // среднее время mergeSort в микросекундах
        long long bubble_avg = bubble_sum / runs; // среднее время bubbleSort в микросекундах
        long long quick_avg  = quick_sum  / runs; // среднее время quickSort в микросекундах

        // Записываем результаты для данного n в одну строку CSV
        out << n << ";" << merge_avg << ";" << bubble_avg << ";" << quick_avg << "\n";

        cout << "n = " << n
             << " | merge = " << merge_avg << " us"
             << " | bubble = " << bubble_avg << " us"
             << " | quick = " << quick_avg << " us" << endl;
    }

    out.close();



    return 0;
}
