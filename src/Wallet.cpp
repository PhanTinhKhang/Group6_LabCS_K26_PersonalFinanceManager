#include "../include/Wallet.h"
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

void printWallet(const Wallet& item) {
    cout << fixed << setprecision(2);
    cout << item.get_ID() << " " << item.get_NAME() << " " << item.get_BALANCE() << "\n";
}

int findWalletIndexById(const string& id, DynamicArray<Wallet>& wallets) {
    int sz = wallets.getSize();
    for (int i = 0; i < sz; ++i) {
        if (wallets[i].CheckID(id)) {
            return i; 
        }
    }
    return -1;
}

bool createWallet(DynamicArray<Wallet>& wallets, const string& id, const string& name, double initialBalance) {
    if (id.empty() || name.empty()) {
        cout << "Error: Wallet ID and Name cannot be empty.\n";
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

bool editWalletName(DynamicArray<Wallet>& wallets, const string& id, const string& newName) {
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

bool deleteWallet(DynamicArray<Wallet>& wallets, const string& id) {
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
        cout << "No wallets found.\n";
        return;
    }

    cout << "\n+------+---------------+-----------------------+----------------------+\n";
    cout << "| " << left << setw(4) << "No."
         << " | " << setw(13) << "Wallet ID"
         << " | " << setw(21) << "Wallet Name"
         << " | " << right << setw(20) << "Balance (VND)" << " |\n";
    cout << "+------+---------------+-----------------------+----------------------+\n";

    cout << fixed << setprecision(2);
    for (int i = 0; i < sz; ++i) {
        cout << "| " << left << setw(4) << (i + 1)
             << " | " << setw(13) << wallets[i].get_ID()
             << " | " << setw(21) << wallets[i].get_NAME()
             << " | " << right << setw(20) << wallets[i].get_BALANCE() << " |\n";
    }

    cout << "+------+---------------+-----------------------+----------------------+\n";
    cout << "Total Balance: " << fixed << setprecision(2)
         << getTotalBalance(wallets) << " VND\n";
}

double getTotalBalance(DynamicArray<Wallet>& wallets) {
    double total = 0.0;
    int sz = wallets.getSize();
    for (int i = 0; i < sz; ++i) {
        total += wallets[i].get_BALANCE();
    }
    return total;
}

string getWalletNameById(const string& id, DynamicArray<Wallet>& wallets) {
    int idx = findWalletIndexById(id, wallets);
    if (idx != -1) {
        return wallets[idx].get_NAME();
    }
    return "Unknown Wallet";
}