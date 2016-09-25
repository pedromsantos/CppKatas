cmake_minimum_required(VERSION 3.6)
project(CppKatas)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

add_library(Katas STATIC src/fizzBuzz.cpp)
add_executable(Tests test/fizzBuzzTests.cpp)