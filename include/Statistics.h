#ifndef STATISTICS_H
#define STATISTICS_H

#include "DynamicArray.h"
#include "Wallet.h"
#include "ExpenseCategory.h"
#include "IncomeSource.h"
#include "Transaction.h"
#include "InputValidator.h"
#include "Date.h"
#include "RecurringTransaction.h"
#include "Dashboard.h"


void reportTimeBasedSummary(DynamicArray<Transaction>& transactions);
void reportWalletBreakdown(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
);
void reportMultiYearOverview(DynamicArray<Transaction>& transactions);
void reportIncomeBreakdownBySource(
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
);
void reportExpenseBreakdownByCategory(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
);

#endif