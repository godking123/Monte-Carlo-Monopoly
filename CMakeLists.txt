cmake_minimum_required(VERSION 3.31)
project(MonteCarlo_Monopoly)

set(CMAKE_CXX_STANDARD 20)

add_executable(MonteCarlo_Monopoly main.cpp
        Player.cpp
        Player.h
        SquareTypes/Property/Property.h
        Board.cpp
        Board.h
        Dice.h
        SquareTypes/Square.h
        SquareTypes/Property/Property.cpp
        "SquareTypes/Community Chest/CommunityChest.cpp"
        "SquareTypes/Community Chest/CommunityChest.h"
        SquareTypes/Chance/Chance.cpp
        SquareTypes/Chance/Chance.h
        SquareTypes/Jail/Jail.cpp
        SquareTypes/Jail/Jail.h
        SquareTypes/GoToJail/GoToJail.cpp
        SquareTypes/GoToJail/GoToJail.h
        SquareTypes/Property/Utility.cpp
        SquareTypes/Property/Utility.h
        SquareTypes/Property/Railroad.cpp
        SquareTypes/Property/Railroad.h
        SquareTypes/Taxes/LuxuryTax.h
        SquareTypes/Taxes/IncomeTax.h
        TerminalColors.h
        SquareTypes/Card.h
        Trading.h
)
set(CMAKE_EXE_LINKER_FLAGS "-static -static-libgcc -static-libstdc++")
