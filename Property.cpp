// Property.cpp
#include "Property.h"
#include "Player.h"

void Property::landOn(Player& player) {
    if (owner == nullptr && player.money >= price) {
        owner = &player;
        player.ownedProperties.push_back(this);
        player.pay(price);
    } 
    // If owned by someone else, pay rent
    else if (owner != nullptr && owner != &player) {
        owner->receive(rent);
        player.pay(rent);
    }
}