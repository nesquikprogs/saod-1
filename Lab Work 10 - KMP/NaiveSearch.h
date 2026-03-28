#pragma once

#include <vector>
#include <cstddef>

namespace string_search
{
    
    #pragma region NaiveSearch

    /// <summary>
    /// Наивный поиск всех вхождений шаблона в последовательности.
    /// При несовпадении мы не запоминаем сколько символов уже совпало.
    /// Big-O: O(n * m), где n — длина text, m — длина pattern.
    /// Big-O память: O(k), где k — количество найденных вхождений.
    /// </summary>
    /// <typeparam name="Seq">Тип последовательности с операцией индексирования и size()</typeparam>
    /// <param name="text">Последовательность, в которой ведётся поиск</param>
    /// <param name="pattern">Последовательность, которую ищем как подстроку</param>
    /// <returns>Вектор индексов начала всех вхождений</returns>
    template<typename Seq>
    std::vector<std::size_t> naive_search(const Seq& text, const Seq& pattern)
    {
        // Здесь будут накапливаться позиции всех найденных вхождений
        std::vector<std::size_t> result;

        const std::size_t n = text.size(); // длина текста 
        const std::size_t m = pattern.size(); // длина шаблона

        // Если шаблон пустой или длиннее текста, то вхождений нет
        if (m == 0 || n < m)
            return result;

        // Перебираем все возможные позиции начала вхождения
        for (std::size_t i = 0; i + m <= n; ++i) // i - индекс кандидата на начало вхождения
        {
            std::size_t j = 0; // сколько первых символов шаблона уже совпало 
            // Сравниваем шаблон с текущей частью текста посимвольно слева направо
            while (j < m && text[i + j] == pattern[j])
            {
                ++j;
            }
            // Если удалось сравнить весь шаблон без несовпадений, значит нашли вхождение
            if (j == m)
            {
                result.push_back(i);
            }
        }

        // Возвращаем все найденные позиции
        return result;
    }

    #pragma endregion

}


