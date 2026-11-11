#include "../include/RecurringTransaction.h"
#include "../include/dynamicArray.h"
#include <iostream>
#include <iomanip>
#include <string>

struct IdNamePair {
    std::string id;
    std::string name;
};

static const IdNamePair CATEGORY_SOURCE_MAP[] = {
    {"C01", "Internet & Utilities"},
    {"C02", "Housing / Rent"},
    {"C03", "Communication"},
    {"S01", "Salary / Main Job"},
    {"S02", "Freelance & Bonus"}
};
static const int CATEGORY_SOURCE_MAP_SIZE = 5;

static const IdNamePair WALLET_MAP[] = {
    {"W01", "Techcombank Main"},
    {"W02", "Cash Wallet"},
    {"W03", "Momo E-Wallet"}
};
static const int WALLET_MAP_SIZE = 3;

std::string getCategoryOrSourceName(const std::string& id) {
    for (int i = 0; i < CATEGORY_SOURCE_MAP_SIZE; i++) {
        if (CATEGORY_SOURCE_MAP[i].id == id) {
            return CATEGORY_SOURCE_MAP[i].name;
        }
    }
    return "Unknown (" + id + ")";
}

std::string getWalletName(const std::string& id) {
    for (int i = 0; i < WALLET_MAP_SIZE; i++) {
        if (WALLET_MAP[i].id == id) {
            return WALLET_MAP[i].name;
        }
    }
    return "Unknown (" + id + ")";
}

void printRecurringTransactionsTable(DynamicArray<RecurringTransaction>& list) {
    int size = list.getSize();
    if (size <= 0) {
        std::cout << "-> Danh sach giao dich dinh ky trong!\n";
        return;
    }

    std::cout << "\n========================================================================================================================\n";
    std::cout << std::left 
              << std::setw(6)  << "ID"
              << std::setw(10) << "Type"
              << std::setw(22) << "Category/Source"
              << std::setw(20) << "Wallet"
              << std::setw(15) << "Amount (VND)"
              << std::setw(14) << "Start Date"
              << std::setw(14) << "Last Applied"
              << std::setw(25) << "Description"
              << "\n========================================================================================================================\n";

    for (int i = 0; i < size; i++) {
        const RecurringTransaction& tx = list[i];

        std::string typeStr = (tx.getType() == Income) ? "INCOME" : "EXPENSE";
        std::string catName = getCategoryOrSourceName(tx.getSourceOrCatId());
        std::string walletName = getWalletName(tx.getWalletId());

        std::cout << std::left 
                  << std::setw(6)  << tx.getId()
                  << std::setw(10) << typeStr
                  << std::setw(22) << catName
                  << std::setw(20) << walletName
                  << std::setw(15) << std::fixed << std::setprecision(0) << tx.getAmount()
                  << std::setw(14) << tx.getStartDate()
                  << std::setw(14) << (tx.getLastAppliedMonth().empty() ? "N/A" : tx.getLastAppliedMonth())
                  << std::setw(25) << tx.getDescription()
                  << "\n";
    }
    std::cout << "========================================================================================================================\n";
}
