#include "Railroad.h"
#include "../../Player.h"
#include <iostream>

void Railroad::landOn(Player& player)
{
    std::cout << "[Railroad] Player " << player.ID << " landed on a Railroad." << std::endl;

    if (owner == nullptr && player.money >= price) {
        owner = &player;
        owner->numRailroads++;
        player.ownedProperties.push_back(this);
        player.pay(price);
        // Note: numRailroads is initialized to -1 in Player.h, so owner->numRailroads + 1 is the actual count
        std::cout << "[Railroad] Player " << player.ID << " bought the Railroad (" << name << ") for $" << price << ". They now own " << (owner->numRailroads + 1) << " railroad(s)." << std::endl;
    }
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        // Current Rent is Based off of numRailroads owned
        int currentRent = rents[owner->numRailroads];
        std::cout << "[Railroad] Railroad is owned by Player " << owner->ID << ". They own " << (owner->numRailroads + 1) << " railroad(s). Rent is $" << currentRent << "." << std::endl;
        
        if (player.money < currentRent) {
            std::cout << "[Railroad] Player " << player.ID << " cannot afford full rent! (Has $" << player.money << ")" << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << "[Railroad] Player " << player.ID << " paid $" << currentRent << " to Player " << owner->ID << "." << std::endl;
        }

    }
    else if (owner == &player) {
        std::cout << "[Railroad] Player " << player.ID << " already owns this Railroad." << std::endl;
    }
    else {
        std::cout << "[Railroad] Player " << player.ID << " does not have enough money to buy this Railroad. (Price: $" << price << ", Has: $" << player.money << ")" << std::endl;
    }
}