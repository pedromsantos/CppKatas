#include "catch.hpp"
#include "../src/RomanNumerals.cpp"

TEST_CASE( "Calculate roman numeral for arabic number", "[Fibonacci]") {
    REQUIRE( RomanNumeral(1) == "I" );
    REQUIRE( RomanNumeral(2) == "II" );
    REQUIRE( RomanNumeral(4) == "IV" );
}