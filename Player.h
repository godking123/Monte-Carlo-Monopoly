#ifndef PLAYER_H
#define PLAYER_H

class Player {
public:
    int ID;
    int money;
    int position;
    bool bankrupt;

    explicit Player(const int newID)
        : ID(newID), money(0), position(0), bankrupt(false) {}

    void move(int steps);
    void pay(int amount);
    void receive(int amount);
};



#endif //PLAYER_H
