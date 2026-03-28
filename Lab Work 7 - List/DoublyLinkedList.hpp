#pragma once

/// комментарий про преимущества массива 

#include <cstddef>
#include <stdexcept>
#include <utility>

/// <summary>
/// Шаблонный двусвязный список.
/// </summary>
/// <typeparam name="T">Тип элементов, хранимых в списке</typeparam>
template <typename T>
class DoublyLinkedList final
{
private:

    #pragma region Node

    /// <summary>
    /// Внутренний узел списка: значение + ссылки на соседей.
    /// </summary>
    struct Node final
    {
        T value; // самозначение типа T
        Node* prev; // указатель на предыдущий узел
        Node* next; // указатель на следующий узел 

        /// <summary>
        /// Конструктор узла (копирование значения).
        /// </summary>
        explicit Node(const T& v) : value(v), prev(nullptr), next(nullptr) {}

        /// <summary>
        /// Конструктор узла (перемещение значения).
        /// </summary>
        explicit Node(T&& v) : value(std::move(v)), prev(nullptr), next(nullptr) {}
    };

    #pragma endregion

    #pragma region Fields

    // Указатель на голову списка (первый элемент)
    // Если список пустой, то здесь nullptr
    Node* head_;

    #pragma endregion

    #pragma region Helpers

    /// <summary>
    /// Подключает новый узел как голову.
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <param name="n">Узел, который станет новой головой</param>
    void link_new_head_(Node* n) noexcept
    {
        // У новой головы не может быть предыдущего узла
        n->prev = nullptr;
        // Следующий узел после новой головы - старая голова
        n->next = head_;

        // Если старая голова была, связываем ее назад с новой
        if (head_ != nullptr)
        {
            head_->prev = n;
        }

        // Обновляем указатель на голову списка
        head_ = n;
    }

    /// <summary>
    /// Поиск узла по индексу.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Индекс узла</param>
    /// <returns>Указатель на узел или nullptr, если индекс вне диапазона</returns>
    Node* node_at_(std::size_t index) const noexcept
    {
        // Стартуем с головы
        Node* cur = head_;
        std::size_t i = 0;

        // Идем вперед, пока не дойдем до нужного индекса и пока элемент существует
        while (cur != nullptr && i < index)
        {
            cur = cur->next;
            ++i;
        }

        // Вернется nullptr, если index >= size()
        return cur;
    }

    /// <summary>
    /// Вставляет уже созданный узел в позицию index.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Позиция вставки</param>
    /// <param name="n">Узел для вставки</param>
    /// <exception cref="std::out_of_range">Если индекс больше size()</exception>
    void insert_node_at_(std::size_t index, Node* n)
    {
        // Вставка в начало - отдельный самый быстрый случай
        if (index == 0)
        {
            link_new_head_(n); // указываем узел как голову 
            return;
        }

        // Ищем узел, который сейчас находится на позиции index
        Node* cur = head_;
        std::size_t i = 0; // текущий идекс который сравниваем с искомым index
        while (cur != nullptr && i < index)
        {
            cur = cur->next;
            ++i;
        }

        // Если дошли до конца ровно на index значит вставка в конец
        if (cur == nullptr && i == index)
        {
            Node* tail = head_;

            // Доходим до последнего узла 
            while (tail->next != nullptr)
            {
                tail = tail->next;
            }

            // Подключаем новый узел после хвоста
            n->next = nullptr;
            n->prev = tail;
            tail->next = n;
            return;
        }

        // Иначе index слишком большой
        if (cur == nullptr)
        {
            throw std::out_of_range("DoublyLinkedList::insert_at: index out of range");
        }

        // Вставка в середину: вставляем n перед cur
        Node* left = cur->prev;
        n->next = cur;
        n->prev = left;
        left->next = n;
        cur->prev = n;
    }

    #pragma endregion

public:
    
    #pragma region ConstructorsAndDestructor

    /// <summary>
    /// Создает пустой список.
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    DoublyLinkedList() noexcept : head_(nullptr) {}

    /// <summary>
    /// Освобождает все узлы списка.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    ~DoublyLinkedList() { clear(); }

    /// <summary>
    /// Копирующий конструктор запрещен.
    /// </summary>
    DoublyLinkedList(const DoublyLinkedList&) = delete;

    /// <summary>
    /// Копирующее присваивание запрещено.
    /// </summary>
    DoublyLinkedList& operator=(const DoublyLinkedList&) = delete;

    /// <summary>
    /// Перемещающий конструктор.
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <param name="other">Cписок-источник, узлы которо передаются новому объекту</param>
    DoublyLinkedList(DoublyLinkedList&& other) noexcept : head_(other.head_)
    {
        // Источник делаем пустым, чтобы он не владел узлами
        other.head_ = nullptr;
    }

    /// <summary>
    /// Перемещающее присваивание.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="other">Cписок, узлы которо передаются новому объекту</param>
    /// <returns>Ссылка на текущий объект списка</returns>
    DoublyLinkedList& operator=(DoublyLinkedList&& other) noexcept
    {
        // Самоприсваивание ничего не меняет
        if (this == &other)
        {
            return *this;
        }

        // Сначала очищаем текущие узлы
        clear();
        // Потом принимаем узлы другого списка
        head_ = other.head_;
        // Источник оставляем пустым
        other.head_ = nullptr;
        return *this;
    }

    #pragma endregion

    #pragma region SizeAndState

    /// <summary>
    /// Проверяет, пуст ли список.
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <returns>true, если список пуст; иначе false</returns>
    bool empty() const noexcept
    {
        // Если нет головы, значит список пуст
        return head_ == nullptr;
    }

    /// <summary>
    /// Возвращает количество элементов списка.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <returns>Количество элементов</returns>
    std::size_t size() const noexcept
    {
        // Размер считаем обходом списка
        std::size_t count = 0;
        Node* cur = head_;
        while (cur != nullptr)
        {
            ++count;
            cur = cur->next;
        }
        return count;
    }

    #pragma endregion

    #pragma region Search

    /// <summary>
    /// Ищет первое вхождение значения.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="value">Искомое значение</param>
    /// <returns>Индекс первого вхождения или -1, если не найдено</returns>
    long long find_first_index(const T& value) const noexcept
    {
        // Проходим по списку по порядку
        long long idx = 0; // текущий индекс у проверяемого узла
        Node* cur = head_;
        while (cur != nullptr)
        {
            // Если совпало - сразу возвращаем индекс
            if (cur->value == value)
            {
                return idx;
            }
            ++idx;
            cur = cur->next;
        }

        // Ничего не нашли
        return -1;
    }

    /// <summary>
    /// Проверяет наличие значения в списке.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="value">Искомое значение</param>
    /// <returns>true, если найдено; иначе false</returns>
    bool contains(const T& value) const noexcept
    {
        // Используем уже готовый поиск индекса
        return find_first_index(value) != -1;
    }

    #pragma endregion

    #pragma region Insert

    /// <summary>
    /// Вставляет элемент в начало (копированием).
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <param name="value">Значение для вставки</param>
    void push_front(const T& value)
    {
        // Создаем новый узел
        Node* n = new Node(value);
        // Делаем его новой головой
        link_new_head_(n);
    }

    /// <summary>
    /// Вставляет элемент в начало (перемещением).
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <param name="value">Значение для вставки</param>
    void push_front(T&& value)
    {
        // Создаем узел с move
        Node* n = new Node(std::move(value));
        // Подключаем его в голову
        link_new_head_(n);
    }

    /// <summary>
    /// Вставляет элемент в конец (копированием).
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="value">Значение для вставки</param>
    void push_back(const T& value)
    {
        // Вставка в конец = вставка по индексу size()
        insert_at(size(), value);
    }

    /// <summary>
    /// Вставляет элемент в конец (перемещением).
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="value">Значение для вставки</param>
    void push_back(T&& value)
    {
        // Аналогично, но с перемещением
        insert_at(size(), std::move(value));
    }

    /// <summary>
    /// Вставляет элемент по индексу (копированием).
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Позиция вставки, диапазон [0, size()]</param>
    /// <param name="value">Значение для вставки</param>
    void insert_at(std::size_t index, const T& value)
    {
        // Создаем узел заранее
        Node* n = new Node(value);
        try
        {
            // Вставляем его в нужную позицию
            insert_node_at_(index, n);
        }
        catch (...)
        {
            // Если индекс неверный и выброшено исключение,
            // освобождаем выделенную память
            delete n;
            throw; // повторно пробрасываем исходное исключение
        }
    }

    /// <summary>
    /// Вставляет элемент по индексу (перемещением).
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Позиция вставки, диапазон [0, size()]</param>
    /// <param name="value">Значение для вставки</param>
    void insert_at(std::size_t index, T&& value)
    {
        // Создаем узел через move
        Node* n = new Node(std::move(value));
        try
        {
            // Вставляем узел в список
            insert_node_at_(index, n);
        }
        catch (...)
        {
            // Чистим память, если вставка не удалась
            delete n;
            throw; // повторно пробрасываем исходное исключение
        }
    }

    #pragma endregion

    #pragma region Erase

    /// <summary>
    /// Удаляет элемент из начала списка.
    /// Big-O: средний O(1), худший O(1), лучший O(1)
    /// </summary>
    /// <returns>true, если удаление выполнено; false, если список пуст</returns>
    bool pop_front() noexcept
    {
        // Если список пустой - ничего не делаем
        if (head_ == nullptr)
        {
            return false;
        }

        // Сохраняем старую голову, чтобы освободить память
        Node* old = head_;
        // Новая голова - следующий узел
        head_ = head_->next;

        // Если список не пуст
        if (head_ != nullptr)
        {
            head_->prev = nullptr; // исправляем prev у новой головы
        }

        // Удаляем старый первый узел
        delete old;
        return true;
    }

    /// <summary>
    /// Удаляет элемент из конца списка.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <returns>true, если удаление выполнено; false, если список пуст</returns>
    bool pop_back() noexcept
    {
        // Пустой список
        if (head_ == nullptr)
        {
            return false;
        }

        // Если элемент только один
        if (head_->next == nullptr)
        {
            delete head_;
            head_ = nullptr;
            return true;
        }

        // Ищем хвост
        Node* tail = head_;
        while (tail->next != nullptr)
        {
            tail = tail->next;
        }

        // Отцепляем хвост от списка
        tail->prev->next = nullptr;
        // Удаляем хвостовой узел
        delete tail;
        return true;
    }

    /// <summary>
    /// Удаляет элемент по индексу.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Индекс удаляемого элемента</param>
    /// <returns>true, если элемент удален; false, если индекс вне диапазона или список пуст</returns>
    bool erase_at(std::size_t index) noexcept
    {
        // Нет элементов - удалять нечего
        if (head_ == nullptr)
        {
            return false;
        }

        // Удаление первого элемента - отдельный случай
        if (index == 0)
        {
            return pop_front();
        }

        // Доходим до узла с индексом index
        Node* cur = head_;
        std::size_t i = 0; // текущий индекс узла который будем наращивать до нужного
        while (cur != nullptr && i < index)
        {
            cur = cur->next;
            ++i;
        }

        // Индекс не существует(дошли до конца списка раньше чем достигли i == index)
        if (cur == nullptr)
        {
            return false;
        }

        // Перешиваем соседей вокруг cur, 
        // чтобы после удаления связи между левым и правым соседями были правильными
        if (cur->prev != nullptr) 
        {
            cur->prev->next = cur->next;
        }
        if (cur->next != nullptr)
        {
            cur->next->prev = cur->prev;
        }

        // Удаляем сам узел
        delete cur;
        return true;
    }

    /// <summary>
    /// Удаляет первое вхождение значения.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="value">Значение для удаления</param>
    /// <returns>true, если элемент найден и удален; иначе false</returns>
    bool erase_first(const T& value) noexcept
    {
        // Ищем первое совпадение по значению
        Node* cur = head_;
        while (cur != nullptr)
        {
            if (cur->value == value) // если нашли
            {
                // Если совпадение в голове
                if (cur->prev == nullptr)
                {
                    return pop_front();
                }

                // Иначе вырезаем узел из середины или хвоста
                cur->prev->next = cur->next; 
                if (cur->next != nullptr) // если элемент в середине(есть сосед справа)
                {
                    cur->next->prev = cur->prev;
                }
                delete cur;
                return true;
            }
            cur = cur->next; // если не нашли
        }

        // Не нашли такое значение
        return false;
    }

    /// <summary>
    /// Удаляет все элементы списка.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    void clear() noexcept
    {
        // Идем от головы к хвосту и удаляем каждый узел
        Node* cur = head_;
        while (cur != nullptr)
        {
            // Сохраняем следующий, т.к. текущий сейчас удалим
            Node* next = cur->next;
            delete cur;
            cur = next;
        }

        // После очистки голова пустая
        head_ = nullptr;
    }

    #pragma endregion

    #pragma region Access

    /// <summary>
    /// Возвращает ссылку на элемент по индексу с проверкой границ.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Индекс элемента</param>
    /// <returns>Ссылка на элемент</returns>
    /// <exception cref="std::out_of_range">Если индекс вне диапазона</exception>
    T& at(std::size_t index)
    {
        // Получаем узел по индексу
        Node* n = node_at_(index);
        if (n == nullptr)
        {
            // Индекс неверный
            throw std::out_of_range("DoublyLinkedList::at: index out of range");
        }

        // Возвращаем ссылку на значение
        return n->value;
    }

    /// <summary>
    /// Возвращает константную ссылку на элемент по индексу с проверкой границ.
    /// Big-O: средний O(n), худший O(n), лучший O(1)
    /// </summary>
    /// <param name="index">Индекс элемента</param>
    /// <returns>Константная ссылка на элемент</returns>
    /// <exception cref="std::out_of_range">Если индекс вне диапазона</exception>
    const T& at(std::size_t index) const
    {
        // Полностью та же логика, но для const-объекта
        Node* n = node_at_(index);
        if (n == nullptr)
        {
            throw std::out_of_range("DoublyLinkedList::at: index out of range");
        }
        return n->value;
    }

    #pragma endregion

};

