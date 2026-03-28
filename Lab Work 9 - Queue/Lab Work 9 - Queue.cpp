#include <iostream>
#include "Queue.h"

using namespace std;

int main()
{
    #pragma region Int

    // Создаём очередь целых чисел и кладём в неё несколько значений
    Queue<int> intQueue(5);
    intQueue.enqueue(10);
    intQueue.enqueue(20);
    intQueue.enqueue(30);

    // Показываем размер очереди и первый элемент
    cout << "intQueue size: " << intQueue.size() << "\n";
    cout << "Front: " << intQueue.front() << "\n";

    // Удаляем первый элемент и снова выводим фронт
    cout << "Dequeue: " << intQueue.dequeue() << "\n";
    cout << "After dequeue, front: " << intQueue.front() << "\n";

    #pragma endregion

    #pragma region String

    // Демонстрация работы с std::string
    Queue<string> stringQueue(3);
    stringQueue.enqueue("first");
    stringQueue.enqueue("second");

    cout << "stringQueue size: " << stringQueue.size() << "\n";
    cout << "Front element: " << stringQueue.front() << "\n";

    // Извлекаем элемент и показываем новый фронт
    cout << "Dequeue: " << stringQueue.dequeue() << "\n";
    cout << "After dequeue, front: " << stringQueue.front() << "\n";

    #pragma endregion

    return 0;
}
