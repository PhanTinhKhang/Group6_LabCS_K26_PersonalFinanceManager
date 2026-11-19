#include "../include/RecurringTransaction.h"
#include "../include/Transaction.h"
#include "../include/Wallet.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include<bits/stdc++.h>

using namespace std;

int main() {
    DynamicArray<Wallet> wallets;
    wallets.push(Wallet(1, "Techcombank Main", 50000000.0));
    wallets.push(Wallet(2, "Cash Wallet", 2000000.0));
    wallets.push(Wallet(3, "Momo E-Wallet", 1500000.0));

    DynamicArray<ExpenseCategory> categories;
    categories.push(ExpenseCategory(201, "Internet & Utilities"));
    categories.push(ExpenseCategory(202, "Housing / Rent"));
    categories.push(ExpenseCategory(203, "Food & Dining"));

    DynamicArray<IncomeSource> sources;
    sources.push(IncomeSource(101, "Salary / Main Job"));
    sources.push(IncomeSource(102, "Freelance Project"));

    cout << "========================================================================================\n";
    cout << "                    BO TEST CHUC NANG IN BANG GIAO DICH & DINH KY                       \n";
    cout << "========================================================================================\n";
    cout << "\n>>> [TEST 1.1] In danh sach giao dich khi DONG (Empty List):\n";
    DynamicArray<Transaction> emptyTransactions;
    printTransactionTable(emptyTransactions, wallets, categories, sources);

    cout << "\n>>> [TEST 1.2] In danh sach giao dich hop le (Income & Expense):\n";
    DynamicArray<Transaction> normalTransactions;
    normalTransactions.push(Transaction(Income, Date(1, 10, 2026), 101, 15000000.0, 1, "Nhan luong thang 10"));
    normalTransactions.push(Transaction(Expense, Date(2, 10, 2026), 202, 3500000.0, 1, "Tien thue nha thang 10"));
    normalTransactions.push(Transaction(Expense, Date(5, 10, 2026), 203, 120000.0, 2, "An trua dong nghiep"));
    normalTransactions.push(Transaction(Expense, Date(10, 10, 2026), 201, 250000.0, 3, "Thanh toan tien mang"));
    normalTransactions.push(Transaction(Income, Date(15, 10, 2026), 102, 2000000.0, 3, "Thuong du an freelance"));
    printTransactionTable(normalTransactions, wallets, categories, sources);

    cout << "\n>>> [TEST 1.3] In giao dich co ID Vi hoac Danh muc KHONG TON TAI (Unknown / Not Found):\n";
    DynamicArray<Transaction> unknownTransactions;
    unknownTransactions.push(Transaction(Expense, Date(20, 10, 2026), 999, 500000.0, 999, "Giao dich vi/danh muc la"));
    unknownTransactions.push(Transaction(Income, Date(21, 10, 2026), 888, 1000000.0, 1, "Nguon thu la"));
    printTransactionTable(unknownTransactions, wallets, categories, sources);




    cout << "\n>>> [TEST 2.1] In danh sach giao dich dinh ky khi DONG (Empty List):\n";
    DynamicArray<RecurringTransaction> emptyRecurring;
    printRecurringTransactionsTable(emptyRecurring, wallets, categories, sources);

    cout << "\n>>> [TEST 2.2] In danh sach giao dich dinh ky hop le:\n";
    DynamicArray<RecurringTransaction> recurringList;
    recurringList.push(RecurringTransaction(101, Expense, 202, 1, 3500000.0, Date(1, 10, 2026), Date(), "10/2026", "Tien thue nha"));
    recurringList.push(RecurringTransaction(102, Income, 101, 1, 15000000.0, Date(5, 10, 2026), Date(), "10/2026", "Luong thang 10"));
    recurringList.push(RecurringTransaction(103, Expense, 201, 3, 250000.0, Date(10, 10, 2026), Date(), "", "Goi cuoc internet"));
    recurringList.push(RecurringTransaction(104, Expense, 203, 2, 500000.0, Date(15, 10, 2026), Date(15, 10, 2027), "09/2026", "Tien an tap the"));
    printRecurringTransactionsTable(recurringList, wallets, categories, sources);

    cout << "\n>>> [TEST 2.3] In giao dich dinh ky co ID Vi hoac Danh muc KHONG TON TAI:\n";
    DynamicArray<RecurringTransaction> unknownRecurring;
    unknownRecurring.push(RecurringTransaction(105, Expense, 999, 999, 700000.0, Date(1, 11, 2026), Date(), "", "Chi phi chua xac dinh"));
    unknownRecurring.push(RecurringTransaction(106, Income, 888, 2, 1200000.0, Date(5, 11, 2026), Date(), "10/2026", "Nguon thu chua xac dinh"));
    printRecurringTransactionsTable(unknownRecurring, wallets, categories, sources);

    cout << "\n========================================================================================\n";
    cout << "                             KET THUC BO TEST IN AN                                     \n";
    cout << "========================================================================================\n";

    return 0;
}
