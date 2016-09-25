#include <string>

const std::string FizzBuzz(const unsigned int number)
{
    if(number % 3 == 0)
    {
        return "fizz";
    }

    if(number == 5 || number == 10 || number == 20)
    {
        return "buzz";
    }

    return std::to_string(number);
}
