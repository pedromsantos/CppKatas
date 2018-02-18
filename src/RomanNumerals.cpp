#include <map>

#include "RomanNumerals.hpp"

std::string RomanNumeral(const unsigned short arabicNumber)
{
    std::map<unsigned int, std::string> arabicsToRomans =
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

    for (auto arabicToRoman = arabicsToRomans.rbegin(); arabicToRoman != arabicsToRomans.rend(); ++arabicToRoman)
    {
        if (arabicNumber >= arabicToRoman->first)
        {
            return arabicToRoman->second + RomanNumeral(arabicNumber - arabicToRoman->first);
        }
    }

    return "";
}