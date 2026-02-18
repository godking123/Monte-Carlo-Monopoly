#include "board.h"

Board::Board() {
    spaces.resize(40, nullptr);

    spaces[39] = new Property("Boardwalk", 400, 39, 150);
    spaces[20] = new Property("Baltic Avenue", 60, 3, 20);
    spaces[1] = new Property("Virginia Avenue", 160, 14, 70);
}

Board::~Board() {
    for (auto p : spaces) {
        delete p;
    }
}

Property* Board::getPropertyAt(int position) {
    return spaces[position];
}