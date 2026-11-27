#include "../include/Dashboard.h"
#include "../include/UITheme.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cstdlib>

std::string formatCurrency(double amount) {
    bool negative = (amount < 0.0);
    if (negative) {
        amount = -amount;
    }

    long long intPart = static_cast<long long>(amount);
    long long decPart = static_cast<long long>(std::round((amount - static_cast<double>(intPart)) * 100.0));
    if (decPart >= 100) {
        intPart += 1;
        decPart -= 100;
    }

    std::string intStr = std::to_string(intPart);
    std::string formattedInt = "";
    int len = static_cast<int>(intStr.length());
    for (int i = 0; i < len; ++i) {
        if (i > 0 && (len - i) % 3 == 0) {
            formattedInt += ",";
        }
        formattedInt += intStr[i];
    }

    std::string decStr = std::to_string(decPart);
    if (decStr.length() < 2) {
        decStr = "0" + decStr;
    }

    std::string result = "";
    if (negative) {
        result += "-";
    }
    result += formattedInt + "." + decStr + " VND";
    return result;
}

double calculateTotalBalance(DynamicArray<Wallet>& wallets) {
    double total = 0.0;
    int count = wallets.getSize();
    for (int i = 0; i < count; ++i) {
        total += wallets[i].get_BALANCE();
    }
    return total;
}

void renderDashboard(DynamicArray<Wallet>& wallets) {
    initConsole();

    std::cout << Color::CYAN << "┌──────────────────────────────────────────────────────────────────────────────────────┐\n";
    std::cout << "│  " << Color::BOLD << Color::WHITE << "PERSONAL FINANCE MANAGER" << Color::RESET << Color::CYAN << "  •  "
              << Color::GRAY << "PRO CLI EDITION" << Color::RESET << Color::CYAN
              << std::string(40, ' ') << "│\n";
    std::cout << "│  " << Color::GRAY << "Academic Year 2026-2027  •  VNU-HCM University of Science"
              << Color::CYAN << std::string(27, ' ') << "│\n";
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────┤\n";

    double totalBalance = calculateTotalBalance(wallets);
    std::string totalStr = formatCurrency(totalBalance);
    int count = wallets.getSize();
    std::string countStr = std::to_string(count) + (count == 1 ? " Wallet" : " Wallets");

    int leftLen = 22 + static_cast<int>(totalStr.length());
    int rightLen = 19 + static_cast<int>(countStr.length());
    int midSpaces = 86 - leftLen - rightLen;
    if (midSpaces < 2) {
        midSpaces = 2;
    }

    std::cout << "│  " << Color::WHITE << "Total Net Balance: " << Color::RESET
              << Color::BOLD << Color::GREEN << totalStr << Color::RESET
              << std::string(midSpaces, ' ')
              << Color::GRAY << "Managed Accounts: " << Color::RESET
              << Color::WHITE << countStr << Color::RESET << Color::CYAN << "  │\n";

    std::cout << "├──────┬──────────────────────────────┬──────────────────────────────┬─────────────────┤\n";
    std::cout << "│  ID  │ ACCOUNT / WALLET NAME        │        CURRENT BALANCE (VND) │ STATUS          │\n";
    std::cout << "├──────┼──────────────────────────────┼──────────────────────────────┼─────────────────┤\n";

    if (count == 0) {
        std::cout << "│  No active wallets found in portfolio." << std::string(44, ' ') << "│\n";
    } else {
        for (int i = 0; i < count; ++i) {
            std::string idStr = std::to_string(wallets[i].get_ID());
            std::string nameStr = wallets[i].get_NAME();
            if (nameStr.length() > 28) {
                nameStr = nameStr.substr(0, 25) + "...";
            }
            std::string balanceStr = formatCurrency(wallets[i].get_BALANCE());

            std::cout << "│ " << Color::YELLOW << std::right << std::setw(4) << idStr << Color::RESET << Color::CYAN << " │ "
                      << Color::WHITE << std::left << std::setw(28) << nameStr << Color::RESET << Color::CYAN << " │ "
                      << Color::BOLD << Color::GREEN << std::right << std::setw(28) << balanceStr << Color::RESET << Color::CYAN << " │ "
                      << Color::WHITE << std::left << std::setw(15) << "Active" << Color::RESET << Color::CYAN << " │\n";
        }
    }
    std::cout << "├──────┴──────────────────────────────┴──────────────────────────────┴─────────────────┤\n";

    std::cout << "│  " << Color::BOLD << Color::WHITE << "NAVIGATION MENU" << Color::RESET << Color::CYAN << std::string(69, ' ') << "│\n";
    std::cout << "├──────────────────────────────────────────────────────────────────────────────────────┤\n";
    std::cout << "│  " << Color::GRAY << "OPERATIONS & CASH FLOW" << Color::CYAN << std::string(62, ' ') << "│\n";
    std::cout << "│    " << Color::CYAN << "[1]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Record Income" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Record daily salary, revenue or deposit" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│    " << Color::CYAN << "[2]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Record Expense" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Record daily purchase, bill or expenditure" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│    " << Color::CYAN << "[3]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Wallet Management" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "View, create, edit or remove wallet accounts" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│" << std::string(86, ' ') << "│\n";
    std::cout << "│  " << Color::GRAY << "ANALYTICS & AUTOMATION" << Color::CYAN << std::string(62, ' ') << "│\n";
    std::cout << "│    " << Color::CYAN << "[4]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Master Data Management" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Configure expense categories and income sources" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│    " << Color::CYAN << "[5]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Recurring Transactions" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Set up automated monthly recurring rules" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│    " << Color::CYAN << "[6]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Financial Analytics" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Generate monthly, wallet and multi-year reports" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│    " << Color::CYAN << "[7]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Save & Load Data" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Binary file storage persistence and backups" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "│" << std::string(86, ' ') << "│\n";
    std::cout << "│  " << Color::GRAY << "SYSTEM" << Color::CYAN << std::string(78, ' ') << "│\n";
    std::cout << "│    " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " " << Color::WHITE << std::left << std::setw(26) << "Exit Application" << Color::RESET
              << Color::GRAY << std::left << std::setw(52) << "Safely save database and exit session" << Color::RESET << Color::CYAN << "│\n";
    std::cout << "└──────────────────────────────────────────────────────────────────────────────────────┘\n" << Color::RESET;
}

MenuAction promptMenuChoice() {
    std::cout << "\n  " << Color::BOLD << Color::CYAN << "▸" << Color::RESET << " Select an option [0 - 7]: ";
    int choice;
    if (!(std::cin >> choice)) {
        if (std::cin.eof()) {
            return MenuAction::EXIT;
        }
        std::cin.clear();
        std::string discard;
        std::getline(std::cin, discard);
        return MenuAction::INVALID;
    }
    std::string remainder;
    std::getline(std::cin, remainder);
    if (choice >= 0 && choice <= 7) {
        return static_cast<MenuAction>(choice);
    }
    return MenuAction::INVALID;
}

void clearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void pauseScreen() {
    std::cout << "\n  " << Color::GRAY << "Press [Enter] to return to dashboard..." << Color::RESET;
    std::cin.get();
}
