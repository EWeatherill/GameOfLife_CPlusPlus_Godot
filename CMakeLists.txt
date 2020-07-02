cmake_minimum_required(VERSION 3.10)

project(GameOfLife CXX)

set(CMAKE_CXX_STANDARD 17)

# Enable unit testing with CTest and gtest
include(CTest)
enable_testing()

add_subdirectory(src)
add_subdirectory(test)
