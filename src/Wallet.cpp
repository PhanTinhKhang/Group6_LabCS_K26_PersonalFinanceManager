#include "../include/Wallet.h"
#include "../include/Dashboard.h"
#include "../include/UITheme.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printWallet(const Wallet& item) {
    cout << fixed << setprecision(2);
    cout << item.get_ID() << " " << item.get_NAME() << " " << item.get_BALANCE() << "\n";
}

int findWalletIndexById(const int& id, DynamicArray<Wallet>& wallets) {
    int sz = wallets.getSize();
    for (int i = 0; i < sz; ++i) {
        if (wallets[i].CheckID(id)) {
            return i; 
        }
    }
    return -1;
}

bool createWallet(DynamicArray<Wallet>& wallets, const int& id, const string& name, double initialBalance) {
    if (id <= 0) {
        cout << "Error: Wallet ID must be a positive integer.\n";
        return false;
    }
    if (name.empty()) {
        cout << "Error: Wallet Name cannot be empty.\n";
        return false;
    }

    if (initialBalance < 0.0) {
        cout << "Error: Initial balance cannot be negative.\n";
        return false;
    }

    if (findWalletIndexById(id, wallets) != -1) {
        cout << "Error: Wallet ID '" << id << "' already exists.\n";
        return false;
    }

    wallets.push(Wallet(id, name, initialBalance));
    return true;
}

bool editWalletName(DynamicArray<Wallet>& wallets, const int& id, const string& newName) {
    if (newName.empty()) {
        cout << "Error: New wallet name cannot be empty.\n";
        return false;
    }

    int idx = findWalletIndexById(id, wallets);
    if (idx == -1) {
        cout << "Error: Wallet ID '" << id << "' not found.\n";
        return false;
    }

    wallets[idx].set_NAME(newName);
    return true;
}

bool deleteWallet(DynamicArray<Wallet>& wallets, const int& id) {
    int idx = findWalletIndexById(id, wallets);
    if (idx == -1) {
        cout << "Error: Wallet ID '" << id << "' not found.\n";
        return false;
    }

    wallets.pop(idx);
    return true;
}

void viewWallets(DynamicArray<Wallet>& wallets) {
    int sz = wallets.getSize();
    if (sz == 0) {
        cout << Color::CYAN << "+------+-------------+-------------------------+------------------------+\n";
        cout << "| No.  | Wallet ID   | Wallet Name             | Current Balance        |\n";
        cout << "+------+-------------+-------------------------+------------------------+\n";
        cout << "|  No active wallets found.                                             |\n";
        cout << "+------+-------------+-------------------------+------------------------+\n" << Color::RESET;
        return;
    }

    cout << Color::CYAN << "+------+-------------+-------------------------+------------------------+\n";
    cout << "| No.  | Wallet ID   | Wallet Name             | Current Balance        |\n";
    cout << "+------+-------------+-------------------------+------------------------+\n" << Color::RESET;

    for (int i = 0; i < sz; ++i) {
        string numStr = (i + 1 < 10 ? "0" : "") + to_string(i + 1);
        cout << Color::CYAN << "|  " << Color::RESET << setw(2) << numStr << Color::CYAN << "  | "
             << Color::YELLOW << left << setw(11) << wallets[i].get_ID() << Color::RESET << Color::CYAN << " | "
             << Color::WHITE << left << setw(23) << wallets[i].get_NAME() << Color::RESET << Color::CYAN << " | "
             << Color::BOLD << Color::GREEN << right << setw(22) << formatCurrency(wallets[i].get_BALANCE()) << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }

    cout << Color::CYAN << "+------+-------------+-------------------------+------------------------+\n";
    cout << "|  " << Color::BOLD << Color::WHITE << "TOTAL AGGREGATE BALANCE:" << Color::RESET << Color::CYAN << "                    | "
         << Color::BOLD << Color::GREEN << right << setw(22) << formatCurrency(getTotalBalance(wallets)) << Color::RESET << Color::CYAN << " |\n";
    cout << "+----------------------------------------------+------------------------+\n" << Color::RESET;
}

double getTotalBalance(DynamicArray<Wallet>& wallets) {
    double total = 0.0;
    int sz = wallets.getSize();
    for (int i = 0; i < sz; ++i) {
        total += wallets[i].get_BALANCE();
    }
    return total;
}

string getWalletNameById(const int& id, DynamicArray<Wallet>& wallets) {
    int idx = findWalletIndexById(id, wallets);
    if (idx != -1) {
        return wallets[idx].get_NAME();
    }
    return "Unknown Wallet";
}

TransferResult transferBetweenWallets(DynamicArray<Wallet>& wallets,
                                      int fromId, int toId, double amount) {
    if(amount <= 0) return TRANSFER_INVALID_AMOUNT;
    if(fromId == toId) return TRANSFER_SAME_WALLET;
    int from = findWalletIndexById(fromId, wallets);
    int to = findWalletIndexById(toId, wallets);
    if(from == -1 || to == -1) return TRANSFER_WALLET_NOT_FOUND;
    if(!wallets[from].Withdrawal(amount)) return TRANSFER_INSUFFICIENT_FUNDS;
    wallets[to].Deposit(amount);
    return TRANSFER_SUCCEEDED;
}

