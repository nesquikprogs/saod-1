#include "pch.h"

#pragma region ConstructorAndBasic

// Проверка конструктора по умолчанию
TEST(DynamicArrayTest, ConstructorDefault) {
    DynamicArray<int> a; // создаём пустой массив
    EXPECT_EQ(a.size(), 0u); // размер должен быть 0
    EXPECT_EQ(a.capacity(), 0u); // ёмкость тоже 0
}

// Проверка конструктора с начальными резервом памяти
TEST(DynamicArrayTest, ConstructorWithCapacity) {
    DynamicArray<int> a(5); // резервируем место под 5 элементов
    EXPECT_EQ(a.size(), 0u); // размер всё ещё 0
    EXPECT_GE(a.capacity(), 5u); // ёмкость не меньше 5
}

#pragma endregion

#pragma region PushAndIndex

// Добавление нескольких элементов и доступ по индексу
TEST(DynamicArrayTest, PushAndIndex) {
    DynamicArray<int> a;
    a.push_back(10);
    a.push_back(20);
    a.push_back(30);

    EXPECT_EQ(a.size(), 3u); // проверяем размер
    EXPECT_EQ(a[0], 10); // проверяем значения
    EXPECT_EQ(a[1], 20);
    EXPECT_EQ(a[2], 30);
}

// Добавление большого количества элементов и рост ёмкости
TEST(DynamicArrayTest, PushMany) {
    DynamicArray<int> a;
    size_t oldCap = a.capacity(); // запоминаем старую ёмкость
    for (int i = 0; i < 50; ++i) {
        a.push_back(i); // добавляем много элементов
    }
    EXPECT_EQ(a.size(), 50u); // размер должен быть 50
    EXPECT_GT(a.capacity(), oldCap); // ёмкость должна увеличиться
    for (int i = 0; i < 50; ++i) {
        EXPECT_EQ(a[i], i); // значения на местах
    }
}

#pragma endregion

#pragma region PopAndShrink

// Удаление последнего элемента уменьшает размер
TEST(DynamicArrayTest, PopSize) {
    DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);
    size_t capBefore = a.capacity(); // сохраняем ёмкость до удаления

    a.pop_back(); // удаляем последний элемент
    EXPECT_EQ(a.size(), 2u); // размер стал 2
    EXPECT_EQ(a[0], 1);
    EXPECT_EQ(a[1], 2);
    EXPECT_LE(a.capacity(), capBefore); // ёмкость не должна расти
}

// Многократный pop_back до пустого массива
TEST(DynamicArrayTest, PopUntilEmpty) {
    DynamicArray<int> a;
    for (int i = 0; i < 10; ++i) {
        a.push_back(i); // заполняем массив
    }

    while (a.size() > 0) {
        a.pop_back(); // по одному удаляем элементы
    }

    EXPECT_EQ(a.size(), 0u); // массив стал пустым
}

#pragma endregion

#pragma region AtMethod

// Корректная работа метода at при верных индексах
TEST(DynamicArrayTest, AtValid) {
    DynamicArray<int> a;
    a.push_back(5);
    a.push_back(7);

    EXPECT_EQ(a.at(0), 5); // чтение по индексу
    EXPECT_EQ(a.at(1), 7);

    a.at(0) = 9; // запись по индексу
    EXPECT_EQ(a[0], 9);
}

// Метод at выбрасывает исключение при неверном индексе
TEST(DynamicArrayTest, AtBadIndex) {
    DynamicArray<int> a;
    a.push_back(1);

    EXPECT_THROW(a.at(1), out_of_range); // индекс == size
    EXPECT_THROW(a.at(100), out_of_range); // сильно выход за границы
}

#pragma endregion

#pragma region CopyAndAssign

// Копирующий конструктор делает глубокую копию
TEST(DynamicArrayTest, CopyConstructor) {
    DynamicArray<int> a;
    a.push_back(1);
    a.push_back(2);
    a.push_back(3);

    DynamicArray<int> b(a); // создаём копию
    EXPECT_EQ(b.size(), a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]); // элементы совпадают
    }

    b[0] = 100; // меняем копию
    EXPECT_EQ(a[0], 1); // исходный массив не меняется
    EXPECT_EQ(b[0], 100);
}

// Оператор присваивания тоже делает глубокую копию
TEST(DynamicArrayTest, CopyAssign) {
    DynamicArray<int> a;
    a.push_back(4);
    a.push_back(5);

    DynamicArray<int> b;
    b.push_back(1);

    b = a; // присваиваем один массив другому

    EXPECT_EQ(b.size(), a.size());
    for (size_t i = 0; i < a.size(); ++i) {
        EXPECT_EQ(a[i], b[i]); // элементы совпадают
    }

    b[0] = 200; // меняем копию
    EXPECT_EQ(a[0], 4); // исходный массив прежний
    EXPECT_EQ(b[0], 200);
}

#pragma endregion
