cmake_minimum_required(VERSION 3.31)
project(MonteCarlo_Monopoly)

set(CMAKE_CXX_STANDARD 20)

add_executable(MonteCarlo_Monopoly main.cpp
        Player.cpp
        Player.h
        Property.h
        Board.cpp
        Board.h
        Dice.h
        Square.h
        Property.cpp
        CommunityChest.cpp
        CommunityChest.h
)
