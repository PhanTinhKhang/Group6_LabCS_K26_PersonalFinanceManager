#include "../include/InputValidator.h"
#include <iostream>

static int passed = 0, failed = 0;

static void check(const char* name, bool got, bool expected) {
    if (got == expected) { passed++; std::cout << "[PASS] " << name << "\n"; }
    else { failed++; std::cout << "[FAIL] " << name << "\n"; }
}

static bool dateIs(const char* s, int d, int m, int y) {
    Date dt;
    return parseDate(s, dt) && dt.getDay() == d && dt.getMonth() == m && dt.getYear() == y;
}

int main() {
    // ---------- parseInt ----------
    int id = 5;
    check("int 12",          parseInt("12", id) && id == 12, true);
    check("int trim",        parseInt("  7  ", id) && id == 7, true);
    check("int 0",           parseInt("0", id), false);
    check("int am",          parseInt("-3", id), false);
    check("int letter",         parseInt("12a", id), false);
    check("int void",        parseInt("", id), false);
    check("int overflow",      parseInt("1234567890", id), false);
    id = 99; parseInt("abc", id);

    // ---------- parseDouble ----------
    double a = 0;
    check("double 1500",        parseDouble("1500", a) && a == 1500, true);
    check("double 1500.5",      parseDouble("1500.5", a) && a == 1500.5, true);
    check("double phay",        parseDouble("1500,25", a) && a == 1500.25, true);
    check("double .5",          parseDouble(".5", a) && a == 0.5, true);
    check("double 12.",         parseDouble("12.", a) && a == 12, true);
    check("rounded double",    parseDouble("1.2345", a) && a == 1.235, true);
    check("double 0",           parseDouble("0", a), false);
    check("double 0.0004",      parseDouble("0.0004", a), false);
    check("negative double",          parseDouble("-5", a), false);
    check("double letter",         parseDouble("12abc", a), false);
    check("wrong format 1.2.3",       parseDouble("1.2.3", a), false);
    check("void",        parseDouble("   ", a), false);

    // ---------- parseDate:Valid ----------
    check("date /",          dateIs("13/08/2026", 13, 8, 2026), true);
    check("date -",          dateIs("13-08-2026", 13, 8, 2026), true);
    check("date space",      dateIs("13 08 2026", 13, 8, 2026), true);
    check("date letter format",  dateIs("13-sep-2026", 13, 9, 2026), true);
    check("date Sep",        dateIs("13 Sep 2026", 13, 9, 2026), true);
    check("date SEP",        dateIs("13/SEP/2026", 13, 9, 2026), true);
    check("date trim",       dateIs("  13 / 08 / 2026  ", 13, 8, 2026), true);
    check("date 1/1/2026",   dateIs("1/1/2026", 1, 1, 2026), true);
    check("date leap year",      dateIs("29/02/2024", 29, 2, 2024), true);

    // ---------- parseDate:Invalid ----------
    Date d;
    check("wrong format",  parseDate("14/12-2026", d), false);
    check("wrong format",     parseDate("13 08/2026", d), false);
    check("wrong format",    parseDate("13 / 08 - 2026", d), false);
    check("date 4 phan",     parseDate("1 3/08/2026", d), false);
    check("date //",         parseDate("13//08/2026", d), false);
    check("date cuoi /",     parseDate("13/08/2026/", d), false);
    check("date dau /",      parseDate("/13/08/2026", d), false);
    check("date thieu",      parseDate("13/08", d), false);
    check("date khong dau",  parseDate("13sep2026", d), false);
    check("date 31/02",      parseDate("31/02/2026", d), false);
    check("date 29/02/2023", parseDate("29/02/2023", d), false);
    check("date thang 13",   parseDate("13/13/2026", d), false);
    check("date nam 26",     parseDate("13/08/26", d), false);
    check("date nam 1800",   parseDate("13/08/1800", d), false);
    check("date thang sai",  parseDate("13-sept-2026", d), false);
    check("date ky tu la",   parseDate("13@08@2026", d), false);
    check("date chu",        parseDate("abc", d), false);
    check("date rong",       parseDate("", d), false);
    d.setDate(1, 1, 2030);
    parseDate("31/02/2026", d);
    check("date sai khong doi out", d.getYear() == 2030, true);

    // ---------- existWallet ----------
    DynamicArray<Wallet> wallets;
    createWallet(wallets, 1, "Cash", 500);
    createWallet(wallets, 2, "Bank", 1000);
    check("wallet 1 exists",   existWallet(wallets, 1), true);
    check("wallet 2 exists",   existWallet(wallets, 2), true);
    check("wallet 99 doesn't exist", existWallet(wallets, 99), false);

    // ---------- existIncome ----------
    DynamicArray<IncomeSource> sources;
    add(sources, IncomeSource(3, "Bonus"));   
    add(sources, IncomeSource(1, "Salary"));
    add(sources, IncomeSource(2, "Gift"));
    check("income 1 exists",   existIncome(sources, 1), true);
    check("income 2 exists",   existIncome(sources, 2), true);
    check("income 3 exists",   existIncome(sources, 3), true);
    check("income 99 doesn't exist", existIncome(sources, 99), false);
    check("income 0 doesn't exist",  existIncome(sources, 0), false);

    // ---------- existExpense ----------
    DynamicArray<ExpenseCategory> cats;
    add(cats, ExpenseCategory(3, "Rent"));
    add(cats, ExpenseCategory(1, "Food"));
    add(cats, ExpenseCategory(2, "Travel"));
    check("expense 1 exists",   existExpense(cats, 1), true);
    check("expense 2 exists",   existExpense(cats, 2), true);
    check("expense 3 exists",   existExpense(cats, 3), true);
    check("expense 99 doesn't exist", existExpense(cats, 99), false);
    check("expense 0 doesn't exist",  existExpense(cats, 0), false);

    std::cout << "Passed: " << passed << ", Failed: " << failed << "\n";
    return failed == 0 ? 0 : 1;
}
/*
g++ test/test_validator.cpp src/InputValidator.cpp src/Date.cpp src/Wallet.cpp src/IncomeSource.cpp src/ExpenseCategory.cpp -Iinclude -o test_validator.exe
.\test_validator.exe


[PASS] int 12                                                                                 
[PASS] int trim
[PASS] int 0
[PASS] int am
[PASS] int letter
[PASS] int void
[PASS] int overflow
[PASS] double 1500
[PASS] double 1500.5
[PASS] double phay
[PASS] double .5
[PASS] double 12.
[PASS] rounded double
[PASS] double 0
[PASS] double 0.0004
[PASS] negative double
[PASS] double letter
[PASS] wrong format 1.2.3
[PASS] void
[PASS] date /
[PASS] date -
[PASS] date space
[PASS] date letter format
[PASS] date Sep
[PASS] date SEP
[PASS] date trim
[PASS] date 1/1/2026
[PASS] date leap year
[PASS] wrong format
[PASS] wrong format
[PASS] wrong format
[PASS] date 4 phan
[PASS] date //
[PASS] date cuoi /
[PASS] date dau /
[PASS] date thieu
[PASS] date khong dau
[PASS] date 31/02
[PASS] date 29/02/2023
[PASS] date thang 13
[PASS] date nam 26
[PASS] date nam 1800
[PASS] date thang sai
[PASS] date ky tu la
[PASS] date chu
[PASS] date rong
[PASS] date sai khong doi out
[PASS] wallet 1 exists
[PASS] wallet 2 exists
[PASS] wallet 99 doesn't exist
Item inserted successfully.
Item inserted successfully.
Item inserted successfully.
[PASS] income 1 exists
[PASS] income 2 exists
[PASS] income 3 exists
[PASS] income 99 doesn't exist
[PASS] income 0 doesn't exist
Item inserted successfully.
Item inserted successfully.
Item inserted successfully.
[PASS] expense 1 exists
[PASS] expense 2 exists
[PASS] expense 3 exists
[PASS] expense 99 doesn't exist
[PASS] expense 0 doesn't exist
Passed: 60, Failed: 0
*/