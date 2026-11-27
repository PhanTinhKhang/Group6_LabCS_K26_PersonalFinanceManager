#include "../include/Wallet.h"
#include <cassert>  
#include <cmath> 
#include <iostream>

using namespace std;

static void testTransfer() {
    DynamicArray<Wallet> w;
    assert(createWallet(w, 1, "Cash", 500.0));
    assert(createWallet(w, 2, "Bank", 1000.0));

    // SUCCEEDED
    assert(transferBetweenWallets(w, 1, 2, 200.0) == TRANSFER_SUCCEEDED);
    assert(fabs(w[0].get_BALANCE() - 300.0) < 1e-6);
    assert(fabs(w[1].get_BALANCE() - 1200.0) < 1e-6);
    assert(fabs(getTotalBalance(w) - 1500.0) < 1e-6);

    assert(transferBetweenWallets(w, 1, 2, 300.0) == TRANSFER_SUCCEEDED);
    assert(fabs(w[0].get_BALANCE() - 0.0) < 1e-6);
    assert(fabs(w[1].get_BALANCE() - 1500.0) < 1e-6);

    // INVALID
    assert(transferBetweenWallets(w, 1, 2, 1.0) == TRANSFER_INSUFFICIENT_FUNDS);
    assert(transferBetweenWallets(w, 2, 1, 0.0) == TRANSFER_INVALID_AMOUNT);
    assert(transferBetweenWallets(w, 2, 1, -5.0) == TRANSFER_INVALID_AMOUNT);
    assert(transferBetweenWallets(w, 2, 2, 10.0) == TRANSFER_SAME_WALLET);
    assert(transferBetweenWallets(w, 99, 2, 10.0) == TRANSFER_WALLET_NOT_FOUND);
    assert(transferBetweenWallets(w, 2, 99, 10.0) == TRANSFER_WALLET_NOT_FOUND);

    // UNCHANGED BALANCE AFTER INVALID TRANS
    assert(fabs(w[0].get_BALANCE() - 0.0) < 1e-6);
    assert(fabs(w[1].get_BALANCE() - 1500.0) < 1e-6);
    assert(fabs(getTotalBalance(w) - 1500.0) < 1e-6);

}

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

    testTransfer();

    cout << "All Wallet CRUD tests passed!\n";
    return 0;
}
