cmake_minimum_required(VERSION 3.6)
project(CppKatas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

add_library(Katas STATIC src/FizzBuzz.cpp src/Fibonacci.cpp)
add_executable(Tests test/FizzBuzzTests.cpp test/FibonacciTests.cpp test/main.cpp)