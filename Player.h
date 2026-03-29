#ifndef PLAYER_H
#define PLAYER_H
#include <set>
#include <unordered_map>

#include "SquareTypes/Property/Property.h"
#include "SquareTypes/Property/Railroad.h"
#include "SquareTypes/Property/Utility.h"
#include <vector>

class Player {

public:
    int ID;
    int money;
    int position;
    bool bankrupt;
    bool inJail;
    int numRailroads;
    int numUtilities;
    int currDiceRoll;
    bool hasGetOutOfJail;
    int turnsInJail; // In simple monopoly 3 turns must be spent in jail
    std::unordered_map<std::string, std::set<Property*>> colorMap;
    std::vector<Property*> ownedProperties;
    std::vector<Railroad*> ownedRailroads;
    std::vector<Utility*> ownedUtilities;


   explicit Player(const int newID)
    : ID(newID), money(1500), position(0), bankrupt(false),
      inJail(false), turnsInJail(0), numRailroads(-1), numUtilities(0), currDiceRoll(0),
      colorMap({
          {"Brown", {}},
          {"Light Blue", {}},
          {"Pink", {}},
          {"Orange", {}},
          {"Red", {}},
          {"Yellow", {}},
          {"Green", {}},
          {"Dark Blue", {}}
      }), hasGetOutOfJail(false) {}
    ~Player() = default;

    void move(int steps);
    void pay(int amount);
    void receive(int amount);
    bool checkColorMap(const std::string& color);
    void autoBuyHouse(Property* property);
};



#endif //PLAYER_H
