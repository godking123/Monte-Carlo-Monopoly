#ifndef UTILITIES_H
#define UTILITIES_H
#include "../Square.h"


class Utility : public Square {
public:
    int price;
    std::string name;
    Player* owner;

    explicit Utility(const std::string& name, int pos) : Square(pos, name), price(150), name(name), owner(nullptr) {}
    ~Utility() override = default;

    void landOn(Player& player, std::vector<Player>& players, Board& board) override;
    void clearOwner() override
    {
        owner = nullptr;
    }
};

#endif //UTILITIES_H
