cmake_minimum_required(VERSION 3.10)

set(Headers
    GameOfLife.hpp
)

set(Sources
    GameOfLife.cpp
)

add_library(${CMAKE_PROJECT_NAME} STATIC ${Sources} $(Headers))