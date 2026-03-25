#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "Square.h"
#include "Property.h"
#include "CommunityChest.h"

class Board {
public:
    std::vector<Square*> spaces;

    Board();
    ~Board();

    Square* getSquareAt(int position) const;
};

#endif