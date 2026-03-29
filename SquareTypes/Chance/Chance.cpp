// Chance.cpp
#include "Chance.h"
#include "../../Player.h"
#include "../../Board.h"
#include "../../TerminalColors.h"
#include "../../SquareTypes/Property/Property.h"
#include <iostream>
#include <algorithm>
#include <random>
#ifdef _WIN32
#include <windows.h>
#endif

Chance::Chance(int pos) : Square(pos, "Chance"), currentCard(0) {
    deck = {
        {
            "Advance to Go",
            "Advance to Go. Collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.position = 0;
                p.receive(200);
            }
        },
        {
            "Advance to Illinois Avenue",
            "Advance to Illinois Avenue. If you pass Go collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                if (p.position > 24) p.receive(200);
                p.position = 24;
                board.getSquareAt(24)->landOn(p, players, board);
            }
        },
        {
            "Advance to St. Charles Place",
            "Advance to St. Charles Place. If you pass Go collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                if (p.position > 11) p.receive(200);
                p.position = 11;
                board.getSquareAt(11)->landOn(p, players, board);
            }
        },
        {
            "Advance to nearest railroad",
            "Advance to nearest railroad.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                int railroads[] = {5, 15, 25, 35};
                for (int r : railroads) {
                    if (p.position < r) {
                        p.position = r;
                        board.getSquareAt(r)->landOn(p, players, board);
                        return;
                    }
                }
                // wrapped past 35 — go to Reading Railroad
                p.receive(200);
                p.position = 5;
                board.getSquareAt(5)->landOn(p, players, board);
            }
        },
        {
            "Advance to nearest utility",
            "Advance to nearest utility.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                // utilities at 12 and 28
                if (p.position < 12 || p.position >= 28) {
                    if (p.position >= 28) p.receive(200); // passed Go
                    p.position = 12;
                } else {
                    p.position = 28;
                }
                board.getSquareAt(p.position)->landOn(p, players, board);
            }
        },
        {
            "Bank pays dividend",
            "Bank pays you a dividend of $50.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(50);
            }
        },
        {
            "Get out of jail free",
            "Get out of jail free. Keep until needed.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.hasGetOutOfJail = true;
            }
        },
        {
            "Go back 3 spaces",
            "Go back 3 spaces.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.position = (p.position - 3 + 40) % 40;
                board.getSquareAt(p.position)->landOn(p, players, board);
            }
        },
        {
            "Go to Jail",
            "Go directly to Jail. Do not pass Go, do not collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.position = 10;
                p.inJail = true;
                p.turnsInJail = 0;
            }
        },
        {
            "Chairman of the Board",
            "You have been elected chairman of the board. Pay each player $50.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                for (auto& other : players) {
                    if (&other != &p && !other.bankrupt) {
                        p.pay(50);
                        other.receive(50);
                    }
                }
            }
        },
        {
            "Building loan matures",
            "Your building loan matures. Collect $150.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(150);
            }
        },
        {
            "Take a trip to Reading Railroad",
            "Take a trip to Reading Railroad. If you pass Go collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                if (p.position > 5) p.receive(200);
                p.position = 5;
                board.getSquareAt(5)->landOn(p, players, board);
            }
        },
        {
            "Advance to Boardwalk",
            "Advance to Boardwalk.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.position = 39;
                board.getSquareAt(39)->landOn(p, players, board);
            }
        },
        {
            "Pay poor tax",
            "Pay poor tax of $15.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.pay(15);
            }
        },
        {
            "Speeding fine",
            "Speeding fine. Pay $15.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.pay(15);
            }
        },
        {
            "Street repairs",
            "Make general repairs. Pay $25 per house, $100 per hotel.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                int total = 0;
                for (auto* sq : p.ownedProperties) {
                    auto* prop = dynamic_cast<Property*>(sq);
                    if (!prop) continue;
                    if (prop->houseCount < 5) total += prop->houseCount * 25;
                    else total += 100;
                }
                p.pay(total);
            }
        }
    };

    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
}

void Chance::landOn(Player& player, std::vector<Player>& players, Board& board) {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;

    Card& card = deck[currentCard % deck.size()];
    currentCard++;

    std::cout << RED << "[Chance] " << RESET << "Player " << player.ID
              << " drew: \"" << card.name << "\" - " << card.description << std::endl;

    card.effect(player, players, board);
}