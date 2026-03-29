#include "Utility.h"
#include "../../Player.h"
#include <iostream>
#include ".//../.././TerminalColors.h"
#ifdef _WIN32
#include <windows.h>
#endif



void Utility::landOn(Player& player, std::vector<Player>& players, Board& board)
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
        owner->numUtilities++;
        player.ownedUtilities.push_back(this);
        player.pay(price);
        std::cout << YELLOW << "[Utility]" << RESET << " Player " << player.ID << " bought the Utility (" << name << ") for $" << price << ". They now own " << owner->numUtilities << " utilitie(s)." << std::endl;
    }
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        // Current Rent is Based off of numUtilities owned
        int currentRent = 0;
        if (owner->numUtilities == 1) {
            // Dice Roll * 4
            currentRent = player.currDiceRoll * 4;
        } else {
            // Dice Roll * 10
            currentRent = player.currDiceRoll * 10;
        }
        
        if (player.money < currentRent) {
            std::cout << YELLOW << "[Utility]" << RESET << " Player " << player.ID << " cannot afford full rent! (Has $" << player.money << ") " << currentRent << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << YELLOW << "[Utility]" << RESET << " Player " << player.ID << " paid $" << currentRent << " to Player " << owner->ID << "." << std::endl;
        }
    }
    else if (owner == &player) {
        std::cout << "[Utility] Player " << player.ID << " already owns this Utility." << std::endl;
    }
    else {
        std::cout << "[Utility] Player " << player.ID << " does not have enough money to buy this Utility. (Price: $" << price << ", Has: $" << player.money << ")" << std::endl;
    }
}