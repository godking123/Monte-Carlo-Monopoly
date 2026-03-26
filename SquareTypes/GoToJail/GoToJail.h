//
// Created by rajit on 3/25/2026.
//

#ifndef GOTOJAIL_H
#define GOTOJAIL_H
#include "../Square.h"


class GoToJail : public Square {
public:
    explicit GoToJail(int pos) : Square(pos, "GoToJail") {}
    ~GoToJail() override = default;

    void landOn(Player &player) override;
};



#endif //GOTOJAIL_H
