#ifndef INCOMERECORD_H
#define INCOMERECORD_H
#include "Wallet.h"
#include "Transaction.h"
#include "DynamicArray.h"
#include "Date.h"
#include "IncomeSource.h"
#include "InputValidator.h"
#include <string>

void inputIncome(Date &date, int &sourceId, double &amount,
                 int &walletId, std::string &desc);

bool addIncome(DynamicArray<Wallet>& wallets, DynamicArray<IncomeSource>& sources,
               DynamicArray<Transaction>& transactions, const Date& date, int sourceId,
               double amount, int walletId, const std::string& desc);
#endif