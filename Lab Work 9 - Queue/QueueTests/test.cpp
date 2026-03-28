#include "pch.h"
#include "gtest/gtest.h"

#include "../Queue.h"

#pragma region Basic

// Новая очередь пустая, size == 0
TEST(QueueInt, Empty)
{
    // Создаём очередь с ёмкостью 3
    Queue<int> q(3);
    // Проверяем начальное состояние
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0u);
}

// enqueue увеличивает size и не меняет front
TEST(QueueInt, Enqueue)
{
    // Создаём очередь с ёмкостью 3
    Queue<int> q(3);
    // Добавляем первый элемент
    q.enqueue(10);
    // Проверяем, что очередь стала непустой
    EXPECT_FALSE(q.isEmpty());
    EXPECT_EQ(q.size(), 1u);
    EXPECT_EQ(q.front(), 10);
    // Добавляем второй элемент, front должен остаться прежним
    q.enqueue(20);
    EXPECT_EQ(q.size(), 2u);
    EXPECT_EQ(q.front(), 10);
}

// dequeue возвращает элементы в порядке FIFO
TEST(QueueInt, DequeueFifo)
{
    // Создаём очередь с ёмкостью 5
    Queue<int> q(5);
    // Добавляем элементы в известном порядке
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    // Извлекаем и проверяем FIFO
    EXPECT_EQ(q.dequeue(), 1);
    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_EQ(q.dequeue(), 3);
    // После извлечения всех элементов очередь должна быть пустой
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0u);
}

#pragma endregion

#pragma region CircularBuffer

// Проверка кругового буфера: после dequeue и enqueue порядок сохраняется
TEST(QueueInt, Circular)
{
    // Создаём очередь ёмкостью 3
    Queue<int> q(3);
    // Заполняем очередь полностью
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    // Освобождаем одну ячейку
    EXPECT_EQ(q.dequeue(), 1);
    // Добавляем новый элемент, он должен встать в освободившееся место по кругу
    q.enqueue(4);
    // Проверяем, что порядок элементов сохраняется
    EXPECT_EQ(q.dequeue(), 2);
    EXPECT_EQ(q.dequeue(), 3);
    EXPECT_EQ(q.dequeue(), 4);
    // В конце очередь должна быть пустой
    EXPECT_TRUE(q.isEmpty());
}

#pragma endregion

#pragma region Capacity

// isFull становится true при заполнении ёмкости
TEST(QueueInt, IsFull)
{
    // Создаём очередь ёмкостью 2
    Queue<int> q(2);
    // До заполнения isFull должен быть false
    EXPECT_FALSE(q.isFull());
    // Заполняем очередь
    q.enqueue(5);
    q.enqueue(6);
    // После заполнения isFull должен быть true
    EXPECT_TRUE(q.isFull());
    EXPECT_EQ(q.size(), 2u);
}

#pragma endregion

#pragma region Types

// Очередь работает со string и сохраняет FIFO
TEST(QueueString, Basic)
{
    // Создаём очередь строк
    Queue<std::string> q(3);
    // Добавляем две строки
    q.enqueue("hello");
    q.enqueue("world");
    // Проверяем размер и порядок FIFO
    EXPECT_EQ(q.size(), 2u);
    EXPECT_EQ(q.front(), "hello");
    EXPECT_EQ(q.dequeue(), "hello");
    EXPECT_EQ(q.front(), "world");
}

// enqueue с перемещением работает для string
TEST(QueueString, MoveEnqueue)
{
    // Создаём очередь строк
    Queue<std::string> q(2);
    // Готовим строку и перемещаем её в очередь
    std::string s = "move";
    q.enqueue(std::move(s));
    // После перемещения в очереди должна быть строка "move"
    EXPECT_EQ(q.front(), "move");
    EXPECT_EQ(q.size(), 1u);
}

// Очередь работает с double и сохраняет FIFO
TEST(QueueDouble, Basic)
{
    // Создаём очередь чисел double
    Queue<double> q(3);
    // Добавляем два значения
    q.enqueue(1.5);
    q.enqueue(2.5);
    // Проверяем порядок FIFO и значения
    EXPECT_DOUBLE_EQ(q.front(), 1.5);
    EXPECT_DOUBLE_EQ(q.dequeue(), 1.5);
    EXPECT_DOUBLE_EQ(q.dequeue(), 2.5);
    // После извлечения очередь должна быть пустой
    EXPECT_TRUE(q.isEmpty());
    EXPECT_EQ(q.size(), 0u);
}

#pragma endregion

#pragma region Exceptions

// enqueue на полной очереди бросает overflow_error
TEST(QueueException, EnqueueOnFull)
{
    // Создаём очередь ёмкостью 1 и заполняем её
    Queue<int> q(1);
    q.enqueue(7);
    // Добавление в полную очередь должно бросать исключение
    EXPECT_THROW(q.enqueue(8), std::overflow_error);
}

// dequeue на пустой очереди бросает underflow_error
TEST(QueueException, DequeueOnEmpty)
{
    // Создаём пустую очередь
    Queue<int> q(3);
    // Извлечение из пустой очереди должно бросать исключение
    EXPECT_THROW(q.dequeue(), std::underflow_error);
}

// front на пустой очереди бросает underflow_error
TEST(QueueException, FrontOnEmpty)
{
    // Создаём пустую очередь
    Queue<int> q(3);
    // Просмотр первого элемента пустой очереди должен бросать исключение
    EXPECT_THROW(q.front(), std::underflow_error);
}

#pragma endregion