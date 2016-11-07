cmake_minimum_required(VERSION 3.6)
project(CppKatas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_library(Katas STATIC src/FizzBuzz.cpp src/Fibonacci.cpp src/RomanNumerals.cpp src/TicTacToe.cpp src/MarsRover/MarsRover.cpp src/MarsRover/Commands.cpp)
add_executable(Tests test/FizzBuzzTests.cpp test/FibonacciTests.cpp test/main.cpp test/RomanNumeralsTests.cpp test/TicTacToeTests.cpp test/MarsRoverTests.cpp)

target_link_libraries(Tests Katas)

enable_testing()
add_test(NAME Tests COMMAND ./bin/Tests)