#include "pch.h"
#include "..\AddRecursive.h"

#pragma region Базовые случаи

// Сумма двух нулей равна нулю
TEST(AddRecursiveTests, ReturnsZeroForTwoZeros)
{
    EXPECT_EQ(AddRecursive(0, 0), 0);
}

// Если второе число равно нулю, возвращается первое
TEST(AddRecursiveTests, ReturnsFirstNumberWhenSecondIsZero)
{
    EXPECT_EQ(AddRecursive(7, 0), 7);
    EXPECT_EQ(AddRecursive(-7, 0), -7);
}

// Если первое число равно нулю, результат равен второму
TEST(AddRecursiveTests, ReturnsSecondNumberWhenFirstIsZero)
{
    EXPECT_EQ(AddRecursive(0, 9), 9);
    EXPECT_EQ(AddRecursive(0, -9), -9);
}

#pragma endregion

#pragma region Положительные и отрицательные

// Оба аргумента положительные
TEST(AddRecursiveTests, AddsPositiveNumbers)
{
    EXPECT_EQ(AddRecursive(4, 6), 10);
}

// Оба аргумента отрицательные
TEST(AddRecursiveTests, AddsNegativeNumbers)
{
    EXPECT_EQ(AddRecursive(-4, -6), -10);
}

#pragma endregion

#pragma region Смешанные знаки

// Сложение чисел разных знаков
TEST(AddRecursiveTests, AddsMixedSignNumbers)
{
    EXPECT_EQ(AddRecursive(5, -2), 3);
    EXPECT_EQ(AddRecursive(-5, 2), -3);
}

// Противоположные числа должны давать ноль
TEST(AddRecursiveTests, ReturnsZeroWhenNumbersAreOpposites)
{
    EXPECT_EQ(AddRecursive(-8, 8), 0);
}

#pragma endregion