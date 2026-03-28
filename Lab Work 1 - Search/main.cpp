#include <iostream>
#include <iomanip>
#include <windows.h>
#include <clocale>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>

#include "array_utils.h"
#include "time_utils.h"

using namespace std;

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));

    #pragma region ConsoleSetup

    // Настройка консоли для русского языка (UTF-8)
    SetConsoleOutputCP(65001); // CP_UTF8
    SetConsoleCP(65001);
    setlocale(LC_ALL, ".UTF8");

    #pragma endregion

    #pragma region CreateRandomArray

  //  {
		//// Параметры для генерации массива
  //      const size_t N = 20;
  //      const int MIN_VAL = 1;
  //      const int MAX_VAL = 100;

		//// Создаём и заполняем массив случайными числами
  //      cout << "Создание случайного массива размером " << N << " элементов\n";
  //      int* arr = create_random_array(N, MIN_VAL, MAX_VAL);
  //      if (!arr) {
  //          cout << "Ошибка выделения памяти\n";
  //          return 1;
  //      }
  //      
		//// Выводим сгенерированный массив на экран
  //      cout << "Сгенерированный случайный массив:\n";
  //      print_array(cout, arr, N);

		//// Сохраняем массив в файл
  //      cout << "\nСохранение в файл array_random.txt  ";
  //      cout << (save_array_to_file("array_random.txt", arr, N) ? "OK" : "ОШИБКА") << "\n";

		//// Проверяем, отсортирован ли массив
  //      cout << "Проверка сортировки случайного массива: "
  //          << (is_sorted(arr, N) ? "отсортирован" : "не отсортирован")
  //          << "\n\n";

  //      delete[] arr;
  //  }

    #pragma endregion

    #pragma region CreateSortedArray

  //  {
		//// Параметры для генерации массива
  //      const size_t N = 20;
  //      const int MIN_VAL = 1;
  //      const int MAX_VAL = 500;

		//// Создаём и заполняем массив возрастающей последовательностью случайных чисел
  //      cout << "Создание монотонно возрастающего массива размером " << N << " элементов\n";
  //      int* arr = create_sorted_random_array(N, MIN_VAL, MAX_VAL);
  //      if (!arr) {
  //          cout << "Ошибка выделения памяти\n";
  //          return 1;
  //      }

		//// Выводим сгенерированный массив на экран
  //      cout << "Сгенерированный отсортированный массив:\n";
  //      print_array(cout, arr, N);

		//// Сохраняем массив в файл
  //      cout << "\nСохранение в файл array_sorted.txt ";
  //      cout << (save_array_to_file("array_sorted.txt", arr, N) ? "OK" : "ОШИБКА") << "\n";

		//// Проверяем, отсортирован ли массив
  //      cout << "Проверка сортировки: "
  //          << (is_sorted(arr, N) ? "отсортирован" : "не отсортирован")
  //          << "\n\n"; 

  //      delete[] arr;
  //  }

    #pragma endregion

    #pragma region LinearSearchSmallArrayDemo

 //   cout << "\nТест последовательного поиска (маленький массив):\n";

	//// Создаём небольшой массив для наглядности
	//const size_t small_N = 15; // небольшой размер для наглядности
 //   int* small_arr = create_random_array(small_N, 1, 100);
 //   print_array(cout, small_arr, small_N);

 //   // Хардкодим искомый элемент, который точно есть в массиве
 //   int target = small_arr[5];  // берём элемент, который точно есть
 //   size_t idx = linear_search(small_arr, small_N, target);
 //   cout << "Элемент " << target << " найден по индексу " << idx << endl;

	//// Хардкодим искомый элемент, которого точно нет в массиве
 //   int not_found = 9999;
 //   idx = linear_search(small_arr, small_N, not_found);
 //   cout << "Элемент " << not_found << (idx == size_t(-1) ? " не найден" : "ошибка") << endl;

 //   delete[] small_arr;

    #pragma endregion 

    #pragma region TimeMeasurement_LinearSearch

    cout << "\nИзмерение времени линейного поиска (лучший / средний / худший случаи)\n";
    cout << "Количество повторений: лучший - 1000000, средний - 10000, худший - 1000\n\n";

    const size_t REPEATS_LINEAR_BEST = 1000000;   // количество повторений для лучшего случая 
    const size_t REPEATS_LINEAR_AVG  = 10000;     // количество повторений для среднего случая
    const size_t REPEATS_LINEAR_WORST = 1000;     // количество повторений для худшего случая

    // Откроем файл для записи результатов измерений 
    ofstream time_out("linear_search_time_results.csv");
    if (time_out.is_open())
    {
        time_out << "N;best_ms;avg_ms;worst_ms\n"; // три случая
    }

    for (size_t exp = 3; exp <= 7; ++exp) {
        size_t N = static_cast<size_t>(pow(10, exp)); // вычисляем размер массива

		cout << "N = " << N << " ... "; // выводим текущий размер массива

        // Диапазон делаем зависящим от N, чтобы в среднем случае было меньше дубликатов
        int max_val = static_cast<int>(N * 10);
        int* arr = create_random_array(N, 1, max_val);
        if (!arr) {
            cout << "Не хватило памяти\n";
			continue; // переходим к следующему размеру массива
        }

        // Лучший случай: искомый элемент на первом месте
        long long total_best_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_LINEAR_BEST; ++r) {
                int target = arr[0];
                linear_search(arr, N, target);
            }
        });
        double best_ms = static_cast<double>(total_best_ms) / REPEATS_LINEAR_BEST;

        // Средний случай: ищем случайный существующий элемент из массива 
        long long total_avg_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_LINEAR_AVG; ++r) {
                int target = arr[rand() % N];
                linear_search(arr, N, target);
            }
        });
        double avg_ms = static_cast<double>(total_avg_ms) / REPEATS_LINEAR_AVG;

        // Худший случай: элемент отсутствует в массиве
        long long total_worst_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_LINEAR_WORST; ++r) {
                int target = max_val + 1 + rand() % max_val;  // число, которого нет в массиве
                linear_search(arr, N, target);
            }
        });
		double worst_ms = static_cast<double>(total_worst_ms) / REPEATS_LINEAR_WORST;

        cout << "лучший/средний/худший: "
             << fixed << setprecision(6)
             << best_ms << " / " << avg_ms << " / " << worst_ms << " мс\n";

        // Запись в файл для графика
        if (time_out.is_open())
        {
            auto format_ms = [](double value) {
                std::ostringstream oss;
                oss << fixed << setprecision(6) << value;
                std::string s = oss.str();
                std::replace(s.begin(), s.end(), '.', ',');
                return s;
            };

            std::string best_str  = format_ms(best_ms);
            std::string avg_str   = format_ms(avg_ms);
            std::string worst_str = format_ms(worst_ms);

            time_out << N << ';' << best_str << ';' << avg_str << ';' << worst_str << '\n';
        }

        delete[] arr;
    }

    if (time_out.is_open())
    {
        time_out.close();
        cout << "\nРезультаты измерений сохранены в файл search_time_results.csv\n";
    }

    #pragma endregion

    #pragma region TimeMeasurement_BinarySearch

    cout << "\nИзмерение времени бинарного поиска (худший случай)\n";
    cout << "Количество повторений для каждого размера: 100000\n\n";

    const size_t REPEATS_BIN = 100000; // больше повторений, т.к. бинарный поиск очень быстрый

    // Откроем файл для записи результатов измерений бинарного поиска
    ofstream time_out_bin("binary_search_time_results.csv");
    if (time_out_bin.is_open())
    {
        time_out_bin << "N;best_ms;avg_ms;worst_ms\n";
    }

    for (size_t exp = 3; exp <= 7; ++exp) {
        size_t N = static_cast<size_t>(pow(10, exp)); // вычисляем размер массива

        cout << "N = " << N << " ... ";

        // Диапазон делаем зависящим от N, чтобы в среднем случае было меньше дубликатов
        int max_val = static_cast<int>(N * 10);
        int* arr = create_sorted_random_array(N, 1, max_val);
        if (!arr) {
            cout << "Не хватило памяти\n";
            continue;
        }

        // Лучший случай: сразу попадаем в середину
        long long total_best_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_BIN; ++r) {
                int target = arr[N / 2];
                binary_search(arr, N, target);
            }
        });
        double best_ms = static_cast<double>(total_best_ms) / REPEATS_BIN;

        // Средний случай: ищем случайный существующий элемент массива
        long long total_avg_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_BIN; ++r) {
                int target = arr[rand() % N];
                binary_search(arr, N, target);
            }
        });
        double avg_ms = static_cast<double>(total_avg_ms) / REPEATS_BIN;

        // Худший случай: элемент отсутствует в массиве
        long long total_worst_ms = measure_time_ms([&]() {
            for (size_t r = 0; r < REPEATS_BIN; ++r) {
                int target = max_val + 1 + rand() % max_val; // число вне диапазона массива
                binary_search(arr, N, target);
            }
        });
        double worst_ms = static_cast<double>(total_worst_ms) / REPEATS_BIN;

        cout << "лучший/средний/худший: "
             << fixed << setprecision(6)
             << best_ms << " / " << avg_ms << " / " << worst_ms << " мс\n";

        if (time_out_bin.is_open())
        {
            auto format_ms = [](double value) {
                std::ostringstream oss;
                oss << fixed << setprecision(6) << value;
                std::string s = oss.str();
                std::replace(s.begin(), s.end(), '.', ',');
                return s;
            };

            std::string best_str  = format_ms(best_ms);
            std::string avg_str   = format_ms(avg_ms);
            std::string worst_str = format_ms(worst_ms);

            time_out_bin << N << ';' << best_str << ';' << avg_str << ';' << worst_str << '\n';
        }

        delete[] arr;
    }

    if (time_out_bin.is_open())
    {
        time_out_bin.close();
        cout << "\nРезультаты измерений бинарного поиска сохранены в файл binary_search_time_results.csv\n";
    }

    #pragma endregion

    cout << "\nПоиск завершен.\n";
    system("pause");  // чтобы консоль не закрывалась сразу
    return 0;
}