// Trading.h
#ifndef TRADING_H
#define TRADING_H
#include <vector>
#include <algorithm>
#include <iostream>
#include "Player.h"
#include "SquareTypes/Property/Property.h"
#include "TerminalColors.h"

struct TradeOffer {
    Player* buyer;
    Player* seller;
    Property* desired;
    Property* offered;
    int cashTop;
};

class Trading {
public:

    static bool allPropertiesBought(const std::vector<Player>& players) {
        int activePlayers = 0;
        for (const auto& p : players)
            if (!p.bankrupt) activePlayers++;
        if (activePlayers <= 2) return true;

        int totalProperties = 0;
        for (const auto& player : players)
            totalProperties += static_cast<int>(player.ownedProperties.size());
        return totalProperties >= 22;
    }

    static void executeTrades(std::vector<Player>& players) {
        for (auto& buyer : players) {
            if (buyer.bankrupt) continue;
            if (buyer.money < 300) continue;

            for (auto& seller : players) {
                if (&buyer == &seller || seller.bankrupt) continue;
                if (isCloseToWinning(seller, players)) continue;

                for (auto* sq : seller.ownedProperties) {
                    auto* prop = dynamic_cast<Property*>(sq);
                    if (!prop) continue;

                    int buyerDesire = propertyDesire(buyer, prop);
                    if (buyerDesire == 0) continue;
                    int sellerDesire = propertyDesire(seller, prop);
                    if (buyerDesire <= sellerDesire) continue;
                    if (!bringsCloserToSet(buyer, prop)) continue;
                    if (wouldCompleteSet(buyer, prop) && buyerHasHouses(buyer)) continue;

                    // build initial offer
                    TradeOffer offer = buildOffer(buyer, seller, prop);
                    if (!isValidOffer(offer)) continue;

                    // seller evaluates — accept, counter, or reject
                    TradeResult result = sellerEvaluate(offer, seller, players);

                    if (result == TradeResult::Accept) {
                        executeOffer(offer);
                    } else if (result == TradeResult::Counter) {
                        TradeOffer counter = buildCounterOffer(offer, seller, buyer);
                        if (isValidOffer(counter) && buyerEvaluate(counter, buyer)) {
                            executeOffer(counter);
                        }
                    }
                    // if Reject, do nothing
                    break;
                }
            }
        }
    }

private:

    enum class TradeResult { Accept, Counter, Reject };

    // build the best offer buyer can make for desired property
    static TradeOffer buildOffer(Player& buyer, Player& seller, Property* desired) {
        TradeOffer offer;
        offer.buyer   = &buyer;
        offer.seller  = &seller;
        offer.desired = desired;
        offer.offered = nullptr;
        offer.cashTop = 0;

        int desiredVal = propertyValue(seller, desired);

        // first try: pure cash
        int cashOffer = desired->price + (propertyDesire(buyer, desired) * 75);
        cashOffer = std::min(cashOffer, desired->price * 2); // cap at 2x

        if (cashOffer >= desiredVal && buyer.money - cashOffer >= 300) {
            offer.cashTop = cashOffer;
            return offer;
        }

        // second try: property + cash
        Property* bestSwap = findBestSwapProperty(buyer, seller, desired);
        if (bestSwap != nullptr) {
            int swapVal  = propertyValue(buyer, bestSwap);
            int cashGap  = desiredVal - swapVal;
            // buyer pays gap, or receives change if their property is worth more
            if (cashGap > 0 && buyer.money - cashGap < 300) {
                offer.offered = nullptr; // can't afford it
            } else {
                offer.offered = bestSwap;
                offer.cashTop = cashGap;
            }
        }

        return offer;
    }

    // find the best property buyer can offer that seller would want
    static Property* findBestSwapProperty(Player& buyer, Player& seller,
                                           Property* desired) {
        Property* best = nullptr;
        int bestScore  = 0;

        for (auto* sq : buyer.ownedProperties) {
            auto* prop = dynamic_cast<Property*>(sq);
            if (!prop) continue;

            // buyer won't offer something that completes their own set
            if (wouldCompleteSet(buyer, prop)) continue;

            // buyer won't offer something they need as much as seller does
            int buyerNeed  = propertyDesire(buyer, prop);
            int sellerNeed = propertyDesire(seller, prop);
            if (buyerNeed >= sellerNeed) continue;

            // score = how much seller wants it
            int score = sellerNeed * 100 + prop->price;
            if (score > bestScore) {
                bestScore = score;
                best      = prop;
            }
        }
        return best;
    }

    // seller decides: accept, counter, or reject
    static TradeResult sellerEvaluate(const TradeOffer& offer,
                                       Player& seller,
                                       const std::vector<Player>& players) {
        using namespace TerminalColors;
        int desiredVal = propertyValue(seller, offer.desired);

        // calculate total value seller receives
        int totalReceived = offer.cashTop; // cash component
        if (offer.cashTop < 0) totalReceived = 0; // seller pays out in this case

        int totalGiven = 0; // value seller gives up
        if (offer.offered != nullptr) {
            totalGiven    += propertyValue(seller, offer.offered); // they receive this prop
            totalReceived += propertyValue(seller, offer.offered);
        }

        // what seller gives up
        totalGiven = desiredVal;

        // accept if they receive fair value
        if (totalReceived >= desiredVal * 0.9) {
            std::cout << TerminalColors::GREEN << "[Trade] " << RESET
                      << "Player " << seller.ID
                      << " accepted offer from Player " << offer.buyer->ID
                      << " for " << offer.desired->name << std::endl;
            return TradeResult::Accept;
        }

        // counter if close (within 30% of desired value)
        if (totalReceived >= desiredVal * 0.7) {
            std::cout << TerminalColors::YELLOW << "[Trade] " << RESET
                      << "Player " << seller.ID
                      << " countered offer from Player " << offer.buyer->ID
                      << " for " << offer.desired->name << std::endl;
            return TradeResult::Counter;
        }

        // reject
        std::cout << TerminalColors::RED << "[Trade] " << RESET
                  << "Player " << seller.ID
                  << " rejected offer from Player " << offer.buyer->ID
                  << " for " << offer.desired->name << std::endl;
        return TradeResult::Reject;
    }

    // seller builds a counteroffer — asks for more cash
    static TradeOffer buildCounterOffer(const TradeOffer& original,
                                         Player& seller, Player& buyer) {
        TradeOffer counter = original;
        int desiredVal     = propertyValue(seller, original.desired);

        // seller asks for 10% more than original offer to meet their value
        int shortfall  = desiredVal - original.cashTop;
        counter.cashTop = original.cashTop + static_cast<int>(shortfall * 0.5);
        counter.cashTop = std::min(counter.cashTop, original.desired->price * 2);

        std::cout << TerminalColors::YELLOW << "[Trade] " << TerminalColors::RESET
                  << "Player " << seller.ID << " counters: wants $"
                  << counter.cashTop << " for " << original.desired->name << std::endl;

        return counter;
    }

    // buyer decides whether to accept counteroffer
    static bool buyerEvaluate(const TradeOffer& counter, Player& buyer) {
        // accept if they can afford it and it's under 2x face value
        if (counter.cashTop > counter.desired->price * 2) return false;
        if (buyer.money - counter.cashTop < 300) return false;
        return true;
    }

    // execute a finalised trade offer
    static void executeOffer(const TradeOffer& offer) {
        using namespace TerminalColors;
        Player& buyer  = *offer.buyer;
        Player& seller = *offer.seller;

        // transfer desired property to buyer
        offer.desired->owner = &buyer;
        buyer.colorMap[offer.desired->color].insert(offer.desired);
        seller.colorMap[offer.desired->color].erase(offer.desired);
        buyer.ownedProperties.push_back(offer.desired);
        seller.ownedProperties.erase(
            std::remove(seller.ownedProperties.begin(),
                        seller.ownedProperties.end(),
                        static_cast<Square*>(offer.desired)),
            seller.ownedProperties.end()
        );

        // transfer offered property to seller if part of deal
        if (offer.offered != nullptr) {
            offer.offered->owner = &seller;
            seller.colorMap[offer.offered->color].insert(offer.offered);
            buyer.colorMap[offer.offered->color].erase(offer.offered);
            seller.ownedProperties.push_back(offer.offered);
            buyer.ownedProperties.erase(
                std::remove(buyer.ownedProperties.begin(),
                            buyer.ownedProperties.end(),
                            static_cast<Square*>(offer.offered)),
                buyer.ownedProperties.end()
            );
        }

        // handle cash
        if (offer.cashTop > 0) {
            buyer.pay(offer.cashTop);
            seller.receive(offer.cashTop);
        } else if (offer.cashTop < 0) {
            seller.pay(-offer.cashTop);
            buyer.receive(-offer.cashTop);
        }

        // print result
        std::cout << GREEN << "[Trade] EXECUTED: " << RESET
                  << "Player " << buyer.ID << " received " << offer.desired->name;
        if (offer.offered != nullptr)
            std::cout << " for " << offer.offered->name;
        if (offer.cashTop > 0)
            std::cout << " + $" << offer.cashTop;
        else if (offer.cashTop < 0)
            std::cout << " + $" << -offer.cashTop << " back";
        std::cout << std::endl;
    }

    static bool isValidOffer(const TradeOffer& offer) {
        if (offer.desired == nullptr) return false;
        if (offer.offered == nullptr && offer.cashTop <= 0) return false;
        if (offer.cashTop > offer.desired->price * 2) return false;
        return true;
    }

    static int propertyDesire(const Player& player, const Property* prop) {
        auto it = player.colorMap.find(prop->color);
        if (it == player.colorMap.end()) return 0;
        return static_cast<int>(it->second.size());
    }

    static int propertyValue(const Player& player, const Property* prop) {
        int colorCount = player.colorMap.count(prop->color) ?
            static_cast<int>(player.colorMap.at(prop->color).size()) : 0;
        return prop->price + (colorCount * 50);
    }

    static bool bringsCloserToSet(const Player& buyer, const Property* prop) {
        auto it = buyer.colorMap.find(prop->color);
        if (it == buyer.colorMap.end()) return false;
        int owned  = static_cast<int>(it->second.size());
        int needed = colorSetSize(prop->color);
        return owned >= (needed / 2);
    }

    static bool wouldCompleteSet(const Player& player, const Property* prop) {
        auto it = player.colorMap.find(prop->color);
        if (it == player.colorMap.end()) return false;
        int owned  = static_cast<int>(it->second.size());
        int needed = colorSetSize(prop->color);
        return owned + 1 >= needed;
    }

    static bool buyerHasHouses(const Player& buyer) {
        for (auto* sq : buyer.ownedProperties) {
            auto* prop = dynamic_cast<Property*>(sq);
            if (prop && prop->houseCount > 0) return true;
        }
        return false;
    }

    static bool isCloseToWinning(const Player& player,
                                  const std::vector<Player>& players) {
        for (const auto& pair : player.colorMap) {
            int owned  = static_cast<int>(pair.second.size());
            int needed = colorSetSize(pair.first);
            if (owned >= needed)
                for (const auto* prop : pair.second)
                    if (prop->houseCount > 0) return true;
        }
        return false;
    }

    static int colorSetSize(const std::string& color) {
        if (color == "Brown" || color == "Dark Blue") return 2;
        return 3;
    }
};
#endif //TRADING_H
