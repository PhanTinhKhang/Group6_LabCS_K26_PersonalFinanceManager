#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <iostream>
#include <string>
#include <iomanip>
#include "Date.h"

enum TransactionType {Income = 1, Expense = 2};

class Transaction {
    private:
    TransactionType TYPE;
    Date DATE;
    int SOURCE_OR_CATEGORY_ID;
    double AMOUNT;
    int WALLET_ID;
    std::string DESCRIPTION;

    public:

    Transaction() : TYPE(Expense) , DATE() , SOURCE_OR_CATEGORY_ID(0) , AMOUNT(0) , WALLET_ID(0) , DESCRIPTION(" ") {}
    Transaction(TransactionType type, const Date& date, const int category, const double amount, const int& id, const std::string desc) : 
    TYPE(type) , DATE(date) ,SOURCE_OR_CATEGORY_ID(category), AMOUNT(amount), WALLET_ID(id), DESCRIPTION(desc) {}
    
    TransactionType get_TYPE() const {return TYPE;}
    Date get_DATE() const {return DATE;}
    int get_SOURCE_OR_CATEGORY_ID() const {return SOURCE_OR_CATEGORY_ID;}
    double get_AMOUNT() const  { return AMOUNT;}
    int get_WALLET() const { return WALLET_ID;}
    std::string get_DESC() const {return DESCRIPTION;}

    void set_TYPE(TransactionType type) {
        TYPE = type;
    }
    void set_DATE(const Date& date) {
        DATE = date;
    }
    void set_SOURCE_OR_CATEGORY_ID(const int& id) {
        SOURCE_OR_CATEGORY_ID = id;
    }
    void set_AMOUNT(double money) {
        AMOUNT = money;
    }
    void set_WALLET(const int& id) {
        WALLET_ID = id;
    }
    void set_DESC (const std::string& desc){
        DESCRIPTION = desc;
    }

};

void printTrans(const Transaction& a);

#endif