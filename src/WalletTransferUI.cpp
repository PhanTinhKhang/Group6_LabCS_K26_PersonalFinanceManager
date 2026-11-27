#include "../include/WalletTransferUI.h"
#include "../include/InputValidator.h"
#include "../include/Dashboard.h"
#include "../include/UITheme.h"
#include <iostream>

void handleWalletsTransfer(DynamicArray<Wallet>& wallets) {
    clearScreen();
    printHeader("TRANSFER BETWEEN WALLETS");

    if (wallets.getSize() < 2) {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " You need at least two wallets to transfer money.\n";
        pauseScreen();
        return;
    }

    std::cout << " " << Color::BOLD << Color::WHITE << "Available Wallets:" << Color::RESET << "\n";
    viewWallets(wallets);
    std::cout << "\n";

    int fromId = 0, toId = 0;
    double amount = 0.0;
    readInt("  ▸ Enter source wallet ID: ", fromId);
    readInt("  ▸ Enter destination wallet ID: ", toId);
    readDouble("  ▸ Enter amount (VND): ", amount);

    TransferResult res = transferBetweenWallets(wallets, fromId, toId, amount);

    switch (res) {
        case TRANSFER_SUCCEEDED:  
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Transferred " << formatCurrency(amount)
                      << " from '" << getWalletNameById(fromId, wallets)
                      << "' to '" << getWalletNameById(toId, wallets) << "' successfully!\n";
            break;

        case TRANSFER_INSUFFICIENT_FUNDS:
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Insufficient balance in source wallet.\n";
            break;

        case TRANSFER_INVALID_AMOUNT:
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Transferred amount must be positive.\n";
            break;

        case TRANSFER_SAME_WALLET: 
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Source and Destination wallets must be different.\n";
            break;

        case TRANSFER_WALLET_NOT_FOUND:
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Either source or destination wallet doesn't exist.\n";
            break;

        default:
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Unknown transfer error occurred.\n";
            break;
    }

    pauseScreen();
}
