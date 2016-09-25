#include "catch.hpp"
#include "../src/Fibonacci.cpp"

TEST_CASE( "Calculate fibonacci number for index", "[Fibonacci]") {
    REQUIRE( Fibonacci(0) == 0 );
    REQUIRE( Fibonacci(1) == 1 );
    REQUIRE( Fibonacci(2) == 1 );
    REQUIRE( Fibonacci(3) == 2 );
}