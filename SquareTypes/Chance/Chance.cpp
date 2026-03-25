//
// Created by rajit on 3/25/2026.
//

#include "Chance.h"
#include "../../Player.h"

void Chance::landOn(Player& player) {
    player.move(move);
    player.receive(cost);
}
