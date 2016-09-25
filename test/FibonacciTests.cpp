#include "catch.hpp"
#include "../src/Fibonacci.cpp"

TEST_CASE( "Calculate fibonacci number for index", "[Fibonacci]") {
    REQUIRE( Fibonacci(0) == 0 );
}