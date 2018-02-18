#include "Fibonacci.hpp"

unsigned int Fibonacci(const unsigned short index)
{
    return (index == 0 || index == 1)
           ? index
           : Fibonacci(index - 1) + Fibonacci(index - 2);
}