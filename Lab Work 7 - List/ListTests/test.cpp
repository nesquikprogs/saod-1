#include "pch.h"

#include "../DoublyLinkedList.hpp"

using List = DoublyLinkedList<int>;

#pragma region BasicState

// Начальное состояние только что созданного списка
TEST(Basic, StartsEmpty)
{
    // Создаем пустой список
    List list;

    // У нового списка не должно быть элементов
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

// Список перестает быть пустым после вставки
TEST(Basic, NotEmpty)
{
    List list;

    // Добавляем один элемент в начало
    list.push_front(10);

    // Теперь список не должен быть пустым, а размер равен 1
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1u);
    EXPECT_EQ(list.at(0), 10);
}

#pragma endregion

#pragma region Insert

// Добавление нескольких элементов в голову списка
TEST(Insert, PushFront)
{
    List list;

    // Добавляем элементы в начало по очереди
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);

    // Последним добавленным в голову был 3, значит он стоит первым
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 3);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 1);
}

// Добавление нескольких элементов в конец списка
TEST (Insert, PushBack)
{
    List list;

    // Добавляем элементы в конец
    list.push_back(5);
    list.push_back(6);
    list.push_back(7);

    // Порядок в списке должен совпасть с порядком добавления
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 5);
    EXPECT_EQ(list.at(1), 6);
    EXPECT_EQ(list.at(2), 7);
}

// Вставка по индексу в середину списка
TEST(Insert, InsertAtMiddle)
{
    List list;

    // Заполняем список тремя элементами
    list.push_back(1); // индекс 0
    list.push_back(3); // индекс 1
    list.push_back(4); // индекс 2

    // Вставляем значение 2 на позицию 1
    list.insert_at(1, 2);

    // Проверяем итоговый порядок
    EXPECT_EQ(list.size(), 4u);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 3);
    EXPECT_EQ(list.at(3), 4);
}

// Вставка по индексу в конец списка через insert_at
TEST(Insert, InsertAtEnd)
{
    List list;

    // Добавляем два элемента
    list.push_back(10);
    list.push_back(20);

    // Вставляем третий элемент ровно в позицию size()
    const std::size_t index = list.size();
    list.insert_at(index, 30);

    // Проверяем, что новый элемент оказался в конце
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(1), 20);
    EXPECT_EQ(list.at(2), 30);
}

#pragma endregion

#pragma region Erase

// Удаление элемента из начала списка
TEST(Erase, PopFront)
{
    List list;

    // Заполняем список несколькими значениями
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Удаляем голову
    const bool removed = list.pop_front();
    EXPECT_TRUE(removed);

    // Теперь первым должен быть бывший второй элемент
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.at(0), 2);
    EXPECT_EQ(list.at(1), 3);
}

// Удаление элемента с конца списка
TEST(Erase, PopBack)
{
    List list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Удаляем последний элемент
    const bool removed = list.pop_back();
    EXPECT_TRUE(removed);

    // Список сократился, а последний элемент изменился
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.at(0), 10);
    EXPECT_EQ(list.at(1), 20);
}

// Удаление элемента по индексу из середины списка
TEST(Erase, EraseAtMiddle)
{
    List list;

    list.push_back(1); // 0
    list.push_back(2); // 1
    list.push_back(3); // 2
    list.push_back(4); // 3

    // Удаляем элемент с индексом 1 (значение 2)
    const bool erased = list.erase_at(1);
    EXPECT_TRUE(erased);

    // Проверяем итоговую последовательность
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 3);
    EXPECT_EQ(list.at(2), 4);
}

// Удаление по индексу за пределами списка
TEST(Erase, EraseAtOutOfRange)
{
    List list;

    list.push_back(1);
    list.push_back(2);

    // Пытаемся удалить элемент по слишком большому индексу
    const bool erased = list.erase_at(5);

    // Ожидаем, что ничего не произошло
    EXPECT_FALSE(erased);
    EXPECT_EQ(list.size(), 2u);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
}

// Удаление первого вхождения по значению
TEST(Erase, EraseFirstValueOK)
{
    List list;

    list.push_back(5);
    list.push_back(6);
    list.push_back(5);
    list.push_back(7);

    // Удаляем первое вхождение числа 5
    const bool erased = list.erase_first(5);
    EXPECT_TRUE(erased);

    // В списке должен остаться только один 5 (второй по счету)
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 6);
    EXPECT_EQ(list.at(1), 5);
    EXPECT_EQ(list.at(2), 7);
}

// Попытка удалить значение, которого нет в списке
TEST(Erase, EraseFirstValueNO)
{
    List list;

    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Значение 100 в списке отсутствует
    const bool erased = list.erase_first(100);
    EXPECT_FALSE(erased);

    // Список должен остаться без изменений
    EXPECT_EQ(list.size(), 3u);
    EXPECT_EQ(list.at(0), 1);
    EXPECT_EQ(list.at(1), 2);
    EXPECT_EQ(list.at(2), 3);
}

#pragma endregion

#pragma region Search

// Поиск индекса первого вхождения существующего элемента
TEST(Search, FindFirstIndexOK)
{
    List list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);

    // Ищем элемент, который точно есть в списке
    const long long idx = list.find_first_index(20);
    EXPECT_EQ(idx, 1);
}

// Поиск индекса для элемента, которого нет в списке
TEST(Search, FindFirstIndexNO)
{
    List list;

    list.push_back(10);
    list.push_back(20);

    // Ищем значение, которого нет
    const long long idx = list.find_first_index(99);
    EXPECT_EQ(idx, -1);
}

// Функция contains для положительного и отрицательного случаев
TEST(Search, Contains)
{
    List list;

    list.push_back(1);
    list.push_back(2);

    // 2 есть, 3 нет
    EXPECT_TRUE(list.contains(2));
    EXPECT_FALSE(list.contains(3));
}

#pragma endregion

#pragma region ClearOperation

// Полная очистка списка
TEST(Clear, Clear)
{
    List list;

    // Заполняем список несколькими элементами
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Полностью очищаем его
    list.clear();

    // После очистки список должен быть пустым
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

// Повторный вызов clear на уже пустом списке
TEST(Clear, ClearOnEmpty)
{
    List list;

    // Дважды вызываем очистку, не добавляя элементы
    list.clear();
    list.clear();

    // Список по-прежнему пуст
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0u);
}

#pragma endregion
