
#include "Player.h"

void Player::pay(const int amount) {
    money -= amount;
    if (money < 0) {
        bankrupt = true;
    }
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

