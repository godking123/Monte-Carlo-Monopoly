
#include "Player.h"

void Player::pay(const int amount) {
    if (money < amount) {
        bankrupt = true;
        return;
    }
    money -= amount;
}

void Player::move(const int steps) {
    position += (steps % 40);
}

void Player::receive(const int amount) {
    money += amount;
}

