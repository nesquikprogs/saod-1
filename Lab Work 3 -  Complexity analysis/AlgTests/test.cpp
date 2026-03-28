#include "pch.h"
#include "../ComplexityModule.h"

#pragma region GetAnswerText

// При greaterCount > lessCount возвращается правильный текст.
TEST(GetAnswerTextTests, Greater)
{
    EXPECT_EQ(GetAnswerText(5, 2), "Элементов больше среднего больше.");
}

// При lessCount > greaterCount возвращается правильный текст.
TEST(GetAnswerTextTests, Less)
{
    EXPECT_EQ(GetAnswerText(1, 4), "Элементов меньше среднего больше.");
}

// При равных счетчиках возвращается текст про равенство.
TEST(GetAnswerTextTests, Equal)
{
    EXPECT_EQ(GetAnswerText(3, 3), "Количество элементов больше и меньше среднего одинаково.");
}

#pragma endregion

#pragma region Analyze

// Алгоритм завершает работу раньше конца списка при явном перевесе.
TEST(AnalyzeTests, EarlyStop)
{
    const vector<int> numbers = { 10, 10, 10, 0, 0 };
    int checked = 0;

    const string result = Analyze(numbers, 5, checked);

    EXPECT_EQ(result, "Элементов больше среднего больше.");
    EXPECT_LT(checked, static_cast<int>(numbers.size()));
}

// Худший случай: ничья определяется только после полного прохода.
TEST(AnalyzeTests, FullPassEqual)
{
    const vector<int> numbers = { 8, 6, 8, 6, 8, 6 };
    int checked = 0;

    const string result = Analyze(numbers, 7, checked);

    EXPECT_EQ(result, "Количество элементов больше и меньше среднего одинаково.");
    EXPECT_EQ(checked, static_cast<int>(numbers.size()));
}

// Корректная обработка элементов, равных среднему значению.
TEST(AnalyzeTests, WithAverageValues)
{
    const vector<int> numbers = { 3, 5, 5, 7 };
    int checked = 0;

    const string result = Analyze(numbers, 5, checked);

    EXPECT_EQ(result, "Количество элементов больше и меньше среднего одинаково.");
    EXPECT_EQ(checked, static_cast<int>(numbers.size()));
}

// Граничный случай из одного элемента.
TEST(AnalyzeTests, OneElement)
{
    const vector<int> numbers = { 100 };
    int checked = 0;

    const string result = Analyze(numbers, 50, checked);

    EXPECT_EQ(result, "Элементов больше среднего больше.");
    EXPECT_EQ(checked, 1);
}

#pragma endregion