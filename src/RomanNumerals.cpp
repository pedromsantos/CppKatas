#include <map>

#include "RomanNumerals.hpp"

std::string RomanNumeral(const unsigned int arabicNumber)
{
    std::map<unsigned int, std::string> arabicToRoman =
            {
                    {1,    "I"},
                    {4,    "IV"},
                    {5,    "V"},
                    {9,    "IX"},
                    {10,   "X"},
                    {40,   "XL"},
                    {50,   "L"},
                    {90,   "XC"},
                    {100,  "C"},
                    {400,  "CD"},
                    {500,  "D"},
                    {900,  "CM"},
                    {1000, "M"},
            };

    for (auto i = arabicToRoman.rbegin(); i != arabicToRoman.rend(); ++i)
    {
        if (arabicNumber >= i->first)
        {
            return i->second + RomanNumeral(arabicNumber - i->first);
        }
    }

    return "";
}