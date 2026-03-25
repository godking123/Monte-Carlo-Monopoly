#ifndef PLAYER_H
#define PLAYER_H
#include "SquareTypes/Property/Property.h"
#include <vector>

class Player {
public:
    int ID;
    int money;
    int position;
    bool bankrupt;
    bool inJail;
    int turnsInJail; // In simple monopoly 3 turns must be spent in jail
    std::vector<Property*> ownedProperties;


    explicit Player(const int newID)
        : ID(newID), money(1500), position(0), bankrupt(false), inJail(false), turnsInJail(0){}

    void move(int steps);
    void pay(int amount);
    void receive(int amount);
};



#endif //PLAYER_H
