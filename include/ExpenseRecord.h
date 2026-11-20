#ifndef EXPENSERECORD_H
#define EXPENSERECORD_H

#include "Wallet.h"
#include "Transaction.h"
#include "DynamicArray.h"
#include "ExpenseCategory.h"
#include "Date.h"
#include "InputValidator.h"
#include <string>

void inputExpense(Date &date, int &cateId, double &amount,
                  int &walletId, std::string &desc);

bool addExpense(DynamicArray<Wallet>& wallets, DynamicArray<ExpenseCategory>& categories,
                DynamicArray<Transaction>& transactions, const Date& date, int cateId,
                double amount, int walletId, const std::string& desc);
#endif