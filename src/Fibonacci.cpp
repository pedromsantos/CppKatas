#include "Fibonacci.hpp"

unsigned int Fibonacci(const unsigned int index)
{
    if(index == 0 || index == 1)
    {
        return index;
    }

    return Fibonacci(index - 1) + Fibonacci(index - 2);
}
