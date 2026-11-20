#include "../include/IncomeRecord.h"
#include "../include/InputValidator.h"
#include <iostream>
#include <string>
void inputIncome(Date &date, int &sourceId, double &amount, int &walletId, std::string &desc) {
    std::cout << "-------------Income Record-------------\n";
    readDate("Date: ", date);
    readInt("SourceID: ", sourceId);
    readDouble("Amount: ", amount);
    readInt("WalletID: ", walletId);
    std::cout << "Description: ";
    std::getline(std::cin, desc);
}

bool addIncome(DynamicArray<Wallet>& wallets, DynamicArray<IncomeSource>& sources,
               DynamicArray<Transaction>& transactions, const Date& date, int sourceId,
               double amount, int walletId, const std::string& desc) {
    if (amount <= 0) return false;
    if (!existIncome(sources, sourceId)) return false;
    int idx = findWalletIndexById(walletId, wallets);
    if (idx == -1) return false;
    wallets[idx].Deposit(amount);
    transactions.push(Transaction(Income, date, sourceId, amount, walletId, desc));
    return true;
}