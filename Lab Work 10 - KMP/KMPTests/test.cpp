#include "pch.h"

#include "../NaiveSearch.h"
#include "../KMPSearch.h"

using namespace string_search;

#pragma region String

// Одиночное вхождение шаблона в строке
TEST(StringSearch, SingleMatch)
{
    // Обычная ситуация
    const std::string text = "abcxabcdabxabcdabcdabcy";
    const std::string pattern = "abcdabcy";

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    // Ожидаем ровно одно вхождение в позиции 15
    ASSERT_EQ(1u, naive_result.size()); // для наивного алгоритма
    ASSERT_EQ(1u, kmp_result.size()); // для КМП

    EXPECT_EQ(15u, naive_result[0]); // проверяем саму позицию
    EXPECT_EQ(15u, kmp_result[0]);
}

// Несколько вхождений шаблона в строке
TEST(StringSearch, MultipleMatches)
{
    // Для поиска всех вхождений
    const std::string text = "aaaaa";
    const std::string pattern = "aa";

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    // В строке "aaaaa" подстрока "aa" встречается в позициях 0,1,2,3
    std::vector<std::size_t> expected = { 0,1,2,3 };

    EXPECT_EQ(expected, naive_result); // сравниваем полученный вектор с ожидаемым
    EXPECT_EQ(expected, kmp_result);
}

// Отсутствие вхождений
TEST(StringSearch, NoMatch)
{
    // Для отсутсвия вхождений
    const std::string text = "abcdefg";
    const std::string pattern = "xyz";

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    EXPECT_TRUE(naive_result.empty()); // оба алгоритма не должны ничего находить
    EXPECT_TRUE(kmp_result.empty());
}

// Шаблон длиннее текста
TEST(StringSearch, PatternLonger)
{
    // Длина шаблона больше длины исходного текста
    const std::string text = "short";
    const std::string pattern = "shoooooort";

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    EXPECT_TRUE(naive_result.empty()); // ожидаем пустой результат
    EXPECT_TRUE(kmp_result.empty());
}

#pragma endregion

#pragma region Sequence

// Поиск по вектору целых чисел
TEST(StringSearch, IntVectorMatches)
{
    // Последовательности
    const std::vector<int> text = { 1,2,3,4,2,3,4,5 };
    const std::vector<int> pattern = { 2,3,4 };

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    // Ожидаем два вхождения: с позиций 1 и 4
    std::vector<std::size_t> expected = { 1,4 };

    EXPECT_EQ(expected, naive_result); // проверяем совпадение с ожидаемым результатом
    EXPECT_EQ(expected, kmp_result);
}

// Поиск с совпадающими префиксами и суффиксами в шаблоне
TEST(StringSearch, OverlappingPattern)
{
    // Шаблон имеет пересекающиеся префиксы и суффиксы,
    const std::string text = "abababac";
    const std::string pattern = "ababac";

    const auto naive_result = naive_search(text, pattern);
    const auto kmp_result = kmp_search(text, pattern);

    // Ожидаем одно вхождение, начинающееся с позиции 2
    ASSERT_EQ(1u, naive_result.size());
    ASSERT_EQ(1u, kmp_result.size());

    EXPECT_EQ(2u, naive_result[0]); // указываем ожидаемую позицию
    EXPECT_EQ(2u, kmp_result[0]);
}

#pragma endregion
