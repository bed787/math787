cmake_minimum_required(VERSION 4.0)
project(math787)

set(CMAKE_CXX_STANDARD 20)

add_executable(math787 main.cpp
        Matrix.hpp
        Permutations.hpp
        utils.hpp)