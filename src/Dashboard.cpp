#include "../include/Dashboard.h"
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
    std::cout << "========================================================================================\n";
    std::cout << "                      PERSONAL FINANCE MANAGER - DASHBOARD CLI                          \n";
    std::cout << "                   Faculty of Information Technology - VNU-HCMUS                        \n";
    std::cout << "========================================================================================\n";

    double totalBalance = calculateTotalBalance(wallets);
    std::string totalStr = formatCurrency(totalBalance);

    std::cout << "                             FINANCIAL SUMMARY OVERVIEW                                 \n";
    std::cout << "+--------------------------------------------------------------------------------------+\n";
    std::cout << "|  TOTAL AGGREGATE BALANCE: "
              << std::right << std::setw(56) << totalStr << "   |\n";
    std::cout << "+------+-------------+---------------------+------------------------+------------------+\n";
    std::cout << "|  No. | Wallet ID   | Wallet Name         | Current Balance        | Status           |\n";
    std::cout << "|------+-------------+---------------------+------------------------+------------------|\n";

    int count = wallets.getSize();
    if (count == 0) {
        std::cout << "|  No active wallets found.                                                            |\n";
    } else {
        for (int i = 0; i < count; ++i) {
            std::string numStr = (i + 1 < 10 ? "0" : "") + std::to_string(i + 1);
            std::string idStr = wallets[i].get_ID();
            std::string nameStr = wallets[i].get_NAME();
            std::string balanceStr = formatCurrency(wallets[i].get_BALANCE());

            std::cout << "|  " << std::setw(2) << numStr << "  | "
                      << std::left << std::setw(11) << idStr << " | "
                      << std::left << std::setw(19) << nameStr << " | "
                      << std::right << std::setw(22) << balanceStr << " | "
                      << std::left << std::setw(16) << "Active" << " |\n";
        }
    }
    std::cout << "+------+-------------+---------------------+------------------------+------------------+\n";

    std::cout << "\n================================== MAIN NAVIGATION MENU =================================\n";
    std::cout << "  [1] Record Income Transaction       (Add daily revenue/deposit)\n";
    std::cout << "  [2] Record Expense Transaction      (Add daily expense/payment)\n";
    std::cout << "  [3] Wallet Management               (Add / Edit / Remove Wallets)\n";
    std::cout << "  [4] Master Data Management          (Expense Categories & Income Sources)\n";
    std::cout << "  [5] Recurring Transactions Setup    (Monthly Automation Rules)\n";
    std::cout << "  [6] Statistics & Financial Reports  (Time, Wallet, Multi-Year Analytics)\n";
    std::cout << "  [7] Data Persistence                (Save to Disk / Reload File)\n";
    std::cout << "  [0] Exit Application\n";
    std::cout << "========================================================================================\n";
}

MenuAction promptMenuChoice() {
    std::cout << " [?] Enter your selection (0 - 7): ";
    int choice;
    if (!(std::cin >> choice)) {
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
    std::cout << "\n [*] Press [Enter] to continue...";
    std::cin.get();
}
