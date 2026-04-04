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
    float alpha;


   explicit Player(const int newID, int startingMoney = 1500, float alphaValue = 0.5f)
    : ID(newID), money(startingMoney), position(0), bankrupt(false), alpha(alphaValue),
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
