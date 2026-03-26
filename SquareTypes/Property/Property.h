#ifndef PROPERTY_H
#define PROPERTY_H

#include "../Square.h"
#include <string>
#include <utility>
#include <vector>
class Player;

class Property : public Square {
public:
    std::string name;
    int price;
    int rent;
    int houseCount;
    int houseCost{};
    std::vector<int> housePrices; // Index 0: Normal Rent -> Index 1: 1 House Rent -> Index 5: Hotel Rent
    Player* owner;

    Property(std::string name, int price, int pos, int rent, std::vector<int> housePrices, int houseCost)
        : Square(pos, name), name(std::move(name)),
          price(price), rent(rent), houseCount(0), owner(nullptr), 
          housePrices(std::move(housePrices)), houseCost(houseCost) {}
    ~Property() override = default;
    void landOn(Player& player) override;
    void clearOwner() override
    {
        owner = nullptr;
    }
};

#endif // PROPERTY_H