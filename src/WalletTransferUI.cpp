#include "../include/WalletTransferUI.h"
#include "../include/InputValidator.h"
#include "../include/Dashboard.h"
#include <iostream>
void handleWalletsTransfer(DynamicArray<Wallet>& wallets) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "               PERSONAL FINANCE MANAGER > TRANSFER BETWEEN WALLETS                      \n";
    std::cout << "========================================================================================\n";

    if (wallets.getSize() < 2) {
        std::cout << "\n [ERROR] You need at least two wallets to transfer money.\n";
        pauseScreen();
        return;
    }

    std::cout << "Available Wallets:\n";
    viewWallets(wallets);
    std::cout << "\n";

    int fromId = 0, toId = 0;
    double amount = 0.0;
    readInt(" Enter source wallet ID: ", fromId);
    readInt(" Enter destination wallet ID: ", toId);
    readDouble(" Enter amount (VND): ", amount);

    TransferResult res = transferBetweenWallets(wallets, fromId, toId, amount);

    switch (res) {
        case TRANSFER_SUCCEEDED:  
            std::cout << "\n [SUCCESS] Transferred " << formatCurrency(amount)
                      << " from '" << getWalletNameById(fromId, wallets)
                      << "' to '" << getWalletNameById(toId, wallets) << "' successfully!\n";
            break;

        case TRANSFER_INSUFFICIENT_FUNDS:
            std::cout << "\n [ERROR] Insufficient balance in source wallet.\n";
            break;

        case TRANSFER_INVALID_AMOUNT:
            std::cout << "\n [ERROR] Transferred amount must be positive.\n";
            break;

        case TRANSFER_SAME_WALLET: 
            std::cout << "\n [ERROR] Source and Destination wallets must be different.\n";
            break;

        case TRANSFER_WALLET_NOT_FOUND:
            std::cout << "\n [ERROR] Either source or destination wallet doesn't exist.\n";
            break;

        default:
            std::cout << "\n [ERROR] Unknown transfer error occurred.\n";
            break;
    }

    pauseScreen();
}
