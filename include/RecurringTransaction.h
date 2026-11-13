#ifndef RECURRINGTRANSACTION_H
#define RECURRINGTRANSACTION_H

#include "DynamicArray.h"
#include<bits/stdc++.h>
#include "Transaction.h"

class RecurringTransaction{
private:
    int id;
    TransactionType type;
    std::string sourceOrCatId;
    std::string walletId;
    double amount;
    std::string startDate;
    std::string endDate;
    std::string lastAppliedMonth;
    std::string description;
public:
    RecurringTransaction(): id(0), type(Expense), amount(0.0){}
    RecurringTransaction(int id, TransactionType type, std::string srcCatId,
                        std::string walletId, double amount, std::string start,
                        std::string end, std::string lastApplied, std::string desc)
                :id(id), type(type), sourceOrCatId(srcCatId), walletId(walletId), amount(amount),
                startDate(start), endDate(end), lastAppliedMonth(lastApplied), description(desc){}

    int getId() const { return id; }
    TransactionType getType() const { return type; }
    std::string getSourceOrCatId() const { return sourceOrCatId; }
    std::string getWalletId() const { return walletId; }
    double getAmount() const { return amount; }
    std::string getStartDate() const { return startDate; }
    std::string getEndDate() const { return endDate; }
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

#endif