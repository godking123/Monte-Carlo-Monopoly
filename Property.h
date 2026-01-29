//
// Created by rajit on 1/28/2026.
//

#ifndef PROPERTY_H
#define PROPERTY_H

class Property {
public:
    int cost;
    int position;
    int rent;
    Property(const int newCost, const int newPosition, const int newRent) {
        cost = newCost;
        position = newPosition;
        rent = newRent;
    }
};






#endif //PROPERTY_H
