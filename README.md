# MonteCarlo Monopoly

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)
![Windows](https://img.shields.io/badge/Windows-0078D6?style=for-the-badge&logo=windows&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=for-the-badge&logo=linux&logoColor=black)
![macOS](https://img.shields.io/badge/macOS-000000?style=for-the-badge&logo=apple&logoColor=white)

<p align="center">
  <img src="Public/Monopoly_game_logo.svg.png" alt="Monopoly Logo" width="400"/>
</p>

## Description

**MonteCarlo Monopoly** is a C++ simulation of the classic board game. This project models the complex rules, probabilities, and mechanics of Monopoly using robust Object-Oriented Programming (OOP) principles. 

It features modular implementations for the board layout, properties, railroads, utilities, dice mechanics, taxes, and specialized spaces like Jail, Chance, and Community Chest. The game calculates game states and effectively simulates the economy of a standard Monopoly match.

## Technologies Used

* **Language:** C++ (Standard C++17 or higher)
* **Build System:** CMake
* **Concepts Used:** Object-Oriented Programming (Polymorphism, Inheritance), Standard Template Library (STL), ANSI escape codes for console styling.

## The Board

![Monopoly Board](Public/81oC5pYhh2L._AC_UF894,1000_QL80_.jpg)

---

### How to Build & Run
1. Ensure you have **CMake** and a compatible C++ compiler installed (e.g., GCC, Clang, or MSVC).
2. Clone the repository.
3. Open the project in an IDE like **CLion** or build it via command line:
   ```bash
   mkdir build && cd build
   cmake ..
   cmake --build .
   ```
4. Run the generated executable to start the simulation.