#include <iostream>
#include <vector>
#include "Board.h"
#include "Player.h"
#include "Dice.h"
#include "SquareTypes/Property/Property.h"

#ifdef _WIN32
#include <windows.h>
#endif

// ANSI color codes for terminal output
namespace TerminalColors {
    const std::string RESET   = "\033[0m";
    const std::string RED     = "\033[31m";
    const std::string GREEN   = "\033[32m";
    const std::string YELLOW  = "\033[33m";
    const std::string BLUE    = "\033[34m";
    const std::string MAGENTA = "\033[35m";
    const std::string CYAN    = "\033[36m";
    const std::string GRAY    = "\033[90m";
    const std::string BOLD    = "\033[1m";
}

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

    int turns = 50;
    for (int t = 1; t <= turns; ++t)
    {
        std::cout << BOLD << BLUE << "\n--- Turn " << t << " ---" << RESET << std::endl;

        for (auto& player : players)
        {
            // Bankruptcy Check
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
                    std::cout << GREEN << "  [Jail] Player " << player.ID << " rolled doubles, out of jail!" << RESET << std::endl;
                } else {
                    // no doubles, serve the turn
                    player.turnsInJail++;
                    if (player.turnsInJail >= 3) {
                        // served 3 turns, must pay fine
                        player.pay(50);
                        player.inJail = false;
                        player.turnsInJail = 0;
                        std::cout << YELLOW << "  [Jail] Player " << player.ID << " paid $50 fine, out of jail." << RESET << std::endl;
                    } else {
                        std::cout << RED << "  [Jail] Player " << player.ID << " stuck in jail, turn " << player.turnsInJail << RESET << std::endl;
                    }
                }
                continue;
            }

            if (player.bankrupt) continue;
            int roll = dice.rollTwo();
            player.currDiceRoll = roll;
            player.move(roll);
            auto* space = board.getSquareAt(player.position);

            if (space != nullptr)
            {
                space->landOn(player);

                // Bankruptcy Check
                if (player.money < 0)
                {
                    player.bankrupt = true;
                    player.numUtilities = 0;
                    player.numRailroads = 0;
                    for (Square* square : player.ownedProperties)
                    {
                        square->clearOwner();
                    }
                    player.ownedProperties.clear();
                    std::cout << BOLD << RED << "\n  !!! Player " << player.ID << " HAS GONE BANKRUPT !!!\n" << RESET << std::endl;
                }
            }
        }
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
        }
        std::cout << GRAY << "-------------------------------------------" << RESET << std::endl;
    }
    return 0;
}