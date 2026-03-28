#pragma once

#include <vector>
#include <ostream>

using namespace std;

/// <summary>
/// Объявление функции постройки первых n строк треугольника Паскаля.
/// </summary>
/// <param name="n">Количество строк (0–30)</param>
/// <returns>Двумерный вектор коэффициентов C(i, j)</returns>
vector<vector<long long>> buildPascalsTriangle(int n);

/// <summary>
/// Объявление функции вывода треугольника Паскаля в указанный поток вывода.
/// </summary>
/// <param name="triangle">Двумерный вектор строк треугольника</param>
/// <param name="os">Поток вывода</param>
void printTriangle(const vector<vector<long long>>& triangle, ostream& os);

