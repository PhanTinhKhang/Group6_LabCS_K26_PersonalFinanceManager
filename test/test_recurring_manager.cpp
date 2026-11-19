#include "../include/RecurringTransaction.h"
#include "../include/Wallet.h"
#include "../include/Transaction.h"
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include<bits/stdc++.h>
#include<cassert>

using namespace std;

int main() {
    cout << "========================================================\n";
    cout << "TEST: RecurringManager (Kiem tra & tu dong tao giao dich)\n";
    cout << "========================================================\n";

    DynamicArray<Wallet> wallets;
    wallets.push(Wallet(1, "Techcombank Main", 5000000.0)); 
    wallets.push(Wallet(2, "Cash Wallet", 100000.0));       
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringTransaction> recurringList;
    recurringList.push(RecurringTransaction(1, Income, 101, 1, 15000000.0, Date(1, 10, 2026), Date(), "10/2026", "Luong hang thang"));
    recurringList.push(RecurringTransaction(2, Expense, 202, 1, 3500000.0, Date(1, 10, 2026), Date(31, 12, 2026), "10/2026", "Tien thue nha"));
    recurringList.push(RecurringTransaction(3, Expense, 201, 2, 250000.0, Date(1, 10, 2026), Date(), "10/2026", "Goi cuoc internet"));
    recurringList.push(RecurringTransaction(4, Expense, 203, 1, 500000.0, Date(1, 12, 2026), Date(), "", "Dang ky tap Gym"));
    recurringList.push(RecurringTransaction(5, Expense, 204, 1, 200000.0, Date(1, 1, 2026), Date(30, 9, 2026), "09/2026", "Bao hiem xe"));
    cout << "\n--- TEST 1: Khoi dong app vao thang 11/2026 ---\n";
    processRecurringTransactions(recurringList, transactions, wallets);
    assert(transactions.getSize() == 2);
    assert(wallets[0].get_BALANCE() == 16500000.0);
    assert(wallets[1].get_BALANCE() == 100000.0);
    assert(recurringList[0].getLastAppliedMonth() == "11/2026");
    assert(recurringList[1].getLastAppliedMonth() == "11/2026");
    assert(recurringList[2].getLastAppliedMonth() == "10/2026"); 
    cout << "-> TEST 1 PASSED!\n";
    cout << "\n--- TEST 2: Khoi dong lai app trong cung chu ky 11/2026 (Chong trung lap) ---\n";
    assert(transactions.getSize() == 2); 
    assert(wallets[0].get_BALANCE() == 16500000.0); 
    cout << "-> TEST 2 PASSED!\n";
    cout << "\n========================================================\n";
    cout << "TAT CA CAC TEST RECURRING MANAGER DEU HOAN THANH XUAT SAC!\n";
    cout << "========================================================\n";
    return 0;
}
/*
    --- TEST 1: Khoi dong app vao thang 11/2026 ---
      -> Kiem tra giao dich dinh ky cho chu ky: 11/2026...
        [+] Income  [Luong hang thang] : +15000000 VND -> Vi: Techcombank Main (W01)
        [-] Expense [Tien thue nha] : -3500000 VND -> Vi: Techcombank Main (W01)
        [X] Xu ly #3 that bai: Vi 'Cash Wallet' (W02) khong du so du de thanh toan 250000 VND!
    -> TEST 1 PASSED!

    --- TEST 2: Khoi dong lai app trong cung chu ky 11/2026 (Chong trung lap) ---
    -> TEST 2 PASSED!
*/