#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "SquareTypes/Square.h"
#include "SquareTypes/Property/Property.h"
#include "SquareTypes/Community Chest/CommunityChest.h"
#include "SquareTypes/Chance/Chance.h"
#include "SquareTypes/Jail/Jail.h"
#include "SquareTypes/GoToJail/GoToJail.h"

class Board {
public:
    std::vector<Square*> spaces;

    Board();
    ~Board();

    Square* getSquareAt(int position) const;
};

#endif