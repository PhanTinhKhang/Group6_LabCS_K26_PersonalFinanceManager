#ifndef INCOMERECORD_H
#define INCOMERECORD_H
#include "Wallet.h"
#include "Transaction.h"
#include "dynamicArray.h"
#include "Date.h"
#include "IncomeSource.h"
#include <string>

void inputIncome( std::string &date,  std::string &SourceID, double &Amount,
                 std::string &walletId, std::string &desc);
bool addIncome(DynamicArray<Wallet>& wallets,DynamicArray<IncomeSource>& sources,
               DynamicArray<Transaction>& transactions, const std::string& date, const std::string& sourceId,
               double Amount, const std::string& walletId,
               const std::string& desc);
#endif