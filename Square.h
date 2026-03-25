//
// Created by rajit on 3/25/2026.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <string>

class Player;

class Square {
public:
    int position;

    Square(int pos) : position(pos){}

    virtual void landOn(Player& player) = 0;
    virtual ~Square() = default;
};



#endif //SQUARE_H
