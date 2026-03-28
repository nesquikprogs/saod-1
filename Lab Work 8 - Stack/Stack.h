#pragma once

#include <stdexcept>

#include "..\\Lab Work 6 - Dynamic Array\\DynamicArray.h"

/// <summary>
/// Шаблонный стек (LIFO), построенный поверх DynamicArray.
/// Основные сложности: push/pop — средний O(1), худший O(n), лучший O(1); top/empty/size — O(1); clear — O(1).
/// Худший O(n) у push: когда в DynamicArray буфер заполнен (size == capacity) — перевыделение и перенос n элементов.
/// Худший O(n) у pop: когда после удаления срабатывает сжатие буфера (size &lt; capacity/4) — reallocate с переносом оставшихся элементов.
/// </summary>
/// <typeparam name="T">Тип элементов, хранящихся в стеке.</typeparam>
template <typename T>
class Stack
{
private:

    #pragma region Fields

    /// <summary>
    /// Внутреннее хранилище элементов стека (динамический массив).
    /// </summary>
    DynamicArray<T> data_;
    
    #pragma endregion

public:

    #pragma region Constructor

    /// <summary>
    /// Создаёт пустой стек.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    Stack() = default;

    #pragma endregion

    #pragma region Methods

    /// <summary>
    /// Кладёт элемент на вершину стека (копирование).
    /// BigO: средний O(1), худший O(n), лучший O(1) (n = size()).
    /// Средний O(1) (амортизированно): при многократных push редкие перевыделения «размазываются» по дешёвым вставкам.
    /// Лучший O(1): в буфере есть свободное место.
    /// Худший O(n): буфер заполнен (size == capacity) - вызов reallocate.
    /// </summary>
    /// <param name="value">Элемент, который нужно поместить в стек.</param>
    void push(const T& value)
    {
        data_.push_back(value);
    }

    /// <summary>
    /// Кладёт элемент на вершину стека (перемещение).
    /// BigO: средний O(1), худший O(n), лучший O(1) (n = size()).
    /// Средний O(1) (амортизированно): как у push по копии - редкие перевыделения при росте буфера.
    /// Лучший O(1): size &lt; capacity — без перевыделения.
    /// Худший O(n): size == capacity — перевыделение и перенос n элементов.
    /// </summary>
    /// <param name="value">Элемент, который нужно поместить в стек (rvalue).</param>
    void push(T&& value)
    {
        data_.push_back(std::move(value));
    }

    /// <summary>
    /// Удаляет элемент с вершины стека.
    /// BigO: средний O(1), худший O(n), лучший O(1) (n = size() до удаления).
    /// Средний O(1) (амортизированно): дорогие reallocate при сжатии редки относительно числа pop.
    /// Лучший O(1): после удаления в DynamicArray сжатие не вызывается — только --size_.
    /// Худший O(n): срабатывает сжатие.
    /// </summary>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если стек пуст.
    /// </exception>
    void pop()
    {
        if (empty())
        {
            throw std::out_of_range("Stack::pop(): empty stack");
        }
        data_.pop_back();
    }

    /// <summary>
    /// Удаляет все элементы из стека.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    void clear() noexcept
    {
        data_.clear();
    }

    #pragma endregion

    #pragma region Access
    
    /// <summary>
    /// Возвращает ссылку на верхний элемент стека.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Изменяемая ссылка на верхний элемент.</returns>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если стек пуст.
    /// </exception>
    T& top()
    {
        if (empty())
        {
            throw std::out_of_range("Stack::top(): empty stack");
        }
        return data_[data_.size() - 1];
    }

    /// <summary>
    /// Возвращает константную ссылку на верхний элемент стека.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Константная ссылка на верхний элемент.</returns>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если стек пуст.
    /// </exception>
    const T& top() const
    {
        if (empty())
        {
            throw std::out_of_range("Stack::top() const: empty stack");
        }
        return data_[data_.size() - 1];
    }
    
    #pragma endregion

    #pragma region Info
    
    /// <summary>
    /// Показывает, пуст ли стек.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>true, если стек не содержит элементов, иначе false.</returns>
    bool empty() const noexcept
    {
        return data_.size() == 0;
    }

    /// <summary>
    /// Возвращает количество элементов в стеке.
    /// BigO: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Текущее число элементов.</returns>
    std::size_t size() const noexcept
    {
        return data_.size();
    }

    #pragma endregion
};

