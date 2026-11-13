#ifndef EXPENSERECORD_H
#define EXPENSERECORD_H

#include "Wallet.h"
#include "Transaction.h"
#include "dynamicArray.h"
#include "ExpenseCategory.h"
#include "Date.h"
#include <string>


void inputExpense(std::string &date, 
    std::string &CateId, double &Amount, 
    std::string &walletId,std::string &desc);

bool addExpense(DynamicArray<Wallet> &wallets, DynamicArray<ExpenseCategory> &expenses,
    DynamicArray<Transaction> &transaction, const std::string &date, const std::string &walletId,
    const std::string &ExpenseId,double Amount, const std::string &desc);
#endif