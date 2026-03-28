#include <iostream>

#include "Benchmark.h"

using namespace std;

int main()
{

    benchmark::measure_for_random_sequences();
    benchmark::measure_for_natural_text();
    benchmark::measure_for_four_symbol_sequences();

    cout << endl << "OK" << endl;

    return 0;

}

