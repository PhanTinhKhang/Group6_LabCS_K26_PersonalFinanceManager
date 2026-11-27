#ifndef UITHEME_H
#define UITHEME_H

#include <string>
#include <iostream>

#ifdef _WIN32
extern "C" __declspec(dllimport) int __stdcall SetConsoleOutputCP(unsigned int);
extern "C" __declspec(dllimport) int __stdcall SetConsoleCP(unsigned int);
extern "C" __declspec(dllimport) void* __stdcall GetStdHandle(unsigned long);
extern "C" __declspec(dllimport) int __stdcall GetConsoleMode(void*, unsigned long*);
extern "C" __declspec(dllimport) int __stdcall SetConsoleMode(void*, unsigned long);
#endif

namespace Color {
    inline const char* RESET = "\033[0m";
    inline const char* BOLD = "\033[1m";
    inline const char* DIM = "\033[2m";
    inline const char* RED = "\033[31m";
    inline const char* GREEN = "\033[32m";
    inline const char* YELLOW = "\033[33m";
    inline const char* BLUE = "\033[34m";
    inline const char* MAGENTA = "\033[35m";
    inline const char* CYAN = "\033[36m";
    inline const char* WHITE = "\033[37m";
    inline const char* GRAY = "\033[90m";
}

inline void initConsole() {
#ifdef _WIN32
    SetConsoleOutputCP(65001);
    SetConsoleCP(65001);
    void* hOut = GetStdHandle((unsigned long)-11);
    if (hOut != (void*)-1 && hOut != nullptr) {
        unsigned long mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= 0x0004;
            SetConsoleMode(hOut, mode);
        }
    }
#endif
}

inline void printHeader(const std::string& subtitle) {
    initConsole();
    std::cout << Color::CYAN << "┌──────────────────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│  " << Color::BOLD << Color::WHITE << "PERSONAL FINANCE MANAGER" << Color::RESET << Color::CYAN << "  •  "
              << Color::GRAY << subtitle << Color::RESET;
    int used = 31 + static_cast<int>(subtitle.length());
    int pad = 86 - used;
    if (pad < 0) {
        pad = 0;
    }
    std::cout << std::string(pad, ' ') << Color::CYAN << "│\n";
    std::cout << "└──────────────────────────────────────────────────────────────────────────────────────┘\n" << Color::RESET;
}

#endif
