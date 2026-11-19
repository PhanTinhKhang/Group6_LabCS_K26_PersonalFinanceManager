#ifndef EXPENSERECORD_H
#define EXPENSERECORD_H

#include "Wallet.h"
#include "Transaction.h"
#include "DynamicArray.h"
#include "ExpenseCategory.h"
#include "Date.h"
#include <string>


void inputExpense(std::string &date, 
    int &CateId, double &Amount, 
    int &walletId,std::string &desc);

bool addExpense(DynamicArray<Wallet> &wallets, DynamicArray<ExpenseCategory> &expenses,
    DynamicArray<Transaction> &transaction, const std::string &date, 
    const int& ExpenseId,double Amount, const int& walletId, const std::string &desc);
#endif