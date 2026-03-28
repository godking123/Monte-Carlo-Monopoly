#ifndef LUXURYTAX_H
#define LUXURYTAX_H

#include "../Square.h"
#include "../../Player.h"
#include <iostream>
#include "../.././TerminalColors.h"
#ifdef _WIN32
#include <windows.h>
#endif

class LuxuryTax : public Square
{
public:
    explicit LuxuryTax(int pos) : Square(pos, "Income Tax") {}
    ~LuxuryTax() override = default;

    void landOn(Player& player) override
    {

        #ifdef _WIN32
                // enable ANSI escape codes on Windows
                HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
                DWORD dwMode = 0;
                GetConsoleMode(hOut, &dwMode);
                SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        #endif
        player.pay(100);
        std::cout << TerminalColors::CYAN << "[Luxury Tax] " << TerminalColors::RESET << "Player " << player.ID << " paid 100." << std::endl;
    };
};

#endif //LUXURYTAX_H
