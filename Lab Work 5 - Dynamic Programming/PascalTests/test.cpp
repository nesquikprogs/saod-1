#include "pch.h"
#include "../pascal.h"
#include <sstream>

using namespace std;

#pragma region TriangleBuild

// При n = 0 функция возвращает пустой треугольник
TEST(TriangleBuild, ZeroRows) {
    // Подготавливаем входные данные
    auto triangle = buildPascalsTriangle(0);

    // Ожидаем, что вектор строк пустой
    EXPECT_TRUE(triangle.empty());
}

// Одна строка треугольника
TEST(TriangleBuild, OneRow) {
    // Строим треугольник из одной строки
    auto triangle = buildPascalsTriangle(1);

    // Должна быть ровно одна строка и один элемент
    ASSERT_EQ(triangle.size(), 1u);
    ASSERT_EQ(triangle[0].size(), 1u);

    // Единственный элемент равен 1
    EXPECT_EQ(triangle[0][0], 1);
}

// Первые несколько строк соответствуют классическому примеру
TEST(TriangleBuild, FirstRows) {
    // Строим первые 5 строк треугольника Паскаля
    auto triangle = buildPascalsTriangle(5);

    // Должно получиться 5 строк
    ASSERT_EQ(triangle.size(), 5u);

    // 0-я строка: 1
    EXPECT_EQ(triangle[0].size(), 1u);
    EXPECT_EQ(triangle[0][0], 1);

    // 1-я строка: 1 1
    EXPECT_EQ(triangle[1].size(), 2u);
    EXPECT_EQ(triangle[1][0], 1);
    EXPECT_EQ(triangle[1][1], 1);

    // 2-я строка: 1 2 1
    EXPECT_EQ(triangle[2].size(), 3u);
    EXPECT_EQ(triangle[2][0], 1);
    EXPECT_EQ(triangle[2][1], 2);
    EXPECT_EQ(triangle[2][2], 1);

    // 3-я строка: 1 3 3 1
    EXPECT_EQ(triangle[3].size(), 4u);
    EXPECT_EQ(triangle[3][0], 1);
    EXPECT_EQ(triangle[3][1], 3);
    EXPECT_EQ(triangle[3][2], 3);
    EXPECT_EQ(triangle[3][3], 1);

    // 4-я строка: 1 4 6 4 1
    EXPECT_EQ(triangle[4].size(), 5u);
    EXPECT_EQ(triangle[4][0], 1);
    EXPECT_EQ(triangle[4][1], 4);
    EXPECT_EQ(triangle[4][2], 6);
    EXPECT_EQ(triangle[4][3], 4);
    EXPECT_EQ(triangle[4][4], 1);
}

// Общие свойства
TEST(TriangleBuild, SymmetryAndRandRow) {
    const int n = 8;

    // Строим треугольник до 8-й строки включительно
    auto triangle = buildPascalsTriangle(n);

    // Проверяем, что размер внешнего вектора правильный
    ASSERT_EQ(triangle.size(), static_cast<size_t>(n));

    // Каждая строка должна быть симметрична относительно центра
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j <= i; ++j) {
            EXPECT_EQ(triangle[i][j], triangle[i][i - j]) << "Несимметричная строка " << i;
        }
    }

    // Проверяем строку с индексом 7 на конкретные значения
    EXPECT_EQ(triangle[7][0], 1);
    EXPECT_EQ(triangle[7][1], 7);
    EXPECT_EQ(triangle[7][2], 21);
    EXPECT_EQ(triangle[7][3], 35);
    EXPECT_EQ(triangle[7][4], 35);
    EXPECT_EQ(triangle[7][5], 21);
    EXPECT_EQ(triangle[7][6], 7);
    EXPECT_EQ(triangle[7][7], 1);
}

// Максимальное значение n (n = 30)
TEST(TriangleBuild, MaxRows) {
    const int n = 30;

    // Строим треугольник до 30-й строки
    auto triangle = buildPascalsTriangle(n);

    // Убеждаемся, что создано именно n строк
    ASSERT_EQ(triangle.size(), static_cast<size_t>(n));

    // Берём 20-ю строку и смотрим несколько элементов ближе к началу
    const auto& row20 = triangle[20];

    // Первый элемент по определению равен 1
    EXPECT_EQ(row20[0], 1);

    // Дальше значения растут по мере приближения к середине строки
    EXPECT_LT(row20[0], row20[1]);
    EXPECT_LT(row20[1], row20[2]);
    EXPECT_LT(row20[2], row20[3]);
}

#pragma endregion

#pragma region TrianglePrint

// Проверяем, что при пустом треугольнике ничего не выводится
TEST(TrianglePrint, EmptyPrint) {
    // Готовим пустые данные
    vector<vector<long long>> triangle;

    // Строковый поток для проверки вывода
    stringstream buffer;

    // Пытаемся вывести пустой треугольник в строку
    printTriangle(triangle, buffer);

    // Ожидаем, что никакого текста не напечатано
    EXPECT_EQ(buffer.str(), "");
}

// Проверяем конкретный пример вывода для небольшого треугольника
TEST(TrianglePrint, PrintFormat) {
    // Готовим несколько строк треугольника Паскаля вручную
    vector<vector<long long>> triangle = {
        {1},
        {1, 1},
        {1, 2, 1},
        {1, 3, 3, 1},
        {1, 4, 6, 4, 1},
    };

    // Строковый поток для проверки вывода
    stringstream buffer;

    // Печатаем подготовленный треугольник в строку
    printTriangle(triangle, buffer);

    // Ожидаемая текстовая форма вывода (каждая строка с переводом строки)
    const string expected =
        "1\n"
        "1 1\n"
        "1 2 1\n"
        "1 3 3 1\n"
        "1 4 6 4 1\n";

    // Сравниваем реальный вывод с ожидаемым
    EXPECT_EQ(buffer.str(), expected);
}

#pragma endregion
