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
    int houseCount;
    int houseCost;
    bool mortgaged;
    std::string color;
    std::vector<int> rents; // Index 0: Normal Rent -> Index 1: 1 House Rent -> Index 5: Hotel Rent
    Player* owner;

    Property(std::string name, int price, int pos, std::vector<int> rents, int houseCost, std::string color)
        : Square(pos, name), name(std::move(name)),
          price(price), houseCount(0), owner(nullptr),
          rents(std::move(rents)), houseCost(houseCost), color(std::move(color)) {}
    ~Property() override = default;

    void landOn(Player& player, std::vector<Player>& players, Board& board) override;
    void clearOwner() override {
        owner = nullptr;
    }
    void clearHouses() override {
        houseCount = 0;
    }

};

#endif // PROPERTY_H