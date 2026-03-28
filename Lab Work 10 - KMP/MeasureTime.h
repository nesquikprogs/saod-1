#pragma once

#include <chrono>
#include <utility>

using namespace std::chrono;
using std::forward;

/// <summary>
/// Шаблонная функция для измерения времени выполнения переданного кода в микросекундах
/// </summary>
/// <typeparam name="Func">Любой тип, который можно вызвать как функцию (обычная функция, лямбда, функтор)</typeparam>
/// <typeparam name="...Args">Типы аргументов, которые будут переданы в вызываемый объект</typeparam>
/// <param name="func">Вызываемый объект, время выполнения которого нужно измерить</param>
/// <param name="...args">Аргументы, которые нужно передать в вызываемый объект</param>
/// <returns>Количество микросекунд, затраченное на выполнение переданного кода</returns>
/// <remarks>
/// Сложность по времени: O(T(func)), где T(func) — время работы вызываемого кода.
/// </remarks>
template<typename Func, typename... Args>
long long measure_time_ms(Func&& func, Args&&... args)
{
    // Начало замера — фиксируем текущее время
    auto start = steady_clock::now();

    // Выполняем переданный код
    func(forward<Args>(args)...);

    // Конец замера — снова фиксируем текущее время
    auto end = steady_clock::now();

    // Вычисляем разницу и преобразуем её в микросекунды
    auto duration = duration_cast<microseconds>(end - start);

    // Возвращаем количество микросекунд
    return duration.count();
}

