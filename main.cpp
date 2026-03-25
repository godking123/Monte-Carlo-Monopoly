#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "Property.h"

int main() {
    std::cout << "Starting Monte Carlo Monopoly Simulation..." << std::endl;
    Board board;
    Dice dice;
    int numPlayers = 4;
    std::vector<Player> players;
    for (int i = 0; i < numPlayers; ++i) {
        players.push_back(Player(i));
    }

    int turns = 10;
    for (int t = 1; t <= turns; ++t) {
        for (auto& player : players) {
            if (player.bankrupt) continue;
            int roll = dice.rollTwo();
            player.move(roll);
            auto* space = board.getSquareAt(player.position);

            if (space != nullptr) {
                space->landOn(player);

                if (player.money < 0) {
                    player.bankrupt = true;
                    // use ownedProperties directly instead of scanning the board
                    for (auto* prop : player.ownedProperties) {
                        prop->owner = nullptr;
                    }
                    player.ownedProperties.clear();
                }
            }
        }
    }

    std::cout << "\nSimulation ended after " << turns << " turns." << std::endl;
    std::cout << "Final Results:" << std::endl;
    for (const auto& player : players) {
        std::cout << "Player " << player.ID
                  << " - Money: $" << player.money
                  << (player.bankrupt ? " (Bankrupt)" : "") << std::endl;

        if (player.ownedProperties.empty()) {
            std::cout << "  No properties owned." << std::endl;
        } else {
            std::cout << "  Properties:" << std::endl;
            for (const auto* prop : player.ownedProperties) {
                std::cout << "    - " << prop->name
                          << " (rent: $" << prop->rent << ")" << std::endl;
            }
        }
    }
    return 0;
}