
#ifndef INCOMETAX_H
#define INCOMETAX_H
#include <iostream>
#include <ostream>

#include "../Square.h"
#include "../../Player.h"

class IncomeTax : public Square
{
public:
    explicit IncomeTax(int pos) : Square(pos, "Income Tax") {}
    ~IncomeTax() override = default;

    void landOn(Player& player) override
    {
        if (player.money < 1000) {
            int currTax = 0.2 * player.money;
            player.pay(currTax);
            std::cout << "Income Tax Paid (" << currTax << ")" << std::endl;
        } else {
            player.pay(200);
            std::cout << "Income Tax Paid (200)" << std::endl;
        }
    };
};
#endif //INCOMETAX_H
