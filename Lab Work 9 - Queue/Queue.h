#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include "..\\Lab Work 6 - Dynamic Array\\DynamicArray.h"

/// <summary>
/// Шаблонная очередь (FIFO), построенная поверх DynamicArray с использованием кругового буфера.
/// </summary>
/// <typeparam name="T">Тип элементов, хранящихся в очереди.</typeparam>
template <typename T>
class Queue
{
private:

    #pragma region Fields

    /// <summary>
    /// Внутреннее хранилище элементов очереди (динамический массив).
    /// </summary>
    DynamicArray<T> buffer_;

    /// <summary>
    /// Индекс первого (фронтального) элемента в круговом буфере.
    /// </summary>
    std::size_t head_;
        
    /// <summary>
    /// Индекс позиции сразу после последнего элемента (хвост очереди).
    /// </summary>
    std::size_t tail_;

    /// <summary>
    /// Текущее количество элементов в очереди.
    /// </summary>
    std::size_t count_;

    #pragma endregion

public:

    #pragma region Constructor

    /// <summary>
    /// Создаёт пустую очередь с заданной максимальной ёмкостью.
    /// Сложность: средний O(capacity), худший O(capacity), лучший O(capacity).
    /// </summary>
    /// <param name="capacity">Максимальное число элементов в очереди.</param>
    /// <exception cref="std::invalid_argument">Если capacity == 0.</exception>
    explicit Queue(std::size_t capacity = 100)
        : buffer_(capacity),
          head_(0),
          tail_(0),
          count_(0)
    {
        if (capacity == 0)
        {
            throw std::invalid_argument("Queue capacity must be greater than 0");
        }
    }

    #pragma endregion

    #pragma region Modifiers

    /// <summary>
    /// Добавляет элемент в конец очереди.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить.</param>
    /// <exception cref="std::overflow_error">Если очередь заполнена (isFull() == true).</exception>
    void enqueue(const T& value)
    {
        if (isFull())
        {
            throw std::overflow_error("Queue is full");
        }
        buffer_[tail_] = value;
        tail_ = (tail_ + 1) % buffer_.capacity();
        ++count_;
    }

    /// <summary>
    /// Добавляет элемент в конец очереди (перемещение).
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить (rvalue).</param>
    /// <exception cref="std::overflow_error">Если очередь заполнена (isFull() == true).</exception>
    void enqueue(T&& value)
    {
        if (isFull())
        {
            throw std::overflow_error("Queue is full");
        }
        buffer_[tail_] = std::move(value);
        tail_ = (tail_ + 1) % buffer_.capacity();
        ++count_;
    }

    /// <summary>
    /// Извлекает элемент из начала очереди и удаляет его.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Возвращаемое значение элемента из начала очереди.</returns>
    /// <exception cref="std::underflow_error">Если очередь пустая (isEmpty() == true).</exception>
    T dequeue()
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        T value = std::move(buffer_[head_]);
        head_ = (head_ + 1) % buffer_.capacity();
        --count_;
        return value;
    }

    #pragma endregion

    #pragma region Access

    /// <summary>
    /// Возвращает значение элемента в начале очереди без удаления.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Значение первого элемента очереди.</returns>
    /// <exception cref="std::underflow_error">Если очередь пустая (isEmpty() == true).</exception>
    T front() const
    {
        if (isEmpty())
        {
            throw std::underflow_error("Queue is empty");
        }
        return buffer_[head_];
    }

    #pragma endregion

    #pragma region Info

    /// <summary>
    /// Проверяет, пуста ли очередь.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>true, если очередь не содержит элементов, иначе false.</returns>
    bool isEmpty() const noexcept
    {
        return count_ == 0;
    }

    /// <summary>
    /// Проверяет, заполнена ли очередь.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>true, если очередь заполнена полностью, иначе false.</returns>
    bool isFull() const noexcept
    {
        return count_ == buffer_.capacity();
    }

    /// <summary>
    /// Возвращает текущее количество элементов в очереди.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Число элементов в очереди.</returns>
    std::size_t size() const noexcept
    {
        return count_;
    }

    /// <summary>
    /// Возвращает максимальную ёмкость очереди.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Максимальное число элементов, которое может хранить очередь.</returns>
    std::size_t capacity() const noexcept
    {
        return buffer_.capacity();
    }

    #pragma endregion
};

