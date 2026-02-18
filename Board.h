#ifndef BOARD_H
#define BOARD_H

#include <vector>
#include "property.h"

class Board {
public:
    std::vector<Property*> spaces;

    Board();
    ~Board();

    Property* getPropertyAt(int position);
};


#endif
