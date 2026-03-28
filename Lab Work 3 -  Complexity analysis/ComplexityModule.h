#pragma once

#include <string>
#include <vector>

using std::string;
using std::vector;

/// <summary>
/// Формирует текстовый ответ на основе сравнения двух счетчиков.
/// </summary>
/// <param name="greaterCount">Количество элементов, больших среднего значения</param>
/// <param name="lessCount">Количество элементов, меньших среднего значения</param>
/// <returns>Строка с итогом сравнения</returns>
string GetAnswerText(int greaterCount, int lessCount);

/// <summary>
/// Сравнивает количество элементов больше и меньше среднего с ранней остановкой.
/// </summary>
/// <param name="numbers">Входной список целых чисел</param>
/// <param name="avg">Среднее значение, относительно которого выполняется сравнение</param>
/// <param name="checked">Количество элементов, обработанных алгоритмом</param>
/// <returns>Строка с результатом сравнения</returns>
string Analyze(const vector<int>& numbers, double avg, int& checked);

/// <summary>
/// Считывает из консоли одну строку целых чисел, разделенных пробелами.
/// </summary>
/// <returns>Вектор считанных целых чисел</returns>
vector<int> ReadNumbers();

/// <summary>
/// Выполняет тестовые примеры и сохраняет результаты в текстовый файл.
/// </summary>
/// <param name="fileName">Имя файла для сохранения результатов тестирования</param>
void RunTestsToFile(const string& fileName);
