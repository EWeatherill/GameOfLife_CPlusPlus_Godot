cmake_minimum_required(VERSION 3.10)

set(Headers
    GameOfLife.hpp
)

set(Sources
    GameOfLife.cpp
)

add_library(${CMAKE_PROJECT_NAME} ${Sources})
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})