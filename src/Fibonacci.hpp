#ifndef CPPKATAS_SRC_FIBONACCI_H
#define CPPKATAS_SRC_FIBONACCI_H

constexpr auto Fibonacci(const unsigned short index)
{
    if(index == 0) { return 0;}
    if(index == 1) { return 1;}
    return Fibonacci(index - 1) + Fibonacci(index - 2);
}

#endif