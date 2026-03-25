
#include "GoToJail.h"

#include "../../Player.h"

void GoToJail::landOn(Player& player)
{
    player.inJail = true;
    player.position = 10;
}

