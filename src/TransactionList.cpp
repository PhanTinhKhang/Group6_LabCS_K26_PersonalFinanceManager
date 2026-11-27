#include "../include/RecurringTransaction.h"
#include "../include/Dashboard.h"
#include "../include/UITheme.h"
#include <iostream>
#include <iomanip>
#include <string>

static std::string truncateStr(const std::string& str, size_t maxLen) {
    if (str.length() <= maxLen) {
        return str;
    }
    if (maxLen <= 3) {
        return str.substr(0, maxLen);
    }
    return str.substr(0, maxLen - 3) + "...";
}

void printTransactionTable(
    DynamicArray<Transaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
){
    int size = list.getSize();
    if (size <= 0) {
        std::cout << Color::CYAN << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n";
        std::cout << "| No.  | Date       | Type      | Category / Source      | Wallet               | Amount (VND)           | Description                  |\n";
        std::cout << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n";
        std::cout << "|  No transactions found in this register.                                                                                              |\n";
        std::cout << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n" << Color::RESET;
        return;
    }

    std::cout << Color::CYAN << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n";
    std::cout << "| No.  | Date       | Type      | Category / Source      | Wallet               | Amount (VND)           | Description                  |\n";
    std::cout << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n" << Color::RESET;

    for (int i = 0; i < size; i++) {
        const Transaction& tx = list[i];
        std::string numStr = (i + 1 < 10 ? "0" : "") + std::to_string(i + 1);
        std::string typeStr = (tx.get_TYPE() == Income) ? "INCOME" : "EXPENSE";
        std::string rawCatName = (typeStr == "INCOME")
            ? getSourceNameById(tx.get_SOURCE_OR_CATEGORY_ID(), sources)
            : getCategoryNameById(tx.get_SOURCE_OR_CATEGORY_ID(), categories);
        std::string catName = truncateStr(rawCatName, 22);
        std::string walletName = truncateStr(getWalletNameById(tx.get_WALLET(), wallets), 20);
        std::string dateStr = tx.get_DATE().toString();
        std::string descStr = truncateStr(tx.get_DESC(), 28);
        std::string amountStr = formatCurrency(tx.get_AMOUNT());

        const char* typeColor = (tx.get_TYPE() == Income) ? Color::GREEN : Color::RED;

        std::cout << Color::CYAN << "|  " << Color::RESET << std::setw(2) << numStr << Color::CYAN << "  | "
                  << Color::WHITE << std::left << std::setw(10) << dateStr << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << typeColor << std::left << std::setw(9) << typeStr << Color::RESET << Color::CYAN << " | "
                  << Color::WHITE << std::left << std::setw(22) << catName << Color::RESET << Color::CYAN << " | "
                  << Color::WHITE << std::left << std::setw(20) << walletName << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << typeColor << std::right << std::setw(22) << amountStr << Color::RESET << Color::CYAN << " | "
                  << Color::GRAY << std::left << std::setw(28) << descStr << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }

    std::cout << Color::CYAN << "+------+------------+-----------+------------------------+----------------------+------------------------+------------------------------+\n" << Color::RESET;
}

void printRecurringTransactionsTable(
    DynamicArray<RecurringTransaction>& list,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    int size = list.getSize();
    if (size <= 0) {
        std::cout << Color::CYAN << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n";
        std::cout << "|  ID  | Type      | Category / Source      | Wallet               | Amount (VND)           | Start Date   | Last Applied | Description                |\n";
        std::cout << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n";
        std::cout << "|  No recurring transaction rules registered.                                                                                                |\n";
        std::cout << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n" << Color::RESET;
        return;
    }

    std::cout << Color::CYAN << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n";
    std::cout << "|  ID  | Type      | Category / Source      | Wallet               | Amount (VND)           | Start Date   | Last Applied | Description                |\n";
    std::cout << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n" << Color::RESET;

    for (int i = 0; i < size; i++) {
        const RecurringTransaction& tx = list[i];
        std::string typeStr = (tx.getType() == Income) ? "INCOME" : "EXPENSE";
        std::string rawCatName = (typeStr == "INCOME")
            ? getSourceNameById(tx.getSourceOrCatId(), sources)
            : getCategoryNameById(tx.getSourceOrCatId(), categories);
        std::string catName = truncateStr(rawCatName, 22);
        std::string walletName = truncateStr(getWalletNameById(tx.getWalletId(), wallets), 20);
        std::string startDateStr = tx.getStartDate().toString();
        std::string lastAppliedStr = tx.getLastAppliedMonth().empty() ? "N/A" : tx.getLastAppliedMonth();
        std::string descStr = truncateStr(tx.getDescription(), 26);
        std::string amountStr = formatCurrency(tx.getAmount());

        const char* typeColor = (tx.getType() == Income) ? Color::GREEN : Color::RED;

        std::cout << Color::CYAN << "| " << Color::YELLOW << std::right << std::setw(4) << tx.getId() << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << typeColor << std::left << std::setw(9) << typeStr << Color::RESET << Color::CYAN << " | "
                  << Color::WHITE << std::left << std::setw(22) << catName << Color::RESET << Color::CYAN << " | "
                  << Color::WHITE << std::left << std::setw(20) << walletName << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << typeColor << std::right << std::setw(22) << amountStr << Color::RESET << Color::CYAN << " | "
                  << Color::WHITE << std::left << std::setw(12) << startDateStr << Color::RESET << Color::CYAN << " | "
                  << Color::GRAY << std::left << std::setw(12) << lastAppliedStr << Color::RESET << Color::CYAN << " | "
                  << Color::GRAY << std::left << std::setw(26) << descStr << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }

    std::cout << Color::CYAN << "+------+-----------+------------------------+----------------------+------------------------+--------------+--------------+----------------------------+\n" << Color::RESET;
}
