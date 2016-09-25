#define CATCH_CONFIG_MAIN

#include "../catch.hpp"
#include "../src/fizzBuzz.cpp"

TEST_CASE( "Convert number to fizz buzz number", "[FizzBuzz]") {
    REQUIRE( FizzBuzz(1) == "1" );
    REQUIRE( FizzBuzz(2) == "2" );
    REQUIRE( FizzBuzz(3) == "fizz" );
    REQUIRE( FizzBuzz(6) == "fizz" );
    REQUIRE( FizzBuzz(9) == "fizz" );
}