#include "catch.hpp"
#include "../src/RomanNumerals.cpp"

TEST_CASE( "Calculate roman numeral for arabic number", "[Fibonacci]") {
    REQUIRE( RomanNumeral(1) == "I" );
    REQUIRE( RomanNumeral(2) == "II" );
    REQUIRE( RomanNumeral(4) == "IV" );
    REQUIRE( RomanNumeral(5) == "V" );
    REQUIRE( RomanNumeral(6) == "VI" );
    REQUIRE( RomanNumeral(7) == "VII" );
    REQUIRE( RomanNumeral(8) == "VIII" );
    REQUIRE( RomanNumeral(9) == "IX" );
    REQUIRE( RomanNumeral(10) == "X" );
    REQUIRE( RomanNumeral(11) == "XI" );
    REQUIRE( RomanNumeral(40) == "XL" );
    REQUIRE( RomanNumeral(50) == "L" );
    REQUIRE( RomanNumeral(90) == "XC" );
    REQUIRE( RomanNumeral(100) == "C" );
    REQUIRE( RomanNumeral(400) == "CD" );
    REQUIRE( RomanNumeral(500) == "D" );
    REQUIRE( RomanNumeral(900) == "CM" );
    REQUIRE( RomanNumeral(1000) == "M" );
}