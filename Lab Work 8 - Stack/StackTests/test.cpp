#include "pch.h"
#include "..\Stack.h"

#pragma region Int

// Только что созданный стек пустой.
TEST(StackInt, Empty)
{
    Stack<int> s;

    // Новый стек не должен содержать элементов
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

// Операция push увеличивает размер.
TEST(StackInt, Push)
{
    Stack<int> s;

    // Первый push: в стеке один элемент 1
    s.push(1);
    EXPECT_FALSE(s.empty());
    EXPECT_EQ(s.size(), 1u);
    EXPECT_EQ(s.top(), 1);

    // Второй push: на вершине должен оказаться элемент 2
    s.push(2);
    EXPECT_EQ(s.size(), 2u);
    EXPECT_EQ(s.top(), 2);
}

// Элементы извлекаются в порядке LIFO.
TEST(StackInt, Pop)
{
    Stack<int> s;

    // Кладём три элемента в известном порядке
    s.push(10);
    s.push(20);
    s.push(30);

    // Первый pop: ожидаем 30
    EXPECT_EQ(s.top(), 30);
    s.pop();

    // Второй pop: ожидаем 20
    EXPECT_EQ(s.top(), 20);
    s.pop();

    // Третий pop: ожидаем 10
    EXPECT_EQ(s.top(), 10);
    s.pop();

    // После трёх pop стек должен стать пустым
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);
}

// Защита от обращения к пустому стеку.
TEST(StackInt, ThrowsOnEmpty)
{
    Stack<int> s;

    // Для пустого стека top и pop считаются ошибочными операциями
    EXPECT_THROW(s.top(), out_of_range);
    EXPECT_THROW(s.pop(), out_of_range);
}

#pragma endregion

#pragma region String

// Стек корректно работает с типом string и сохраняет порядок элементов.
TEST(StackString, Basic)
{
    Stack<string> s;

    // Кладём две строки: hello и world
    s.push("hello");
    s.push("world");

    // На вершине должна быть последняя добавленная строка
    EXPECT_EQ(s.size(), 2u);
    EXPECT_EQ(s.top(), "world");

    // После pop вершиной становится hello
    s.pop();
    EXPECT_EQ(s.top(), "hello");
}

#pragma endregion

#pragma region Clear

// Метод clear удаляет все элементы
TEST(Stack, Clear)
{
    Stack<int> s;

    // Заполняем стек несколькими значениями
    s.push(1);
    s.push(2);
    s.push(3);

    // Вызываем clear и проверяем, что стек пуст
    s.clear();
    EXPECT_TRUE(s.empty());
    EXPECT_EQ(s.size(), 0u);

    // Дополнительно убеждаемся, что top на пустом стеке бросает исключение
    EXPECT_THROW(s.top(), out_of_range);
}

#pragma endregion

