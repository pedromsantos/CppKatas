#include "RomanNumerals.hpp"
#include <map>

std::string RomanNumeral(const unsigned short arabicNumber)
{
    using numeral = std::pair<int, std::string>;

    static const numeral arabicsToRomans[] =
          {
                  {1000, "M"}, {900, "CM"},
                  {500, "D"}, {400, "CD"},
                  {100, "C"}, {90, "XC"},
                  {50, "L"}, {40, "XL"},
                  {10, "X"}, {9, "IX"},
                  {5, "V"}, {4, "IV"},
                  {1, "I"}
          };

    for (auto [arabic, roman] : arabicsToRomans)
    {
        if (arabicNumber >= arabic)
        {
            return roman + RomanNumeral(arabicNumber - arabic);
        }
    }

    return "";
}