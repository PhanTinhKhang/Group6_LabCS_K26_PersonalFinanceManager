#include "../include/RecurringTransaction.h"
#include "../include/dynamicArray.h"
#include <bits/stdc++.h>

using namespace std;

int main() {
    DynamicArray<RecurringTransaction> recurringList;

    recurringList.push(RecurringTransaction(101, Expense, "C02", "W01", 3500000.0, "01/10/2026", "", "10/2026", "Tien thue nha"));
    recurringList.push(RecurringTransaction(102, Income, "S01", "W01", 15000000.0, "05/10/2026", "", "10/2026", "Luong thang 10"));
    recurringList.push(RecurringTransaction(103, Expense, "C01", "W03", 250000.0, "10/10/2026", "", "", "Goi cuoc internet"));

    printRecurringTransactionsTable(recurringList);
    return 0;
}
/*
========================================================================================================================
ID    Type      Category/Source       Wallet              Amount (VND)   Start Date    Last Applied  Description              
========================================================================================================================
101   EXPENSE   Housing / Rent        Techcombank Main    3500000        01/10/2026    10/2026       Tien thue nha            
102   INCOME    Salary / Main Job     Techcombank Main    15000000       05/10/2026    10/2026       Luong thang 10           
103   EXPENSE   Internet & Utilities  Momo E-Wallet       250000         10/10/2026    N/A           Goi cuoc internet        
========================================================================================================================
*/
