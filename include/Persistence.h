#ifndef PERSISTENCE_H
#define PERSISTENCE_H

#include <string>
#include "DynamicArray.h"
#include "Wallet.h"
#include "ExpenseCategory.h"
#include "IncomeSource.h"
#include "Transaction.h"
#include "RecurringTransaction.h"

static const std::string DATA_FILE = "finance_data.bin";

bool saveDataToFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
);

bool loadDataFromFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
);

void seedDefaultData(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);

#endif
