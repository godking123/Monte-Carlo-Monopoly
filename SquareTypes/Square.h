//
// Created by rajit on 3/25/2026.
//

#ifndef SQUARE_H
#define SQUARE_H
#include <string>
#include <utility>
#include <vector>
class Player;
class Board;

class Square {
public:
    int position;
    std::string name;


    Square(const int pos, std::string name) : position(pos), name(std::move(name)){}
    virtual ~Square() = default;

    virtual void landOn(Player& player, std::vector<Player>& players, Board& board) = 0;
    virtual void clearOwner() {}
    virtual void clearHouses() {}
};



#endif //SQUARE_H
