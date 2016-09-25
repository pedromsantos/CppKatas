#include <string>

const std::string FizzBuzz(const unsigned int number)
{
    if(number % 3 == 0 && number % 5 == 0)
    {
        return "fizzbuzz";
    }

    if(number % 3 == 0)
    {
        return "fizz";
    }

    if(number % 5 == 0)
    {
        return "buzz";
    }

    return std::to_string(number);
}
