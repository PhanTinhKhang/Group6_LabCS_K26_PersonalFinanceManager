#include "../include/IncomeRecord.h"
#include "../include/ExpenseRecord.h"
#include <iostream>

static int passed = 0, failed = 0;

static void check(const char* name, bool got, bool expected) {
    if (got == expected) { passed++; std::cout << "[PASS] " << name << "\n"; }
    else { failed++; std::cout << "[FAIL] " << name << "\n"; }
}

int main() {
    DynamicArray<Wallet> wallets;
    DynamicArray<IncomeSource> sources;
    DynamicArray<ExpenseCategory> cats;
    DynamicArray<Transaction> trans;

    createWallet(wallets, 1, "Cash", 500);
    add(sources, IncomeSource(1, "Salary"));    
    add(cats, ExpenseCategory(1, "Food"));      

    Date d(13, 11, 2026);

    
    check("Income valid",           addIncome(wallets, sources, trans, d, 1, 200, 1, "Salary"), true);
    std::cout << "Balance (expected 700): " << wallets[0].get_BALANCE() << "\n";
    check("Income amount = 0",      addIncome(wallets, sources, trans, d, 1, 0, 1, "x"), false);
    check("Income amount < 0",      addIncome(wallets, sources, trans, d, 1, -5, 1, "x"), false);
    check("Income wallet missing",  addIncome(wallets, sources, trans, d, 1, 100, 99, "x"), false);
    check("Income source missing",  addIncome(wallets, sources, trans, d, 99, 100, 1, "x"), false);
    check("Income source = 0",      addIncome(wallets, sources, trans, d, 0, 100, 1, "x"), false);

    
    check("Expense valid",            addExpense(wallets, cats, trans, d, 1, 50, 1, "Lunch"), true);
    std::cout << "Balance (expected 650): " << wallets[0].get_BALANCE() << "\n";
    check("Expense insufficient",     addExpense(wallets, cats, trans, d, 1, 10000, 1, "Gift"), false);
    std::cout << "Balance (still 650): " << wallets[0].get_BALANCE() << "\n";
    check("Expense amount = 0",       addExpense(wallets, cats, trans, d, 1, 0, 1, "x"), false);
    check("Expense amount < 0",       addExpense(wallets, cats, trans, d, 1, -5, 1, "x"), false);
    check("Expense wallet missing",   addExpense(wallets, cats, trans, d, 1, 10, 99, "x"), false);
    check("Expense category missing", addExpense(wallets, cats, trans, d, 99, 10, 1, "x"), false);

    
    std::cout << "\nSaved transactions (expected 2): " << trans.getSize() << "\n";
    for (int i = 0; i < trans.getSize(); i++) printTrans(trans[i]);
    printWallet(wallets[0]);

    std::cout << "\nPassed: " << passed << ", Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}

/*
g++ test/test_income_expense.cpp src/IncomeRecord.cpp src/ExpenseRecord.cpp src/InputValidator.cpp src/Date.cpp src/Wallet.cpp src/IncomeSource.cpp src/ExpenseCategory.cpp src/Transaction.cpp -Iinclude -o test_ie.exe
.\test_ie.exe

Item inserted successfully.
Item inserted successfully.
[PASS] Income valid
Balance (expected 700): 700
[PASS] Income amount = 0
[PASS] Income amount < 0
[PASS] Income wallet missing
[PASS] Income source missing
[PASS] Income source = 0
[PASS] Expense valid
Balance (expected 650): 650
[PASS] Expense insufficient
Balance (still 650): 650
[PASS] Expense amount = 0
[PASS] Expense amount < 0
[PASS] Expense wallet missing
[PASS] Expense category missing
Saved transactions (expected 2): 2
Income 13/11/2026 1 200.00 1 Salary
Expense 13/11/2026 1 50.00 1 Lunch
1 Cash 650.00
Passed: 12, Failed: 0
*/