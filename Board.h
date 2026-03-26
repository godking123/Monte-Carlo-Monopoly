#ifndef BOARD_H
#define BOARD_H

#include <unordered_map>
#include <vector>
#include "SquareTypes/Square.h"
#include "SquareTypes/Property/Property.h"
#include "SquareTypes/Community Chest/CommunityChest.h"
#include "SquareTypes/Chance/Chance.h"
#include "SquareTypes/Jail/Jail.h"
#include "SquareTypes/GoToJail/GoToJail.h"
#include "SquareTypes/Property/Railroad.h"
#include "SquareTypes/Property/Utility.h"
#include "SquareTypes/Taxes/IncomeTax.h"
#include "SquareTypes/Taxes/LuxuryTax.h"

class Board {
public:
    std::vector<Square*> spaces;

    Board();
    ~Board();

    [[nodiscard]] Square* getSquareAt(int position) const;
};

#endif