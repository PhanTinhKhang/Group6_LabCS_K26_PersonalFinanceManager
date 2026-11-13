#include "../include/Dashboard.h"
#include <cassert>
#include <iostream>

void testFormatCurrency() {
    assert(formatCurrency(0.0) == "0.00 VND");
    assert(formatCurrency(100.0) == "100.00 VND");
    assert(formatCurrency(1000.0) == "1,000.00 VND");
    assert(formatCurrency(28450000.0) == "28,450,000.00 VND");
    assert(formatCurrency(1234567.89) == "1,234,567.89 VND");
    assert(formatCurrency(-45000.0) == "-45,000.00 VND");
}

void testCalculateTotalBalance() {
    DynamicArray<Wallet> wallets;
    assert(calculateTotalBalance(wallets) == 0.0);

    wallets.push(Wallet("W_CASH", "Physical Cash", 3450000.0));
    assert(calculateTotalBalance(wallets) == 3450000.0);

    wallets.push(Wallet("W_TCB", "Techcombank Debit", 18500000.0));
    assert(calculateTotalBalance(wallets) == 21950000.0);

    wallets.push(Wallet("W_MOMO", "MoMo E-Wallet", 1500000.0));
    assert(calculateTotalBalance(wallets) == 23450000.0);

    wallets.push(Wallet("W_SAVING", "Bank Savings", 5000000.0));
    assert(calculateTotalBalance(wallets) == 28450000.0);
}

void testRenderDashboard() {
    DynamicArray<Wallet> wallets;
    wallets.push(Wallet("W_CASH", "Physical Cash", 3450000.0));
    wallets.push(Wallet("W_TCB", "Techcombank Debit", 18500000.0));
    wallets.push(Wallet("W_MOMO", "MoMo E-Wallet", 1500000.0));
    wallets.push(Wallet("W_SAVING", "Bank Savings", 5000000.0));

    renderDashboard(wallets);
}

int main() {
    testFormatCurrency();
    testCalculateTotalBalance();
    testRenderDashboard();
    std::cout << "All Dashboard unit tests passed successfully!\n";
    return 0;
}
