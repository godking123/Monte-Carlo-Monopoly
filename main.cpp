#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "SquareTypes/Property/Property.h"
#include "SquareTypes/GoToJail/GoToJail.h"
#include "SquareTypes/Jail/Jail.h"

int main()
{
    std::cout << "Starting Monte Carlo Monopoly Simulation..." << std::endl;
    Board board;
    Dice dice;
    int numPlayers = 4;
    std::vector<Player> players;
    for (int i = 0; i < numPlayers; ++i)
    {
        players.push_back(Player(i));
    }

    int turns = 50;
    for (int t = 1; t <= turns; ++t)
    {
        for (auto& player : players)
        {
            // Bankruptcy Checkk
            if (player.bankrupt) continue;
            // Jail Check
            if (player.inJail) {
                // Roll for doubles first
                int roll1 = dice.roll();
                int roll2 = dice.roll();
                if (roll1 == roll2) {
                    // rolled doubles, get out free
                    player.inJail = false;
                    player.turnsInJail = 0;
                    player.move(roll1 + roll2);
                    std::cout << "Player " << player.ID << " rolled doubles, out of jail!" << std::endl;
                } else {
                    // no doubles, serve the turn
                    player.turnsInJail++;
                    if (player.turnsInJail >= 3) {
                        // served 3 turns, must pay fine
                        player.pay(50);
                        player.inJail = false;
                        player.turnsInJail = 0;
                        std::cout << "Player " << player.ID << " paid $50 fine, out of jail." << std::endl;
                    } else {
                        std::cout << "Player " << player.ID << " stuck in jail, turn " << player.turnsInJail << std::endl;
                    }
                }
                continue;
            }

            if (player.bankrupt) continue;
            int roll = dice.rollTwo();
            player.move(roll);
            auto* space = board.getSquareAt(player.position);

            if (space != nullptr)
            {
                space->landOn(player);
                // Bankruptcy Checkk
                if (player.money < 0)
                {
                    player.bankrupt = true;
                    for (auto* prop : player.ownedProperties)
                    {
                        prop->owner = nullptr;
                    }
                    player.ownedProperties.clear();
                }
            }
        }
    }

    std::cout << "\nSimulation ended after " << turns << " turns." << std::endl;
    std::cout << "Final Results:" << std::endl;
    for (const auto& player : players)
    {
        std::cout << "Player " << player.ID
            << " - Money: $" << player.money
            << (player.bankrupt ? " (Bankrupt)" : "") << std::endl;

        if (player.ownedProperties.empty())
        {
            std::cout << "  No properties owned." << std::endl;
        }
        else
        {
            std::cout << "  Properties:" << std::endl;
            for (const auto* prop : player.ownedProperties)
            {
                std::cout << "    - " << prop->name
                    << " (rent: $" << prop->rent << ")" << std::endl;
            }
        }
    }
    return 0;
}
