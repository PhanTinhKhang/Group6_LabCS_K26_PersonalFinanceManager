#ifndef DASHBOARD_H
#define DASHBOARD_H

#include <string>
#include "Wallet.h"
#include "dynamicArray.h"

enum class MenuAction {
    EXIT = 0,
    RECORD_INCOME = 1,
    RECORD_EXPENSE = 2,
    MANAGE_WALLETS = 3,
    MANAGE_MASTER_DATA = 4,
    RECURRING_TRANSACTIONS = 5,
    STATISTICS_REPORTS = 6,
    PERSISTENCE_SETTINGS = 7,
    INVALID = -1
};

std::string formatCurrency(double amount);
double calculateTotalBalance(DynamicArray<Wallet>& wallets);
void renderDashboard(DynamicArray<Wallet>& wallets);
MenuAction promptMenuChoice();
void clearScreen();
void pauseScreen();

#endif
