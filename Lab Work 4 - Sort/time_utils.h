#ifndef TIME_UTILS_H
#define TIME_UTILS_H

#include <chrono>

using namespace std;          
using namespace std::chrono;   

/// <summary>
/// Шаблонная функция для измерения времени выполнения переданного кода в миллисекундах
/// </summary>
/// <typeparam name="Func">Любой тип, который можно назвать как функцию</typeparam>
/// <typeparam name="...Args">Возможность переделать сколько угодно параментров</typeparam>
/// <param name="func">Имя функции время которой нужно измерить</param>
/// <param name="...args">Агументы которые надо передавать в функцию</param>
/// <returns>Количество миллисекунд</returns> 
template<typename Func, typename... Args>
long long measure_time_ms(Func&& func, Args&&... args)
{
    // Начало замера — фиксируем текущее время
    auto start = steady_clock::now();

    // Выполняем переданный код
    func(forward<Args>(args)...);

    // Конец замера
    auto end = steady_clock::now();

    // Вычисляем разницу и переводим в миллисекунды
    auto duration = duration_cast<milliseconds>(end - start);

	// Возвращаем количество миллисекунд
    return duration.count();
}

#endif