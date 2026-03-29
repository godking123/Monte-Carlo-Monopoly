#ifndef RAILROADS_H
#define RAILROADS_H
#include <vector>

#include "../Square.h"

class Railroad : public Square {
public:

    int price;
    std::string name;
    std::vector<int> rents;
    Player* owner;

    explicit Railroad(const std::string& name, int pos) : Square(pos, name), price(200), rents( {25, 50, 100, 200}), name(name), owner(nullptr) {}
    ~Railroad() override = default;

    void landOn(Player& player, std::vector<Player>& players, Board& board) override;
    void clearOwner() override
    {
        owner = nullptr;
    }
};

#endif //RAILROADS_H
