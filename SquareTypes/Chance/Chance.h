// Chance.h
#ifndef CHANCE_H
#define CHANCE_H
#include "../Square.h"
#include "../Card.h"
#include <vector>

class Board;

class Chance : public Square {
public:
    std::vector<Card> deck;
    int currentCard;

    explicit Chance(int pos);
    ~Chance() override = default;
    void landOn(Player& player, std::vector<Player>& players, Board& board) override;
    void clearOwner() override {}
};
#endif //CHANCE_H