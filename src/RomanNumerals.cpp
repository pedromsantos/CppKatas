#include <string>

const std::string RomanNumeral(const unsigned int arabicNumber)
{
    if(arabicNumber == 4)
    {
        return "IV";
    }
    
    return std::string(arabicNumber, 'I');
}