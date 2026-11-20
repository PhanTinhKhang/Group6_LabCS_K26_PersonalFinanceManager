#include "../include/RecurringTransaction.h"
#include<bits/stdc++.h>

using namespace std;

int findRecurringTransactionIndexById(int id, DynamicArray<RecurringTransaction>& list) {
    int sz = list.getSize();
    for (int i = 0; i < sz; ++i) {
        if (list[i].getId() == id) {
            return i;
        }
    }
    return -1;
}

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
) {
    if (id <= 0) {
        cout << "Error: Recurring Transaction ID must be a positive integer.\n";
        return false;
    }
    if (amount <= 0.0) {
        cout << "Error: Amount must be greater than 0.\n";
        return false;
    }
    if (findRecurringTransactionIndexById(id, list) != -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' already exists.\n";
        return false;
    }
    if (findWalletIndexById(walletId, wallets) == -1) {
        cout << "Error: Wallet ID '" << walletId << "' not found.\n";
        return false;
    }
    if (type == Expense) {
        int dummyIdx = -1;
        if (!search(srcCatId, categories, dummyIdx)) {
            cout << "Error: Expense Category ID '" << srcCatId << "' not found.\n";
            return false;
        }
    } else if (type == Income) {
        int dummyIdx = -1;
        if (!search(srcCatId, sources, dummyIdx)) {
            cout << "Error: Income Source ID '" << srcCatId << "' not found.\n";
            return false;
        }
    }
    Date defaultDate;
    if (!endDate.isEqual(defaultDate) && endDate.isBefore(startDate)) {
        cout << "Error: End date cannot be before start date.\n";
        return false;
    }

    list.push(RecurringTransaction(id, type, srcCatId, walletId, amount, startDate, endDate, "", desc));
    cout << "Successfully created recurring transaction #" << id << ".\n";
    return true;
}

bool deleteRecurringTransaction(DynamicArray<RecurringTransaction>& list, int id) {
    int idx = findRecurringTransactionIndexById(id, list);
    if (idx == -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' not found.\n";
        return false;
    }
    list.pop(idx);
    cout << "Successfully deleted recurring transaction #" << id << ".\n";
    return true;
}

bool editRecurringAmount(DynamicArray<RecurringTransaction>& list, int id, double newAmount) {
    if (newAmount <= 0.0) {
        cout << "Error: New amount must be greater than 0.\n";
        return false;
    }
    int idx = findRecurringTransactionIndexById(id, list);
    if (idx == -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' not found.\n";
        return false;
    }
    list[idx].setAmount(newAmount);
    cout << "Successfully updated amount for recurring transaction #" << id << ".\n";
    return true;
}

bool editRecurringWallet(DynamicArray<RecurringTransaction>& list, int id, int newWalletId, DynamicArray<Wallet>& wallets) {
    int idx = findRecurringTransactionIndexById(id, list);
    if (idx == -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' not found.\n";
        return false;
    }
    if (findWalletIndexById(newWalletId, wallets) == -1) {
        cout << "Error: Wallet ID '" << newWalletId << "' not found.\n";
        return false;
    }
    list[idx].setWalletId(newWalletId);
    cout << "Successfully updated wallet for recurring transaction #" << id << ".\n";
    return true;
}

bool editRecurringEndDate(DynamicArray<RecurringTransaction>& list, int id, const Date& newEndDate) {
    int idx = findRecurringTransactionIndexById(id, list);
    if (idx == -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' not found.\n";
        return false;
    }
    Date defaultDate;
    if (!newEndDate.isEqual(defaultDate) && newEndDate.isBefore(list[idx].getStartDate())) {
        cout << "Error: End date cannot be before start date.\n";
        return false;
    }
    list[idx].setEndDate(newEndDate);
    cout << "Successfully updated end date for recurring transaction #" << id << ".\n";
    return true;
}

bool editRecurringDescription(DynamicArray<RecurringTransaction>& list, int id, const std::string& newDesc) {
    int idx = findRecurringTransactionIndexById(id, list);
    if (idx == -1) {
        cout << "Error: Recurring Transaction ID '" << id << "' not found.\n";
        return false;
    }
    list[idx].setDescription(newDesc);
    cout << "Successfully updated description for recurring transaction #" << id << ".\n";
    return true;
}

bool isRecurringActive(const RecurringTransaction& tx, const Date& currentDate) {
    Date start = tx.getStartDate();
    Date end = tx.getEndDate();
    Date defaultDate;

    if (currentDate.isBefore(start)) {
        return false;
    }
    if (!end.isEqual(defaultDate) && !end.isBefore(start)) {
        if (end.isBefore(currentDate)) {
            return false;
        }
    }
    return true;
}

