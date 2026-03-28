// TerminalColors.h
#ifndef TERMINALCOLORS_H
#define TERMINALCOLORS_H
#include <string>

namespace TerminalColors {
    inline const std::string RESET   = "\033[0m";
    inline const std::string RED     = "\033[31m";
    inline const std::string GREEN   = "\033[32m";
    inline const std::string YELLOW  = "\033[33m";
    inline const std::string BLUE    = "\033[34m";
    inline const std::string MAGENTA = "\033[35m";
    inline const std::string CYAN    = "\033[36m";
    inline const std::string GRAY    = "\033[90m";
    inline const std::string BOLD    = "\033[1m";
    inline const std::string BLACK   = "\033[30m";
}
#endif