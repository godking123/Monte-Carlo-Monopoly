
#include "Player.h"

#include <iostream>
#include <bits/ostream.tcc>

void Player::pay(const int amount) {
    money -= amount;
}

void Player::move(const int steps) {
    int oldPosition = position;
    position = (position + steps) % 40;

    if (oldPosition > position)
    {
        receive(200);
    }
}

void Player::receive(const int amount) {
    money += amount;
}

bool Player::checkColorMap(const std::string& color) {
    if (color == "Dark Blue" || color == "Brown") {
        if (colorMap[color].size() == 2) {
            return true;
        }
    } else {
        if (colorMap[color].size() == 3) {
            return true;
        }
    }
    return false;
}

void Player::autoBuyHouse(Property* property) {
    if (!this->checkColorMap(property->color)) {
        return;
    }
    // Determine properties in the color group
    const auto& colorGroup = colorMap[property->color];

    for (Property* p : colorGroup) {
        if (p->houseCount < property->houseCount) {
            return; // Must buy a property with less houses
        }
    }

    if (property->houseCount == 5) {
        return;
    }

    if (money >= property->houseCost) {
        money -= property->houseCost;
        property->houseCount++;

        if (property->houseCount == 5) {
            std::cout << "[House] Player " << ID << " bought a hotel for " << property->name << "." << std::endl;
        } else {
            std::cout << "[House] Player " << ID << " bought a house for " << property->name << "." << std::endl;
        }
    }
}



