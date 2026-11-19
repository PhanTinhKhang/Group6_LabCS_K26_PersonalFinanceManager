#ifndef INCOMERECORD_H
#define INCOMERECORD_H
#include "Wallet.h"
#include "Transaction.h"
#include "DynamicArray.h"
#include "Date.h"
#include "IncomeSource.h"
#include <string>

void inputIncome( std::string &date,  int &SourceID, double &Amount,
                 int &walletId, std::string &desc);
bool addIncome(DynamicArray<Wallet>& wallets,DynamicArray<IncomeSource>& sources,
               DynamicArray<Transaction>& transactions, const std::string& date, const std::string& sourceId,
               double Amount, const int& walletId,
               const std::string& desc);
#endif