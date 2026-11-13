#include "../include/IncomeRecord.h"
#include "../include/ExpenseRecord.h"
#include <iostream>

static void check(const char* name, bool got, bool expected) {
    std::cout << (got == expected ? "[PASS] " : "[FAIL] ") << name << "\n";
}

int main() {
    DynamicArray<Wallet> wallets;
    DynamicArray<IncomeSource> sources;
    DynamicArray<ExpenseCategory> cats;
    DynamicArray<Transaction> trans;


    Wallet w;
    w.set_ID("1"); w.set_NAME("Cash"); w.set_BALANCE(500);
    wallets.push(w);
    sources.push(IncomeSource(1, "Salary"));  
    cats.push(ExpenseCategory(1, "Food"));     

    check("Income valid",           addIncome(wallets, sources, trans, "13/11/2026", "1", 200, "1", "Salary"), true);
    std::cout << "Balance (expected 700): " << wallets[0].get_BALANCE() << "\n";
    check("Income amount = 0",      addIncome(wallets, sources, trans, "13/11/2026", "1", 0, "1", "x"), false);
    check("Income amount < 0",      addIncome(wallets, sources, trans, "13/11/2026", "1", -5, "1", "x"), false);
    check("Income date 31/02",      addIncome(wallets, sources, trans, "31/02/2026", "1", 100, "1", "x"), false);
    check("Income date is text",    addIncome(wallets, sources, trans, "ab/cd/efgh", "1", 100, "1", "x"), false);
    check("Income date wrong size", addIncome(wallets, sources, trans, "1/1/2026", "1", 100, "1", "x"), false);
    check("Income wallet missing",  addIncome(wallets, sources, trans, "13/11/2026", "1", 100, "99", "x"), false);
    check("Income source missing",  addIncome(wallets, sources, trans, "13/11/2026", "99", 100, "1", "x"), false);
    check("Income source is text",  addIncome(wallets, sources, trans, "13/11/2026", "abc", 100, "1", "x"), false);
    check("Income source empty",    addIncome(wallets, sources, trans, "13/11/2026", "", 100, "1", "x"), false);
    check("Income source too long", addIncome(wallets, sources, trans, "13/11/2026", "12345678901", 100, "1", "x"), false);

    check("Expense valid",            addExpense(wallets, cats, trans, "13/11/2026", "1", "1", 50, "Lunch"), true);
    std::cout << "Balance (expected 650): " << wallets[0].get_BALANCE() << "\n";
    check("Expense insufficient",     addExpense(wallets, cats, trans, "13/11/2026", "1", "1", 10000, "Gift"), false);
    std::cout << "Balance (still 650): " << wallets[0].get_BALANCE() << "\n";
    check("Expense amount = 0",       addExpense(wallets, cats, trans, "13/11/2026", "1", "1", 0, "x"), false);
    check("Expense amount < 0",       addExpense(wallets, cats, trans, "13/11/2026", "1", "1", -5, "x"), false);
    check("Expense date 31/02",       addExpense(wallets, cats, trans, "31/02/2026", "1", "1", 10, "x"), false);
    check("Expense date is text",     addExpense(wallets, cats, trans, "ab/cd/efgh", "1", "1", 10, "x"), false);
    check("Expense wallet missing",   addExpense(wallets, cats, trans, "13/11/2026", "99", "1", 10, "x"), false);
    check("Expense category missing", addExpense(wallets, cats, trans, "13/11/2026", "1", "99", 10, "x"), false);
    check("Expense category is text", addExpense(wallets, cats, trans, "13/11/2026", "1", "abc", 10, "x"), false);

    std::cout << "\nSaved transactions (expected 2): " << trans.getSize() << "\n";
    for (int i = 0; i < trans.getSize(); i++) printTrans(trans[i]);
    printWallet(wallets[0]);
    return 0;
}

/*
[PASS] Income valid
Balance (expected 700): 700
[PASS] Income amount = 0
[PASS] Income amount < 0
[PASS] Income date 31/02
[PASS] Income date is text
[PASS] Income date wrong size
[PASS] Income wallet missing
[PASS] Income source missing
[PASS] Income source is text
[PASS] Income source empty
[PASS] Income source too long
[PASS] Expense valid
Balance (expected 650): 650
[PASS] Expense insufficient
Balance (still 650): 650
[PASS] Expense amount = 0
[PASS] Expense amount < 0
[PASS] Expense date 31/02
[PASS] Expense date is text
[PASS] Expense wallet missing
[PASS] Expense category missing
[PASS] Expense category is text

Saved transactions (expected 2): 2
Income 13/11/2026 1 200.00 1 Salary
Expense 13/11/2026 1 50.00 1 Lunch
1 Cash 650.00
*/