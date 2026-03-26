//
// Created by rajit on 3/25/2026.
//

#ifndef CHANCE_H
#define CHANCE_H
#include "../Square.h"


class Chance : public Square{

public:
    int move;
    int cost;
    int pos;

    Chance(int pos, int move, int cost)
        : Square(pos, "Chance"), move(move), cost(cost) {}
    ~Chance() override = default;
    void landOn(Player& player) override;
};

#endif //CHANCE_H
