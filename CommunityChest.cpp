

#include "CommunityChest.h"

#include "Player.h"

void CommunityChest::landOn(Player& player) {
    player.move(move);
    player.receive(cost);
}
