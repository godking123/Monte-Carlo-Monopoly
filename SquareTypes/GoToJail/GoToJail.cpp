
#include "GoToJail.h"
#include "../../Player.h"
#include <iostream>
#include "../.././TerminalColors.h"
#ifdef _WIN32
#include <windows.h>
#endif

void GoToJail::landOn(Player& player)
{
    #ifdef _WIN32
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD dwMode = 0;
    GetConsoleMode(hOut, &dwMode);
    SetConsoleMode(hOut, dwMode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
    #endif
    using namespace TerminalColors;
    std::cout << RED << "[Go To Jail]" << RESET << " Player " << player.ID << " landed on Go To Jail." << std::endl;
    player.inJail = true;
    player.position = 10;
}

