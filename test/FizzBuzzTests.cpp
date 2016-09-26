#include "catch.hpp"
#include "../src/FizzBuzz.hpp"

TEST_CASE( "Convert number to fizz buzz number", "[FizzBuzz]") {
    REQUIRE( FizzBuzz(1) == "1" );
    REQUIRE( FizzBuzz(2) == "2" );
    REQUIRE( FizzBuzz(3) == "fizz" );
    REQUIRE( FizzBuzz(6) == "fizz" );
    REQUIRE( FizzBuzz(9) == "fizz" );
    REQUIRE( FizzBuzz(5) == "buzz" );
    REQUIRE( FizzBuzz(10) == "buzz" );
    REQUIRE( FizzBuzz(20) == "buzz" );
    REQUIRE( FizzBuzz(15) == "fizzbuzz" );
}
