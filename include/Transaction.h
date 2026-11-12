#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <iomanip>

enum TransactionType {Income = 1, Expense = 2};

class Transaction {
    private:
    TransactionType TYPE;
    std::string DATE;
    std::string SOURCE_OR_CATEGORY_ID;
    double AMOUNT;
    std::string WALLET_ID;
    std::string DESCRIPTION;

    public:

    Transaction() : TYPE(Expense) , DATE(" ") , SOURCE_OR_CATEGORY_ID(" ") , AMOUNT(0) , WALLET_ID(" ") , DESCRIPTION(" ") {}
    Transaction(TransactionType type, const std::string& date, const std::string category, const double amount, const std::string& id, const std::string desc) : 
    TYPE(type) , DATE(date) ,SOURCE_OR_CATEGORY_ID(category), AMOUNT(amount), WALLET_ID(id), DESCRIPTION(desc) {}
    
    TransactionType get_TYPE() const {return TYPE;}
    std::string get_DATE() const {return DATE;}
    std::string get_SOURCE_OR_CATEGORY_ID() const {return SOURCE_OR_CATEGORY_ID;}
    double get_AMOUNT() const  { return AMOUNT;}
    std::string get_WALLET() const { return WALLET_ID;}
    std::string get_DESC() const {return DESCRIPTION;}

    void set_TYPE(TransactionType type) {
        TYPE = type;
    }
    void set_DATE(const std::string& date) {
        DATE = date;
    }
    void set_SOURCE_OR_CATEGORY_ID(const std::string& id) {
        SOURCE_OR_CATEGORY_ID = id;
    }
    void set_AMOUNT(double money) {
        AMOUNT = money;
    }
    void set_WALLET(const std::string& id) {
        WALLET_ID = id;
    }
    void set_DESC (const std::string& desc){
        DESCRIPTION = desc;
    }

};

inline void printTrans(const Transaction& a) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << (a.get_TYPE() == Income ? "Income" :"Expense") << " " << a.get_DATE() << " ";
    std::cout << a.get_SOURCE_OR_CATEGORY_ID() << " " << a.get_AMOUNT() << " " << a.get_WALLET() << " " <<a.get_DESC() << "\n";
}

#endif