#include "../include/Wallet.h"
#include <cassert>  
#include <cmath> 
#include <iostream>


using namespace std;

int main() {
    DynamicArray<Wallet> wallets;

    // Test 1: initial state
    assert(wallets.getSize() == 0);
    assert(fabs(getTotalBalance(wallets) - 0.0) < 1e-6);
    viewWallets(wallets);

    // Test 2: create 3 valid wallet
    assert(createWallet(wallets, "W_CASH", "Physical Cash", 3450000.0));
    assert(createWallet(wallets, "W_TCB", "Techcombank Debit", 18500000.0));
    assert(createWallet(wallets, "W_MOMO", "MoMo E-Wallet", 1500000.0));
    assert(wallets.getSize() == 3);

    // Test 3:invalid input -> false
    assert(!createWallet(wallets, "W_CASH", "Duplicate", 1000.0)); 
    assert(!createWallet(wallets, "", "No ID", 1000.0));
    assert(!createWallet(wallets, "W_NEG", "Negative", -500.0));
    assert(wallets.getSize() == 3);

    // Test 4: check total balance
    assert(fabs(getTotalBalance(wallets) - 23450000.0) < 1e-6);

    // Test 5: change wallet name
    assert(editWalletName(wallets, "W_MOMO", "MoMo Personal"));
    assert(getWalletNameById("W_MOMO", wallets) == "MoMo Personal");
    assert(!editWalletName(wallets, "W_UNKNOWN", "Test"));
    assert(!editWalletName(wallets, "W_MOMO", ""));

    // Test 6: view wallets
    viewWallets(wallets);

    // Test 7: delete wallet and recheck balance
    assert(deleteWallet(wallets, "W_CASH"));
    assert(wallets.getSize() == 2);
    assert(fabs(getTotalBalance(wallets) - 20000000.0) < 1e-6);
    // delete nonexist wallet -> false
    assert(!deleteWallet(wallets, "W_CASH"));

    cout << "All Wallet CRUD tests passed!\n";
    return 0;
}