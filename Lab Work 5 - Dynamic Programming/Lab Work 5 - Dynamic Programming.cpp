#include <iostream>
#include <fstream>
#include "pascal.h"

using namespace std;

int main() {
    // Потоки для работы с файлами ввода и вывода
    ifstream in("INPUT.TXT"); // входные данные
    ofstream out("OUTPUT.TXT"); // выходные данные

    // Если один из файлов не открылся, завершаем программу
    if (!in.is_open() || !out.is_open()) {
        return 0;
    }

    int N; // количество строк треугольника Паскаля

    // Читаем N из файла INPUT.TXT
    if (!(in >> N)) {
        // Если ввод не удался, просто завершаем программу
        return 0;
    }

    // Проверяем, что N лежит в допустимом диапазоне по условию задачи
    if (N < 0 || N > 30) {
        // При некорректном N ничего не выводим
        return 0;
    }

    // Строим треугольник Паскаля из N строк
    auto triangle = buildPascalsTriangle(N);

    // Выводим построенный треугольник в файл OUTPUT.TXT
    printTriangle(triangle, out);

    return 0;
}




