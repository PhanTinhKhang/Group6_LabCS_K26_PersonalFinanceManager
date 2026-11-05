#ifndef WALLET_H
#define WALLET_H

#include <iostream>
#include <string>
#include <iomanip>

class Wallet {
    //
    std::string WALLET_ID;
    std::string NAME;
    double BALANCE;
    //
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

void printWallet(const Wallet& item) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << item.get_ID() << " " << item.get_NAME() << " " << std::fixed << item.get_BALANCE() << "\n";
}

#endif