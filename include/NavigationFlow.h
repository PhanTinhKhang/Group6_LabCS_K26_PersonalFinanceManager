#ifndef NAVIGATIONFLOW_H
#define NAVIGATIONFLOW_H

#include "DynamicArray.h"
#include "Wallet.h"
#include "ExpenseCategory.h"
#include "IncomeSource.h"
#include "Transaction.h"
#include "RecurringTransaction.h"
#include "Dashboard.h"

void initializeApp(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
);

void handleRecordIncome(
    DynamicArray<Wallet>& wallets,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
);

void handleRecordExpense(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
);

void handleWalletManagement(DynamicArray<Wallet>& wallets);

void handleMasterDataManagement(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);

void handleRecurringTransactions(
    DynamicArray<RecurringTransaction>& recurringList,
    DynamicArray<Transaction>& transactions,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);

void handleStatistics(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
);

void handlePersistence(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
);

void shutdownApp(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
);

void handleInvalidChoice();

#endif
