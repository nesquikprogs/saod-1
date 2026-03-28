#include "pascal.h"
#include <iostream>

using namespace std;

/// <summary>
/// Функция постройки первых n строк треугольника Паскаля.
/// </summary>
/// <param name="n">Количество строк (0–30)</param>
/// <returns>Двумерный вектор коэффициентов C(i, j)</returns>
vector<vector<long long>> buildPascalsTriangle(int n) {
    vector<vector<long long>> triangle; // внешний вектор для всех строк
    triangle.reserve(n); // заранее резервируем память под n строк

    // Цикл по номеру строки треугольника
    for (int i = 0; i < n; ++i) {
        vector<long long> row(i + 1); // в i‑й строке i + 1 элементов

        row[0] = 1; // первый элемент строки
        row[i] = 1; // последний элемент строки

        // Цикл по внутренним элементам строки (без крайних единиц)
        for (int j = 1; j < i; ++j) {
            // Внутренние элементы рассчитываются по формуле C(i, j) = C(i-1, j-1) + C(i-1, j)
            row[j] = triangle[i - 1][j - 1] + triangle[i - 1][j];
        }

        triangle.push_back(row); // сохраняем готовую строку в общий треугольник
    }

    return triangle;
}

/// <summary>
/// Функция вывода треугольника Паскаля в указанный поток вывода.
/// </summary>
/// <param name="triangle">Двумерный вектор строк треугольника</param>
/// <param name="os">Поток вывода</param>
void printTriangle(const vector<vector<long long>>& triangle, ostream& os) {
    // Цикл по всем строкам треугольника
    for (size_t i = 0; i < triangle.size(); ++i) {
        const auto& row = triangle[i]; // текущая строка треугольника
        // Цикл по элементам внутри строки
        for (size_t j = 0; j < row.size(); ++j) {
            if (j > 0) { // пробел перед всеми элементами, кроме первого
                os << ' ';
            }
            os << row[j]; // вывод значения элемента
        }
        os << '\n'; // перевод строки после каждой строки треугольника
    }
}

