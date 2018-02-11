#include "FizzBuzz.hpp"

std::string FizzBuzz(const unsigned int number)
{
    std::string fizzBuzz;

    if (number % 3 == 0)
    {
        fizzBuzz = "fizz";
    }

    if (number % 5 == 0)
    {
        fizzBuzz += "buzz";
    }

    return fizzBuzz.length() > 0
           ? fizzBuzz
           : std::to_string(number);
}
