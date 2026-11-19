#include "../include/RecurringTransaction.h"
#include<bits/stdc++.h>

void printTransactionTable(
    DynamicArray<Transaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
){
    int size = list.getSize();
    if (size <= 0) {
        std::cout << "-> Danh sach giao dich trong!\n";
        return;
    }

    std::cout << "\n========================================================================================================================\n";
    std::cout << std::left 
              << std::setw(6)  << "No." 
              << std::setw(13)  << "Date"
              << std::setw(10) << "Type"
              << std::setw(22) << "Category/Source"
              << std::setw(20) << "Wallet"
              << std::right << std::setw(15) << "Amount (VND)"
              << std::left  << " " << std::setw(25) << "Description"
              << "\n========================================================================================================================\n";
    for(int i=0; i<list.getSize(); i++){
        const Transaction& tx= list[i];
        std::string typeStr = (tx.get_TYPE() == Income) ? "INCOME" : "EXPENSE";
        std::string catName = (typeStr=="INCOME") ? getSourceNameById(tx.get_SOURCE_OR_CATEGORY_ID(), sources) : getCategoryNameById(tx.get_SOURCE_OR_CATEGORY_ID(), categories);
        std::string walletName = getWalletNameById(tx.get_WALLET(), wallets);

        std::cout << std::left 
                  << std::setw(6)  << i+1
                  << std::setw(13)  << tx.get_DATE()
                  << std::setw(10) << typeStr
                  << std::setw(22) << catName
                  << std::setw(20) << walletName
                  << std::right << std::setw(15) << std::fixed << std::setprecision(0) << tx.get_AMOUNT()
                  << std::left  << " " << std::setw(25) << tx.get_DESC()
                  << "\n";
    }
    std::cout << "========================================================================================================================\n";
}


void printRecurringTransactionsTable(DynamicArray<RecurringTransaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources) {
    int size = list.getSize();
    if (size <= 0) {
        std::cout << "-> Danh sach giao dich dinh ky trong!\n";
        return;
    }

    std::cout << "\n========================================================================================================================\n";
    std::cout << std::left 
              << std::setw(6)  << "ID"
              << std::setw(10) << "Type"
              << std::setw(22) << "Category/Source"
              << std::setw(20) << "Wallet"
              << std::setw(15) << "Amount (VND)"
              << std::setw(14) << "Start Date"
              << std::setw(14) << "Last Applied"
              << std::setw(25) << "Description"
              << "\n========================================================================================================================\n";

    for (int i = 0; i < size; i++) {
        const RecurringTransaction& tx = list[i];

        std::string typeStr = (tx.getType() == Income) ? "INCOME" : "EXPENSE";
        std::string catName = (typeStr=="INCOME") ? getSourceNameById(tx.getSourceOrCatId(), sources) : getCategoryNameById(tx.getSourceOrCatId(), categories);
        std::string walletName = getWalletNameById(tx.getWalletId(), wallets);

        std::cout << std::left 
                  << std::setw(6)  << tx.getId()
                  << std::setw(10) << typeStr
                  << std::setw(22) << catName
                  << std::setw(20) << walletName
                  << std::setw(15) << std::fixed << std::setprecision(0) << tx.getAmount()
                  << std::setw(14) << tx.getStartDate().toString()
                  << std::setw(14) << (tx.getLastAppliedMonth().empty() ? "N/A" : tx.getLastAppliedMonth())
                  << std::setw(25) << tx.getDescription()
                  << "\n";
    }
    std::cout << "========================================================================================================================\n";
}
