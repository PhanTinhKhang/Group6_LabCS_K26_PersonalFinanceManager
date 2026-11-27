#include "../include/DynamicArray.h"
#include "../include/Wallet.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include "../include/Transaction.h"
#include "../include/RecurringTransaction.h"
#include "../include/Dashboard.h"
#include "../include/NavigationFlow.h"
#include "../include/UITheme.h"

int main() {
    initConsole();
    DynamicArray<Wallet> wallets;
    DynamicArray<ExpenseCategory> categories;
    DynamicArray<IncomeSource> sources;
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringTransaction> recurringList;

    initializeApp(wallets, categories, sources, transactions, recurringList);

    bool running = true;
    while (running) {
        clearScreen();
        renderDashboard(wallets);
        MenuAction action = promptMenuChoice();

        switch (action) {
            case MenuAction::RECORD_INCOME:
                handleRecordIncome(wallets, sources, transactions);
                break;
            case MenuAction::RECORD_EXPENSE:
                handleRecordExpense(wallets, categories, transactions);
                break;
            case MenuAction::MANAGE_WALLETS:
                handleWalletManagement(wallets);
                break;
            case MenuAction::MANAGE_MASTER_DATA:
                handleMasterDataManagement(categories, sources);
                break;
            case MenuAction::RECURRING_TRANSACTIONS:
                handleRecurringTransactions(recurringList, transactions, wallets, categories, sources);
                break;
            case MenuAction::STATISTICS_REPORTS:
                handleStatistics(wallets, categories, sources, transactions);
                break;
            case MenuAction::PERSISTENCE_SETTINGS:
                handlePersistence(wallets, categories, sources, transactions, recurringList);
                break;
            case MenuAction::EXIT:
                shutdownApp(wallets, categories, sources, transactions, recurringList);
                running = false;
                break;
            default:
                handleInvalidChoice();
                break;
        }
    }

    return 0;
}
