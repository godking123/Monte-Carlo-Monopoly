//
// Created by rajit on 3/25/2026.
//

#ifndef JAIL_H
#define JAIL_H
#include "../Square.h"


class Jail : public Square{
public:
    explicit Jail(int pos) : Square(pos) {}
    ~Jail() override = default;

    void landOn(Player& player) override;
};



#endif //JAIL_H
