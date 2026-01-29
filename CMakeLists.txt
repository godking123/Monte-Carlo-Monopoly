cmake_minimum_required(VERSION 3.31)
project(MonteCarlo_Monopoly)

set(CMAKE_CXX_STANDARD 20)

add_executable(MonteCarlo_Monopoly main.cpp
        player.cpp
        player.h
        Property.cpp
        Property.h)
