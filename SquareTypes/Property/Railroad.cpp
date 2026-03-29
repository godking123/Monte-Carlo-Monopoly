// Railroad.cpp
#include "Railroad.h"
#include "../../Player.h"
#include "../../TerminalColors.h"
#include <iostream>
#ifdef _WIN32
#include <windows.h>
#endif

void Railroad::landOn(Player& player, std::vector<Player>& players, Board& board)
{
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;

    if (owner == nullptr && player.money >= price) {
        owner = &player;
        owner->numRailroads++;
        player.ownedRailroads.push_back(this);
        player.pay(price);
        std::cout << BLACK << "[Railroad] " << RESET << "Player " << player.ID << " bought the Railroad (" << name << ") for $" << price << ". They now own " << (owner->numRailroads + 1) << " railroad(s). Remaining money: $" << RED << player.money << RESET << std::endl;
    }

    else if (owner != nullptr && owner != &player) {
        int currentRent = rents[owner->numRailroads];

        if (player.money < currentRent) {
            std::cout << BLACK << "[Railroad] " << RESET << "Player " << player.ID << " cannot afford full rent! (Has $" << RED << player.money << RESET << ")" << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << BLACK << "[Railroad] " << RESET << "Player " << player.ID << " paid $" << currentRent << " to Player " << owner->ID << ". Remaining money: $" << RED << player.money << RESET << std::endl;
        }
    }
    else if (owner == &player) {
        std::cout << BLACK << "[Railroad] " << RESET << "Player " << player.ID << " already owns this Railroad. " << "(" << name << ")" << std::endl;
    }
    else {
        std::cout << BLACK << "[Railroad] " << RESET << "Player " << player.ID << " does not have enough money to buy this Railroad. (Price: $" << price << ", Has: $" << RED << player.money << RESET << ")" << std::endl;
    }
}