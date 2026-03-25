
#ifndef DICE_H
#define DICE_H
#include <random>

class Dice {
public:
    Dice() : rng_(std::random_device{}()), dist_(1, 6) {}
    int roll() { return dist_(rng_); }
    int rollTwo() { return roll() + roll(); }

private:
    std::mt19937 rng_;
    std::uniform_int_distribution<int> dist_;
};

#endif //DICE_H
