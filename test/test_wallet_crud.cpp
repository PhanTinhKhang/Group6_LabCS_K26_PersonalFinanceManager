#include "../include/Wallet.h"
#include <cassert>  
#include <cmath> 
#include <iostream>

using namespace std;

int main() {
    DynamicArray<Wallet> wallets;

    assert(wallets.getSize() == 0);
    assert(fabs(getTotalBalance(wallets) - 0.0) < 1e-6);
    viewWallets(wallets);

    assert(createWallet(wallets, 1, "Physical Cash", 3450000.0));
    assert(createWallet(wallets, 2, "Techcombank Debit", 18500000.0));
    assert(createWallet(wallets, 3, "MoMo E-Wallet", 1500000.0));
    assert(wallets.getSize() == 3);

    assert(!createWallet(wallets, 1, "Duplicate", 1000.0)); 
    assert(!createWallet(wallets, 0, "No ID", 1000.0));
    assert(!createWallet(wallets, 4, "Negative", -500.0));
    assert(wallets.getSize() == 3);

    assert(fabs(getTotalBalance(wallets) - 23450000.0) < 1e-6);

    assert(editWalletName(wallets, 3, "MoMo Personal"));
    assert(getWalletNameById(3, wallets) == "MoMo Personal");
    assert(!editWalletName(wallets, 999, "Test"));
    assert(!editWalletName(wallets, 3, ""));

    viewWallets(wallets);

    assert(deleteWallet(wallets, 1));
    assert(wallets.getSize() == 2);
    assert(fabs(getTotalBalance(wallets) - 20000000.0) < 1e-6);
    assert(!deleteWallet(wallets, 1));

    cout << "All Wallet CRUD tests passed!\n";
    return 0;
}
