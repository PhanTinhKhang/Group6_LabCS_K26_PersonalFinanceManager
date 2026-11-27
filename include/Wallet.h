#ifndef WALLET_H
#define WALLET_H
#include "DynamicArray.h"
#include <iostream>
#include <string>
#include <iomanip>

class Wallet {

    private:

    int WALLET_ID;
    std::string NAME;
    double BALANCE;

    public:

    Wallet() : WALLET_ID(0) , NAME("") , BALANCE(0) {}
    Wallet(int id, std::string name, double money) : WALLET_ID(id) ,  NAME(name) , BALANCE(money){}

    int get_ID() const { return WALLET_ID;}
    std::string get_NAME() const { return NAME;}
    double get_BALANCE() const { return BALANCE;}

    void set_ID(const int& id) { WALLET_ID = id; }
    void set_NAME(const std::string& name) { NAME = name; }
    void set_BALANCE(double money) { BALANCE = money; }

    bool CheckID(const int& id) { return WALLET_ID == id;}

    void Deposit(double amount){BALANCE += amount;}

    bool Withdrawal(double amount){
        if(amount <= BALANCE) {
            BALANCE -= amount;
            return true;
        } else return false;
    }
};
//Change printWallet to declaration only, moving src to Wallet.cpp
void printWallet(const Wallet& item);
// Add more wallet function
int findWalletIndexById(const int& id, DynamicArray<Wallet>& wallets);
bool createWallet(DynamicArray<Wallet>& wallets, const int& id, const std::string& name, double initialBalance);
bool editWalletName(DynamicArray<Wallet>& wallets, const int& id, const std::string& newName);
bool deleteWallet(DynamicArray<Wallet>& wallets, const int& id);
void viewWallets(DynamicArray<Wallet>& wallets);
double getTotalBalance(DynamicArray<Wallet>& wallets);
std::string getWalletNameById(const int& id, DynamicArray<Wallet>& wallets);

// Wallet Transfer
enum TransferResult {
    TRANSFER_SUCCEEDED,
    TRANSFER_INVALID_AMOUNT,
    TRANSFER_SAME_WALLET,
    TRANSFER_WALLET_NOT_FOUND,
    TRANSFER_INSUFFICIENT_FUNDS
};

TransferResult transferBetweenWallets(DynamicArray<Wallet>& wallets,
                                      int fromId, int toId, double amount);
                                      
#endif