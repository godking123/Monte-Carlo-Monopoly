// Card.h
#ifndef CARD_H
#define CARD_H
#include <string>
#include <functional>
#include <vector>

class Player;
class Board;

struct Card {
    std::string name;
    std::string description;
    std::function<void(Player&, std::vector<Player>&, Board&)> effect;
};

#endif