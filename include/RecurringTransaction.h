#ifndef RECURRINGTRANSACTION_H
#define RECURRINGTRANSACTION_H

#include "DynamicArray.h"
#include "Date.h"
#include "Wallet.h"
#include "Transaction.h"
#include <bits/stdc++.h>


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
};
void printRecurringTransactionsTable(DynamicArray<RecurringTransaction>& list);
void processRecurringTransactions(
    DynamicArray<RecurringTransaction>& recurringList,
    DynamicArray<Transaction>& transactions,
    DynamicArray<Wallet>& wallets
);

#endif