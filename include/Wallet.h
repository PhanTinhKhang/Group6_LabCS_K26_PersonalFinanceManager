#ifndef WALLET_H
#define WALLET_H
#include "DynamicArray.h"
#include <iostream>
#include <string>
#include <iomanip>

class Wallet {

    private:

    std::string WALLET_ID;
    std::string NAME;
    double BALANCE;

    public:

    Wallet() : WALLET_ID("") , NAME("") , BALANCE(0) {}
    Wallet(std::string id, std::string name, double money) : WALLET_ID(id) ,  NAME(name) , BALANCE(money){}

    std::string get_ID() const { return WALLET_ID;}
    std::string get_NAME() const { return NAME;}
    double get_BALANCE() const { return BALANCE;}

    void set_ID(const std::string& id) { WALLET_ID = id; }
    void set_NAME(const std::string& name) { NAME = name; }
    void set_BALANCE(double money) { BALANCE = money; }

    bool CheckID(const std::string& id) { return WALLET_ID == id;}

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
int findWalletIndexById(const std::string& id, DynamicArray<Wallet>& wallets);
bool createWallet(DynamicArray<Wallet>& wallets, const std::string& id, const std::string& name, double initialBalance);
bool editWalletName(DynamicArray<Wallet>& wallets, const std::string& id, const std::string& newName);
bool deleteWallet(DynamicArray<Wallet>& wallets, const std::string& id);
void viewWallets(DynamicArray<Wallet>& wallets);
double getTotalBalance(DynamicArray<Wallet>& wallets);
std::string getWalletNameById(const std::string& id, DynamicArray<Wallet>& wallets);

#endif