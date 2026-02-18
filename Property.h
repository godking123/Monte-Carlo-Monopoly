#ifndef PROPERTY_H
#define PROPERTY_H
#include <string>

class Property {
public:
    std::string name;
    int cost;
    int position;
    int rent;
    int owner;
    Property(const std::string& newName, const int newCost, const int newPosition, const int newRent) {
        name = newName;
        cost = newCost;
        position = newPosition;
        rent = newRent;
        owner = -1;
    }
    bool isOwned() const;
};






#endif //PROPERTY_H
