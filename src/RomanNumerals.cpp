#include <string>

const std::string RomanNumeral(const unsigned int arabicNumber)
{
    if(arabicNumber == 10)
    {
        return "X";
    }

    if(arabicNumber == 9)
    {
        return "IX";
    }

    if(arabicNumber >= 5)
    {
        return "V" + RomanNumeral(arabicNumber - 5);
    }

    if(arabicNumber == 4)
    {
        return "IV";
    }

    return std::string(arabicNumber, 'I');
}