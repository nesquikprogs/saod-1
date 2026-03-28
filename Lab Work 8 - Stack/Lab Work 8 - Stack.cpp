#include <iostream>
#include "Stack.h"

using namespace std;

int main()
{

    #pragma region Int

    // Создаём стек целых чисел и кладём в него несколько значений
    Stack<int> intStack;
    intStack.push(10);
    intStack.push(20);
    intStack.push(30);

    // Показываем размер стека и верхний элемент
    cout << "intStack size: " << intStack.size() << "\n";
    cout << "Top element: " << intStack.top() << "\n";

    // Удаляем верхний элемент и снова выводим вершину
    intStack.pop();
    cout << "After pop, top: " << intStack.top() << "\n";

    #pragma endregion

    #pragma region String

    // Демонстрация работы с string
    Stack<string> stringStack;
    stringStack.push("hello");
    stringStack.push("world");

    cout << "stringStack size: " << stringStack.size() << "\n";
    cout << "Top element: " << stringStack.top() << "\n";
    
    #pragma endregion
    
    return 0;
}

