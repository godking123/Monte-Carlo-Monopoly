#include "Utility.h"
#include "../../Player.h"
#include <iostream>

void Utility::landOn(Player& player)
{
    std::cout << "[Utility] Player " << player.ID << " landed on a Utility. Current dice roll was " << player.currDiceRoll << "." << std::endl;

    if (owner == nullptr && player.money >= price) {
        owner = &player;
        owner->numUtilities++;
        player.ownedProperties.push_back(this);
        player.pay(price);
        std::cout << "[Utility] Player " << player.ID << " bought the Utility (" << name << ") for $" << price << ". They now own " << owner->numUtilities << " utilitie(s)." << std::endl;
    }
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        // Current Rent is Based off of numUtilities owned
        int currentRent = 0;
        if (owner->numUtilities == 1) {
            // Dice Roll * 4
            currentRent = player.currDiceRoll * 4;
            std::cout << "[Utility] Utility owned by Player " << owner->ID << " (owns 1). Rent is 4x dice roll: $" << currentRent << "." << std::endl;
        } else {
            // Dice Roll * 10
            currentRent = player.currDiceRoll * 10;
            std::cout << "[Utility] Utility owned by Player " << owner->ID << " (owns 2). Rent is 10x dice roll: $" << currentRent << "." << std::endl;
        }
        
        if (player.money < currentRent) {
            std::cout << "[Utility] Player " << player.ID << " cannot afford full rent! (Has $" << player.money << ")" << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << "[Utility] Player " << player.ID << " paid $" << currentRent << " to Player " << owner->ID << "." << std::endl;
        }
    }
    else if (owner == &player) {
        std::cout << "[Utility] Player " << player.ID << " already owns this Utility." << std::endl;
    }
    else {
        std::cout << "[Utility] Player " << player.ID << " does not have enough money to buy this Utility. (Price: $" << price << ", Has: $" << player.money << ")" << std::endl;
    }
}