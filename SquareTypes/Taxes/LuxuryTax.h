#ifndef LUXURYTAX_H
#define LUXURYTAX_H


#include "../Square.h"
#include "../../Player.h"

class LuxuryTax : public Square
{
public:
    explicit LuxuryTax(int pos) : Square(pos, "Income Tax") {}
    ~LuxuryTax() override = default;

    void landOn(Player& player) override
    {
        player.pay(100);
        std::cout << "Luxury Tax Paid (100)" << std::endl;
    };
};

#endif //LUXURYTAX_H
