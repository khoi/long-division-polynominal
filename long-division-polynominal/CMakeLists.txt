cmake_minimum_required(VERSION 3.10)
project(long_division_polynominal)

set(CMAKE_CXX_STANDARD 11)

include_directories(.)

add_executable(long_division_polynominal
        main.cpp
        polynomial.cpp
        polynomial.hpp
        polynomial_linkedlist.hpp
        polynomial_linkedlist.cpp)
