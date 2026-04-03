#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "SquareTypes/Property/Property.h"
#include "TerminalColors.h"
#include "Trading.h"

#ifdef _WIN32
#include <windows.h>
#endif

int main()
    {
    #ifdef _WIN32
        // enable ANSI escape codes on Windows
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;

    std::cout << BOLD << MAGENTA << "===========================================" << RESET << std::endl;
    std::cout << BOLD << CYAN    << "  Starting Monte Carlo Monopoly Simulation" << RESET << std::endl;
    std::cout << BOLD << MAGENTA << "===========================================\n" << RESET << std::endl;

    Board board;
    Dice dice;
    int numPlayers = 4;
    std::vector<Player> players;
    for (int i = 0; i < numPlayers; ++i)
    {
        players.emplace_back(i);
    }

    int turns = 1;
    int numBankrupt = 0;
    
    // FIX 1: Stop the game when 1 player is left (numPlayers - 1)
    while (numBankrupt < numPlayers - 1)
    {
        if (turns > 100) {
            std::cout << BOLD << RED << "\n  !!! Simulation ended after " << turns << " turns. !!!" << RESET << std::endl;
            break;
        }
        std::cout << BOLD << BLUE << "\n--- Turn " << turns << " ---" << RESET << std::endl;

        for (auto& player : players)
        {
            // Bankruptcy Check
            if (player.bankrupt) continue;

            bool skipMovement = false;

            // Jail Check
            if (player.inJail) {
                if (player.hasGetOutOfJail) {
                    player.inJail = false;
                    player.turnsInJail = 0;
                    player.hasGetOutOfJail = false;
                    std::cout << GREEN << "  [Jail] Player " << player.ID
                              << " used Get Out of Jail Free card!" << RESET << std::endl;
                } else {
                    int roll1 = dice.roll();
                    int roll2 = dice.roll();
                    player.currDiceRoll = roll1 + roll2;

                    if (roll1 == roll2) {
                        player.inJail = false;
                        player.turnsInJail = 0;
                        std::cout << GREEN << "  [Jail] Player " << player.ID
                                  << " rolled doubles, out of jail!" << RESET << std::endl;
                    } else {
                        player.turnsInJail++;
                        if (player.turnsInJail >= 3) {
                            player.pay(50);
                            player.inJail = false;
                            player.turnsInJail = 0;
                            std::cout << YELLOW << "  [Jail] Player " << player.ID
                                      << " paid $50 fine, out of jail." << RESET << std::endl;
                        } else {
                            std::cout << RED << "  [Jail] Player " << player.ID
                                      << " stuck in jail, turn " << player.turnsInJail << RESET << std::endl;
                            skipMovement = true;
                        }
                    }
                }
            } else {
                player.currDiceRoll = dice.rollTwo();
            }

            // Move and Land (applies to normal rolls AND leaving jail)
            if (!skipMovement) {
                player.move(player.currDiceRoll);
                auto* space = board.getSquareAt(player.position);

                if (space != nullptr)
                {
                    space->landOn(player, players, board);

                    // Bankruptcy Check
                    if (player.money < 0) {
                        player.bankrupt = true;
                        numBankrupt++;
                        player.numUtilities = 0;
                        player.numRailroads = 0;
                        player.colorMap.clear();
                        for (Square* square : player.ownedProperties) {
                            square->clearOwner();
                            square->clearHouses();
                        }
                        player.ownedRailroads.clear();
                        player.ownedUtilities.clear();
                        player.ownedProperties.clear();
                        std::cout << BOLD << RED << "\n  !!! Player " << player.ID << " HAS GONE BANKRUPT !!!\n" << RESET << std::endl;
                    }
                }
            }

            // Buy houses for properties in color sets
            if (!player.bankrupt) {
                for (const auto& pair : player.colorMap) {
                    for (auto* prop : pair.second) {
                        player.autoBuyHouse(prop);
                    }
                }
            }

            if (Trading::allPropertiesBought(players)) {
                Trading::executeTrades(players);
            }
        }
        turns++;
    }

    std::cout << "\n" << BOLD << MAGENTA << "===========================================" << RESET << std::endl;
    std::cout << BOLD << CYAN << "  Simulation ended after " << turns << " turns." << RESET << std::endl;
    std::cout << BOLD << MAGENTA << "===========================================" << RESET << std::endl;

    std::cout << BOLD << YELLOW << "\nFinal Results:" << RESET << std::endl;
    for (const auto& player : players)
    {
        std::string statusColor = player.bankrupt ? RED : GREEN;

        std::cout << BOLD << "Player " << player.ID << RESET
                  << " - Money: " << statusColor << "$" << player.money << RESET
                  << (player.bankrupt ? (RED + " (Bankrupt)" + RESET) : "") << std::endl;

        if (player.ownedProperties.empty())
        {
            std::cout << "  " << GRAY << "No properties owned." << RESET << std::endl;
        }
        else
        {
            std::cout << "  Properties:" << std::endl;
            for (const auto* prop : player.ownedProperties)
            {
                std::cout << CYAN << "    - " << prop->name << RESET << std::endl;
            }
            std::cout << "  Railroads: " << player.numRailroads + 1 << std::endl;
            for (const auto* railroad : player.ownedRailroads)
            {
                std::cout << BLACK << "    - " << railroad->name << RESET << std::endl;
            }
            std::cout << "  Utilities: " << player.numUtilities << std::endl;
            for (const auto* utility : player.ownedUtilities)
            {
                std::cout << YELLOW << "    - " << utility->name << RESET << std::endl;
            }

            std::cout << "  Color Sets:" << std::endl;
            if (player.colorMap.empty())
            {
                std::cout << GRAY << "    No colored properties collected yet." << RESET << std::endl;
            }
            else
            {
                for (const auto& pair : player.colorMap)
                {
                    std::cout << GREEN << "    [" << pair.first << "] " << RESET << "- " << pair.second.size() << " properties owned" << std::endl;
                    for (const auto* prop : pair.second)
                    {
                        std::cout << GRAY << "      - " << prop->name << " (" << prop->houseCount << " houses)" << RESET << std::endl;
                    }
                }
            }
        }
        std::cout << GRAY << "-------------------------------------------" << RESET << std::endl;
    }
    return 0;
}