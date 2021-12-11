cmake_minimum_required(VERSION 3.6)
project(adventofcode2021)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -Wall -Werror -Wextra")

add_executable(day01 day01/day01.cpp)
add_executable(day02 day02/day02.cpp)
add_executable(day03 day03/day03.cpp)
add_executable(day04 day04/day04.cpp)
