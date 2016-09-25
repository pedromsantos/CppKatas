#include <string>

const std::string FizzBuzz(unsigned int number)
{
    if(number % 3 == 0)
    {
        return "fizz";
    }

    return std::to_string(number);
}
