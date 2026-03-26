// Property.cpp
#include "Property.h"
#include "../../Player.h"
#include <iostream>

void Property::landOn(Player& player) {
    std::cout << "[Property] Player " << player.ID << " landed on a Property." << std::endl;

    if (owner == nullptr && player.money >= price) {
        owner = &player;
        player.ownedProperties.push_back(this);
        player.pay(price);
        std::cout << "[Property] Player " << player.ID << " bought the Property (" << name << ") for $" << price << ". Remaining money: $" << player.money << std::endl;
    } 
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        int currentRent = housePrices[houseCount];
        std::cout << "[Property] Property is owned by Player " << owner->ID << ". Rent is $" << currentRent << "." << std::endl;
        
        if (player.money < currentRent) {
            std::cout << "[Property] Player " << player.ID << " cannot afford full rent! (Has $" << player.money << ")" << std::endl;
            owner->receive(player.money);
            player.pay(currentRent);
        }
        else {
            player.pay(currentRent);
            owner->receive(currentRent);
            std::cout << "[Property] Player " << player.ID << " paid $" << currentRent << " to Player " << owner->ID << ". Remaining money: $" << player.money << std::endl;
        }

    } 
    else if (owner == &player) {
        std::cout << "[Property] Player " << player.ID << " already owns this Property." << std::endl;
    } 
    else {
        std::cout << "[Property] Player " << player.ID << " does not have enough money to buy this Property. (Price: $" << price << ", Has: $" << player.money << ")" << std::endl;
    }
}