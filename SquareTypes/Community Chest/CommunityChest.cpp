// CommunityChest.cpp
#include "CommunityChest.h"
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

CommunityChest::CommunityChest(int pos) : Square(pos, "Community Chest"), currentCard(0) {
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
            "Bank error in your favor",
            "Bank error in your favor. Collect $200.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(200);
            }
        },
        {
            "Doctor's fee",
            "Doctor's fee. Pay $50.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.pay(50);
            }
        },
        {
            "Sale of stock",
            "From sale of stock you get $50.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(50);
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
            "Grand Opera Night",
            "Grand Opera Night. Collect $50 from every other player.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                for (auto& other : players) {
                    if (&other != &p && !other.bankrupt) {
                        other.pay(50);
                        p.receive(50);
                    }
                }
            }
        },
        {
            "Holiday Fund matures",
            "Holiday Fund matures. Receive $100.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(100);
            }
        },
        {
            "Income tax refund",
            "Income tax refund. Collect $20.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(20);
            }
        },
        {
            "It is your birthday",
            "It is your birthday. Collect $10 from every player.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                for (auto& other : players) {
                    if (&other != &p && !other.bankrupt) {
                        other.pay(10);
                        p.receive(10);
                    }
                }
            }
        },
        {
            "Life insurance matures",
            "Life insurance matures. Collect $100.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(100);
            }
        },
        {
            "Hospital fees",
            "Pay hospital fees of $100.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.pay(100);
            }
        },
        {
            "School fees",
            "Pay school fees of $50.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.pay(50);
            }
        },
        {
            "Consultancy fee",
            "Receive $25 consultancy fee.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(25);
            }
        },
        {
            "Street repairs",
            "Pay $40 per house, $115 per hotel.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                int total = 0;
                for (auto* sq : p.ownedProperties) {
                    auto* prop = dynamic_cast<Property*>(sq);
                    if (!prop) continue;
                    if (prop->houseCount < 5) total += prop->houseCount * 40;
                    else total += 115;
                }
                p.pay(total);
            }
        },
        {
            "Beauty contest",
            "You have won second prize in a beauty contest. Collect $10.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(10);
            }
        },
        {
            "You inherit $100",
            "You inherit $100.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.receive(100);
            }
        },
        {
            "Get out of jail free",
            "Get out of jail free. Keep until needed.",
            [](Player& p, std::vector<Player>& players, Board& board) {
                p.hasGetOutOfJail = true;
            }
        }
    };

    std::shuffle(deck.begin(), deck.end(), std::mt19937(std::random_device{}()));
}

void CommunityChest::landOn(Player& player, std::vector<Player>& players, Board& board) {
    #ifdef _WIN32
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;

    Card& card = deck[currentCard % deck.size()];
    currentCard++;

    std::cout << YELLOW << "[Community Chest] " << RESET << "Player " << player.ID
              << " drew: \"" << card.name << "\" - " << card.description << std::endl;

    card.effect(player, players, board);
}