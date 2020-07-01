cmake_minimum_required(VERSION 3.10)

project(GameOfLife CXX)

set(CMAKE_CXX_STANDARD 17)

# Enable gtest
enable_testing()

include_directories(src)

add_subdirectory(test)
