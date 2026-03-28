// Property.cpp
#include "Property.h"
#include "../../Player.h"
#include <iostream>
#include "../.././TerminalColors.h"
#ifdef _WIN32
#include <windows.h>
#endif


void Property::landOn(Player& player) {

    #ifdef _WIN32
        // enable ANSI escape codes on Windows
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;

    if (owner == nullptr && player.money >= price) {
        // Buys property, adding colors to colorSet and numColors to hashMap
        owner = &player;
        player.ownedProperties.push_back(this);
        player.pay(price);
        player.colorMap[color].insert(this);
        std::cout << MAGENTA << "[Property] " << RESET << "Player " << player.ID << " bought the Property (" << name << ") for $" << price << ". Remaining money: $" << RED << player.money << std::endl;
    }
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        int currentRent;
        if (houseCount == 0 && owner->checkColorMap(color)) {
            currentRent = rents[0]*2;
        }
        else {
            currentRent = rents[houseCount];
        }
        if (player.money < currentRent) {
            std::cout << "[Property] Player " << player.ID << " cannot afford full rent! (Has $" << player.money << ")" << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << MAGENTA << "[Property]" << RESET << " Player " << player.ID << " landed on " << name << " and paid $" << currentRent << " to Player " << owner->ID << ". Remaining money: $" << RED << player.money << std::endl;
        }

    } 
    else if (owner == &player) {
        std::cout << MAGENTA << "[Property]" << RESET << " Player " << player.ID << " already owns this Property." << std::endl;
    } 
    else {
        std::cout << MAGENTA << "[Property]" << RESET << " Player " << player.ID << " does not have enough money to buy this Property. (Price: $" << price << ", Has: $" << player.money << ")" << std::endl;
    }
}