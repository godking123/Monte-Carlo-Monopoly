// CommunityChest.h
#ifndef COMMUNITYCHEST_H
#define COMMUNITYCHEST_H
#include "../Square.h"
#include "../Card.h"
#include <vector>

class CommunityChest : public Square {
public:
    std::vector<Card> deck;
    int currentCard;

    explicit CommunityChest(int pos);
    ~CommunityChest() override = default;
    void landOn(Player& player, std::vector<Player>& players, Board& board) override;
    void clearOwner() override {}
};

#endif //COMMUNITYCHEST_H