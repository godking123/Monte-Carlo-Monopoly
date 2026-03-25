#ifndef PROPERTY_H
#define PROPERTY_H

#include "../Square.h"
#include <string>
class Player;

class Property : public Square {
public:
    std::string name;
    int price;
    int rent;
    int houseCount;
    Player* owner;

    Property(std::string name, int price, int pos, int rent)
        : Square(pos), name(std::move(name)),
          price(price), rent(rent), houseCount(0), owner(nullptr) {}
    ~Property() override = default;
    void landOn(Player& player) override;
};

#endif // PROPERTY_H