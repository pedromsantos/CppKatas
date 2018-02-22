cmake_minimum_required(VERSION 3.6)
project(CppKatas)

set(CMAKE_ENABLE_COMPILE_COMMANDS=ON)
set(CMAKE_CXX_STANDARD 17)

if(MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /std:c++17")
endif(MSVC)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

file(GLOB_RECURSE LIB_SRC src/*.cpp src/*hpp)
file(GLOB TEST_SRC test/*.cpp test/*.hpp)

add_library(CppKatas STATIC ${LIB_SRC})
add_executable(CppKatasTests ${TEST_SRC})

target_link_libraries(CppKatasTests CppKatas)

enable_testing()
add_test(NAME CppKatasTests COMMAND CppKatasTests)