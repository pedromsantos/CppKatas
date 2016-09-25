#include "catch.hpp"
#include "../src/Fibonacci.cpp"

TEST_CASE( "Calculate fibonacci number for index", "[Fibonacci]") {
    REQUIRE( Fibonacci(0) == 0 );
    REQUIRE( Fibonacci(1) == 1 );
    REQUIRE( Fibonacci(2) == 1 );
    REQUIRE( Fibonacci(3) == 2 );
    REQUIRE( Fibonacci(3) == 2 );
    REQUIRE( Fibonacci(4) == 3 );
    REQUIRE( Fibonacci(5) == 5 );
    REQUIRE( Fibonacci(6) == 8 );
    REQUIRE( Fibonacci(7) == 13 );
}