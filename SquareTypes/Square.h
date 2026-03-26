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
    std::string name;

    Square(int pos, std::string name) : position(pos), name(name){}
    virtual ~Square() = default;

    virtual void landOn(Player& player) = 0;
    virtual void clearOwner() {}
};



#endif //SQUARE_H
