#pragma once

#include <cstddef>
#include <stdexcept>
#include <utility>

#include <cassert>

using namespace std;

/// <summary>
/// Простой шаблон динамического массива, похожий по идее на vector.
/// </summary>
/// <typeparam name="T">Тип элементов, которые будут храниться в массиве</typeparam>
template <typename T>
class DynamicArray {
private:

    #pragma region Fields

    // Указатель на динамически выделенный буфер (указатель на начало блока памяти)
    T* data_;
    // Текущее количество элементов в массиве
    size_t size_;
    // Выделенная ёмкость (сколько элементов можно хранить без перевыделения)
    size_t capacity_;

    #pragma endregion

    #pragma region Helpers

    /// <summary>
    /// Перевыделяет внутренний буфер под указанную ёмкость и переносит элементы.
    /// Сложность: средний O(n), худший O(n), лучший O(1) (n = size_).
    /// Лучший случай: size_ == 0.
    /// </summary>
    /// <param name="new_capacity">Новая ёмкость массива (количество элементов, под которое нужно выделить память)</param>
    void reallocate(size_t new_capacity) {
        // Выделяем новый буфер нужного размера
        T* new_data = new T[new_capacity];
        assert(size_ <= new_capacity);
        // Переносим существующие элементы в новый буфер
        for (size_t i = 0; i < size_; ++i) {
            new_data[i] = move(data_[i]);
        }
        // Освобождаем старую память и переключаемся на новый буфер
        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    #pragma endregion

public:

    #pragma region ConstructorsAndDestructor

    /// <summary>
    /// Создаёт пустой динамический массив без выделения памяти.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    DynamicArray()
        : data_(nullptr), size_(0), capacity_(0) {}

    /// <summary>
    /// Создаёт пустой массив и сразу резервирует память под указанное количество элементов.
    /// Сложность: средний O(k), худший O(k), лучший O(1) (k = initial_capacity).
    /// Лучший случай: initial_capacity == 0 — буфер не выделяется.
    /// </summary>
    /// <param name="initial_capacity">Начальная ёмкость (сколько элементов можно будет положить без перевыделения памяти)</param>
    explicit DynamicArray(size_t initial_capacity)
        : data_(nullptr), size_(0), capacity_(0) {
        // Если передали положительную ёмкость — сразу резервируем память
        if (initial_capacity > 0) {
            data_ = new T[initial_capacity]; // выделение буфера с initial_capacity ёмкостью 
            capacity_ = initial_capacity;
        }
    }

    /// <summary>
    /// Освобождает динамически выделенную память массива.
    /// Сложность: средний O(c), худший O(c), лучший O(1) (c = capacity_).
    /// Лучший случай: data_ == nullptr — delete[] nullptr не освобождает реальный буфер.
    /// </summary>
    ~DynamicArray() {
        // Освобождаем буфер, если он был выделен
        delete[] data_;
    }

    #pragma endregion

    #pragma region CopyAndMove

    /// <summary>
    /// Копирующий конструктор. Создаёт новый массив как глубокую копию другого.
    /// Сложность: средний O(n), худший O(n), лучший O(1) (n = size_).
    /// Лучший случай: other.size_ == 0 — цикл копирования элементов не выполняется (остаётся выделение буфера, если other.capacity_ &gt; 0).
    /// </summary>
    /// <param name="other">Исходный массив, из которого копируются элементы</param>
    DynamicArray(const DynamicArray& other)
        : data_(nullptr), size_(other.size_), capacity_(other.capacity_) {
        if (capacity_ > 0) {
            // Выделяем свой буфер нужной ёмкости
            data_ = new T[capacity_];
            // Поэлементно копируем значения из other
            for (size_t i = 0; i < size_; ++i) {
                data_[i] = other.data_[i];
            }
        }
    }

    /// <summary>
    /// Оператор копирующего присваивания. Заменяет содержимое текущего массива копией из другого массива.
    /// Сложность: средний O(n), худший O(n), лучший O(1) (n = other.size_).
    /// Лучший случай: самоприсваивание (this == &amp;other) — сразу return *this, без создания копии и без swap.
    /// </summary>
    /// <param name="other">Массив, содержимое которого нужно скопировать</param>
    /// <returns>Ссылку на текущий массив после присваивания</returns>
    DynamicArray& operator=(const DynamicArray& other) {
        if (this == &other) {
            // Защита от самоприсваивания
            return *this;
        }

        // Создаём временную копию (copy-swap)
        DynamicArray temp(other);
        // Меняем содержимое текущего объекта и временного местами
        swap(data_, temp.data_);
        swap(size_, temp.size_);
        swap(capacity_, temp.capacity_);
        return *this;
    }

    /// <summary>
    /// Перемещающий конструктор. Забирает ресурсы у временного массива без копирования элементов.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// Все случаи O(1): копируются только указатель и два числа, без перевыделения и без цикла по элементам.
    /// </summary>
    /// <param name="other">Временный массив, ресурсы которого будут переданы</param>
    DynamicArray(DynamicArray&& other) noexcept
        : data_(other.data_), size_(other.size_), capacity_(other.capacity_) {
        // Обнуляем источник, чтобы он больше не владел памятью
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
    }

    /// <summary>
    /// Перемещающий оператор присваивания. Освобождает свои ресурсы и забирает ресурсы у другого массива.
    /// Сложность: средний O(c), худший O(c), лучший O(1) (c = capacity_ текущего объекта).
    /// Лучший случай: самоприсваивание (this == &other).
    /// Также O(1) по старому буферу, если у текущего объекта data_ == nullptr (delete[] nullptr).
    /// </summary>
    /// <param name="other">Массив, ресурсы которого нужно перенести</param>
    /// <returns>Ссылку на текущий массив после присваивания</returns>
    DynamicArray& operator=(DynamicArray&& other) noexcept {
        if (this == &other) {
            return *this;
        }

        // Освобождаем свои текущие ресурсы
        delete[] data_;

        // Забираем указатель и параметры у other
        data_ = other.data_;
        size_ = other.size_;
        capacity_ = other.capacity_;

        // Обнуляем other
        other.data_ = nullptr;
        other.size_ = 0;
        other.capacity_ = 0;
        return *this;
    }

    #pragma endregion

    #pragma region GetSizeAndCapacity

    /// <summary>
    /// Возвращает текущее количество элементов, фактически хранящихся в массиве.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Число элементов в массиве</returns>
    size_t size() const noexcept {
        // Просто возвращаем текущее количество элементов
        return size_;
    }

    /// <summary>
    /// Возвращает текущую ёмкость массива (сколько элементов можно разместить без перевыделения памяти).
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <returns>Ёмкость массива в элементах</returns>
    size_t capacity() const noexcept {
        // Возвращаем, сколько элементов помещается в текущий буфер
        return capacity_;
    }

    #pragma endregion

    #pragma region Modifiers

    /// <summary>
    /// Добавляет элемент в конец массива (по константной ссылке).
    /// При нехватке места увеличивает внутреннюю ёмкость.
    /// Сложность: средний O(1), худший O(n), лучший O(1) (n = size_).
    /// Лучший случай: size_ < capacity_ — место в буфере есть.
    /// </summary>
    /// <param name="value">Элемент, который нужно добавить</param>
    void push_back(const T& value) {
        // Если буфер заполнен — увеличиваем ёмкость
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        // Записываем новый элемент в конец и увеличиваем размер
        data_[size_] = value;
        ++size_;
    }

    /// <summary>
    /// Добавляет элемент в конец массива, принимая его как rvalue-ссылку.
    /// Использует перемещение вместо копирования, если это возможно.
    /// Сложность: средний O(1), худший O(n), лучший O(1) (n = size_).
    /// Лучший случай: size_ < capacity_.
    /// </summary>
    /// <param name="value">Элемент, который нужно переместить в массив</param>
    void push_back(T&& value) {
        // При заполненном буфере увеличиваем ёмкость
        if (size_ == capacity_) {
            size_t new_capacity = (capacity_ == 0) ? 1 : capacity_ * 2;
            reallocate(new_capacity);
        }
        // Перемещаем значение в конец массива
        data_[size_] = move(value);
        ++size_;
    }

    /// <summary>
    /// Удаляет последний элемент массива. При заметном уменьшении размера может уменьшить ёмкость.
    /// Сложность: средний O(1), худший O(n), лучший O(1) (n = size_ до удаления).
    /// Худший случай: срабатывает сжатие буфера — вызов reallocate.
    /// </summary>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если массив пуст (size_ == 0).
    /// </exception>
    void pop_back() {
        // Проверка на пустой массив
        if (size_ == 0) {
            throw std::out_of_range("DynamicArray is empty");
        }
        // Логически удаляем последний элемент, уменьшая размер
        --size_;

        // Если элементов стало намного меньше, чем ёмкость и сам буфер выделен
        if (capacity_ > 0 && size_ < capacity_ / 4) {
            size_t new_capacity = capacity_ / 2; // ёмкость сокращается в два раза
            // Если после уменьщения ёмокости она стала меньше размера
            if (new_capacity < size_) {
                new_capacity = size_; // подгоняем ёмкость поднимаем до размера
            }
            reallocate(new_capacity); // уменьшаем буфер и переносим элементы
        }
    }

    /// <summary>
    /// Удаляет все элементы логически.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    void clear() noexcept {
        size_ = 0;
    }

    #pragma endregion

    #pragma region Access

    /// <summary>
    /// Возвращает ссылку на элемент по индексу без проверки границ.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <param name="index">Индекс элемента в диапазоне [0, size())</param>
    /// <returns>Ссылка на элемент массива по указанному индексу</returns>
    T& operator[](size_t index) {
        // Доступ к элементу без проверки границ
        return data_[index];
    }

    /// <summary>
    /// Возвращает константную ссылку на элемент по индексу без проверки границ.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <param name="index">Индекс элемента в диапазоне [0, size())</param>
    /// <returns>Константная ссылка на элемент массива по указанному индексу</returns>
    const T& operator[](size_t index) const {
        return data_[index];
    }

    /// <summary>
    /// Возвращает ссылку на элемент по индексу с проверкой границ.
    /// При неверном индексе выбрасывает исключение `std::out_of_range`.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если index >= size().
    /// </exception>
    /// <param name="index">Индекс элемента в диапазоне [0, size())</param>
    /// <returns>Ссылка на элемент массива по указанному индексу</returns>
    T& at(size_t index) {
        // Проверяем корректность индекса
        if (index >= size_) {
            throw out_of_range("index out of range");
        }
        // Если индекс корректный — возвращаем ссылку на элемент
        return data_[index];
    }

    /// <summary>
    /// Возвращает константную ссылку на элемент по индексу с проверкой границ.
    /// При неверном индексе выбрасывает исключение `std::out_of_range`.
    /// Сложность: средний O(1), худший O(1), лучший O(1).
    /// </summary>
    /// <exception cref="std::out_of_range">
    /// Выбрасывается, если index >= size().
    /// </exception>
    /// <param name="index">Индекс элемента в диапазоне [0, size())</param>
    /// <returns>Константная ссылка на элемент массива по указанному индексу</returns>
    const T& at(size_t index) const {
        // Проверка индекса для константной версии
        if (index >= size_) {
            throw out_of_range("index out of range");
        }
        // Возвращаем константную ссылку на элемент
        return data_[index];
    }

    #pragma endregion

};

