#include "Chance.h"
#include "../../Player.h"
#include <iostream>
#include "../.././TerminalColors.h"
#ifdef _WIN32
#include <windows.h>
#endif

void Chance::landOn(Player& player) {
    #ifdef _WIN32
        // enable ANSI escape codes on Windows
        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        DWORD dwMode = 0;
        GetConsoleMode(hOut, &dwMode);
        SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;
    player.position += move;
    player.money += cost;

    std::cout << RED << "[Chance] " << RESET << "Player " << player.ID << " moved to position " << player.position << " and gained " << cost << "." << std::endl;
}
