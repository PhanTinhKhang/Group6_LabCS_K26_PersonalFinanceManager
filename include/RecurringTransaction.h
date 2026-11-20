#ifndef RECURRINGTRANSACTION_H
#define RECURRINGTRANSACTION_H

#include "DynamicArray.h"
#include "Date.h"
#include "Wallet.h"
#include "ExpenseCategory.h"
#include "IncomeSource.h"
#include "Transaction.h"
#include<bits/stdc++.h>

class RecurringTransaction{
private:
    int id;
    TransactionType type;
    int sourceOrCatId;
    int walletId;
    double amount;
    Date startDate;
    Date endDate;
    std::string lastAppliedMonth;
    std::string description;
public:
    RecurringTransaction(): id(0), type(Expense), amount(0.0){}
    RecurringTransaction(int id, TransactionType type, int srcCatId,
                        int walletId, double amount, Date start,
                        Date end, std::string lastApplied, std::string desc)
                :id(id), type(type), sourceOrCatId(srcCatId), walletId(walletId), amount(amount),
                startDate(start), endDate(end), lastAppliedMonth(lastApplied), description(desc){}

    int getId() const { return id; }
    TransactionType getType() const { return type; }
    int getSourceOrCatId() const { return sourceOrCatId; }
    int getWalletId() const { return walletId; }
    double getAmount() const { return amount; }
    Date getStartDate() const { return startDate; }
    Date getEndDate() const { return endDate; }
    std::string getLastAppliedMonth() const { return lastAppliedMonth; }
    std::string getDescription() const { return description; }

    void setLastAppliedMonth(const std::string& month) {
        lastAppliedMonth = month;
    }
    void setAmount(double amt) {
        amount = amt;
    }
    void setWalletId(int wId) {
        walletId = wId;
    }
    void setDescription(const std::string& desc) {
        description = desc;
    }
    void setStartDate(const Date& start) {
        startDate = start;
    }
    void setEndDate(const Date& end) {
        endDate = end;
    }
    void setSourceOrCatId(int id) {
        sourceOrCatId = id;
    }
    void setType(TransactionType t) {
        type = t;
    }
};

int findRecurringTransactionIndexById(int id, DynamicArray<RecurringTransaction>& list);

bool createRecurringTransaction(
    DynamicArray<RecurringTransaction>& list,
    int id,
    TransactionType type,
    int srcCatId,
    int walletId,
    double amount,
    const Date& startDate,
    const Date& endDate,
    const std::string& desc,
    DynamicArray<Wallet>& wallets
);

bool createRecurringTransaction(
    DynamicArray<RecurringTransaction>& list,
    int id,
    TransactionType type,
    int srcCatId,
    int walletId,
    double amount,
    const Date& startDate,
    const Date& endDate,
    const std::string& desc,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);

bool deleteRecurringTransaction(DynamicArray<RecurringTransaction>& list, int id);

bool editRecurringAmount(DynamicArray<RecurringTransaction>& list, int id, double newAmount);
bool editRecurringWallet(DynamicArray<RecurringTransaction>& list, int id, int newWalletId, DynamicArray<Wallet>& wallets);
bool editRecurringEndDate(DynamicArray<RecurringTransaction>& list, int id, const Date& newEndDate);
bool editRecurringDescription(DynamicArray<RecurringTransaction>& list, int id, const std::string& newDesc);

bool isRecurringActive(const RecurringTransaction& tx, const Date& currentDate);

void printTransactionTable(
    DynamicArray<Transaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);
void printRecurringTransactionsTable(
    DynamicArray<RecurringTransaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
);
void processRecurringTransactions(
    DynamicArray<RecurringTransaction>& recurringList,
    DynamicArray<Transaction>& transactions,
    DynamicArray<Wallet>& wallets
);

#endif