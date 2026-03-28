
#ifndef INCOMETAX_H
#define INCOMETAX_H
#include <iostream>
#include <ostream>

#include "../Square.h"
#include "../../Player.h"
#include "../../TerminalColors.h"

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
            std::cout << TerminalColors::RESET << "[Income Tax] " << "Player " << player.ID << " paid " << currTax << " for income tax." << std::endl;
        } else {
            player.pay(200);
            std::cout << TerminalColors::RESET << "[Income Tax] " << "Player " << player.ID << " paid 200 for income tax." << std::endl;
        }
    };
};
#endif //INCOMETAX_H
