//
// Created by rajit on 3/25/2026.
//

#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H
#include "../Square.h"


class CommunityChest : public Square {
public:
    int move;
    int cost;
    int pos;

    CommunityChest(int pos, int move, int cost)
        : Square(pos), move(move), cost(cost) {}
    ~CommunityChest() override = default;
    void landOn(Player& player) override;
};




#endif //COMMUNITYCHEST_H
