#include "../include/NavigationFlow.h"
#include "../include/Persistence.h"
#include "../include/FinancialReport.h"
#include "../include/IncomeRecord.h"
#include "../include/ExpenseRecord.h"
#include "../include/InputValidator.h"
#include <iostream>

static int readSubmenuChoice(const std::string& prompt, int minChoice, int maxChoice) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimInput(line);
        if (trimmed == "0" && minChoice <= 0 && maxChoice >= 0) {
            return 0;
        }
        int val = 0;
        if (parseInt(trimmed, val) && val >= minChoice && val <= maxChoice) {
            return val;
        }
        std::cout << " [!] Invalid choice. Please enter a number from " << minChoice << " to " << maxChoice << ".\n";
    }
}

static std::string readNonEmptyLine(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimInput(line);
        if (!trimmed.empty()) {
            return trimmed;
        }
        std::cout << " [!] Input cannot be empty. Please try again.\n";
    }
}

static double readNonNegativeBalance(const std::string& prompt) {
    while (true) {
        std::cout << prompt;
        std::string line;
        std::getline(std::cin, line);
        std::string trimmed = trimInput(line);
        if (trimmed == "0" || trimmed == "0.0" || trimmed == "0.00") {
            return 0.0;
        }
        double val = 0.0;
        if (parseDouble(trimmed, val)) {
            return val;
        }
        std::cout << " [!] Invalid balance. Enter 0 or a positive number.\n";
    }
}

void initializeApp(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    if (!loadDataFromFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
        seedDefaultData(wallets, categories, sources);
    }
    clearScreen();
    processRecurringTransactions(recurringList, transactions, wallets);
}

void handleRecordIncome(
    DynamicArray<Wallet>& wallets,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                 PERSONAL FINANCE MANAGER > RECORD INCOME TRANSACTION                   \n";
    std::cout << "========================================================================================\n";

    if (sources.getSize() == 0 || wallets.getSize() == 0) {
        std::cout << " [ERROR] You must have at least one Income Source and one Wallet before recording.\n";
        pauseScreen();
        return;
    }

    std::cout << "Available Income Sources:\n";
    view(sources);
    std::cout << "\nAvailable Wallets:\n";
    viewWallets(wallets);
    std::cout << "\n";

    Date date;
    int sourceId = 0;
    double amount = 0.0;
    int walletId = 0;
    std::string desc;

    inputIncome(date, sourceId, amount, walletId, desc);

    if (addIncome(wallets, sources, transactions, date, sourceId, amount, walletId, desc)) {
        std::cout << "\n [SUCCESS] Recorded income +" << formatCurrency(amount)
                  << " into '" << getWalletNameById(walletId, wallets) << "' successfully!\n";
    } else {
        std::cout << "\n [ERROR] Failed to record income. Please check Source ID, Wallet ID, and Amount.\n";
    }
    pauseScreen();
}

void handleRecordExpense(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                PERSONAL FINANCE MANAGER > RECORD EXPENSE TRANSACTION                   \n";
    std::cout << "========================================================================================\n";

    if (categories.getSize() == 0 || wallets.getSize() == 0) {
        std::cout << " [ERROR] You must have at least one Expense Category and one Wallet before recording.\n";
        pauseScreen();
        return;
    }

    std::cout << "Available Expense Categories:\n";
    view(categories);
    std::cout << "\nAvailable Wallets:\n";
    viewWallets(wallets);
    std::cout << "\n";

    Date date;
    int cateId = 0;
    double amount = 0.0;
    int walletId = 0;
    std::string desc;

    inputExpense(date, cateId, amount, walletId, desc);

    if (addExpense(wallets, categories, transactions, date, cateId, amount, walletId, desc)) {
        std::cout << "\n [SUCCESS] Recorded expense -" << formatCurrency(amount)
                  << " from '" << getWalletNameById(walletId, wallets) << "' successfully!\n";
    } else {
        std::cout << "\n [ERROR] Failed to record expense. Insufficient balance or invalid Category/Wallet ID.\n";
    }
    pauseScreen();
}

void handleWalletManagement(DynamicArray<Wallet>& wallets) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                   PERSONAL FINANCE MANAGER > WALLET MANAGEMENT                         \n";
    std::cout << "========================================================================================\n";
    viewWallets(wallets);
    std::cout << "\n  [1] Create New Wallet\n";
    std::cout << "  [2] Edit Wallet Name\n";
    std::cout << "  [3] Delete Wallet\n";
    std::cout << "  [4] View Wallets Overview\n";
    std::cout << "  [0] Return to Dashboard\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int choice = readSubmenuChoice(" [?] Select option (0 - 4): ", 0, 4);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        int id = 0;
        readInt(" Enter new Wallet ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Wallet Name: ");
        double balance = readNonNegativeBalance(" Enter Initial Balance (VND): ");
        if (createWallet(wallets, id, name, balance)) {
            std::cout << "\n [SUCCESS] Wallet '" << name << "' (ID: " << id << ") created successfully!\n";
        }
        pauseScreen();
    } else if (choice == 2) {
        int id = 0;
        readInt(" Enter Wallet ID to rename: ", id);
        std::string newName = readNonEmptyLine(" Enter new Wallet Name: ");
        if (editWalletName(wallets, id, newName)) {
            std::cout << "\n [SUCCESS] Wallet ID " << id << " renamed to '" << newName << "' successfully!\n";
        }
        pauseScreen();
    } else if (choice == 3) {
        int id = 0;
        readInt(" Enter Wallet ID to delete: ", id);
        if (deleteWallet(wallets, id)) {
            std::cout << "\n [SUCCESS] Wallet ID " << id << " deleted successfully!\n";
        }
        pauseScreen();
    } else if (choice == 4) {
        std::cout << "\n [SUCCESS] Wallet overview displayed successfully.\n";
        pauseScreen();
    }
}

void handleMasterDataManagement(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                 PERSONAL FINANCE MANAGER > MASTER DATA MANAGEMENT                      \n";
    std::cout << "========================================================================================\n";
    std::cout << " --- Expense Categories ---\n";
    if (categories.getSize() == 0) {
        std::cout << "  (Empty)\n";
    } else {
        view(categories);
    }
    std::cout << "\n --- Income Sources ---\n";
    if (sources.getSize() == 0) {
        std::cout << "  (Empty)\n";
    } else {
        view(sources);
    }
    std::cout << "\n  [1] Add Expense Category       [4] Add Income Source\n";
    std::cout << "  [2] Edit Expense Category      [5] Edit Income Source\n";
    std::cout << "  [3] Delete Expense Category    [6] Delete Income Source\n";
    std::cout << "  [7] View Master Data           [0] Return to Dashboard\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int choice = readSubmenuChoice(" [?] Select option (0 - 7): ", 0, 7);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        int id = 0;
        readInt(" Enter Expense Category ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Category Name: ");
        add(categories, ExpenseCategory(id, name));
        std::cout << "\n [SUCCESS] Expense Category '" << name << "' added successfully!\n";
        pauseScreen();
    } else if (choice == 2) {
        int id = 0;
        readInt(" Enter Expense Category ID to edit: ", id);
        int idx = -1;
        if (search(id, categories, idx)) {
            std::string newName = readNonEmptyLine(" Enter new Category Name: ");
            categories[idx].edit_Category(newName);
            std::cout << "\n [SUCCESS] Expense Category ID " << id << " updated to '" << newName << "' successfully!\n";
        } else {
            std::cout << "\n [ERROR] Expense Category ID " << id << " not found.\n";
        }
        pauseScreen();
    } else if (choice == 3) {
        int id = 0;
        readInt(" Enter Expense Category ID to delete: ", id);
        del(categories, ExpenseCategory(id, ""));
        std::cout << "\n [SUCCESS] Expense Category ID " << id << " deletion processed successfully!\n";
        pauseScreen();
    } else if (choice == 4) {
        int id = 0;
        readInt(" Enter Income Source ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Source Name: ");
        add(sources, IncomeSource(id, name));
        std::cout << "\n [SUCCESS] Income Source '" << name << "' added successfully!\n";
        pauseScreen();
    } else if (choice == 5) {
        int id = 0;
        readInt(" Enter Income Source ID to edit: ", id);
        int idx = -1;
        if (search(id, sources, idx)) {
            std::string newName = readNonEmptyLine(" Enter new Source Name: ");
            sources[idx].edit_IncomeSource(newName);
            std::cout << "\n [SUCCESS] Income Source ID " << id << " updated to '" << newName << "' successfully!\n";
        } else {
            std::cout << "\n [ERROR] Income Source ID " << id << " not found.\n";
        }
        pauseScreen();
    } else if (choice == 6) {
        int id = 0;
        readInt(" Enter Income Source ID to delete: ", id);
        del(sources, IncomeSource(id, ""));
        std::cout << "\n [SUCCESS] Income Source ID " << id << " deletion processed successfully!\n";
        pauseScreen();
    } else if (choice == 7) {
        std::cout << "\n [SUCCESS] Master data list displayed successfully.\n";
        pauseScreen();
    }
}

void handleRecurringTransactions(
    DynamicArray<RecurringTransaction>& recurringList,
    DynamicArray<Transaction>& transactions,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "            PERSONAL FINANCE MANAGER > RECURRING TRANSACTIONS (MONTHLY)                 \n";
    std::cout << "========================================================================================\n";
    printRecurringTransactionsTable(recurringList, wallets, categories, sources);
    std::cout << "\n  [1] Add Recurring Rule\n";
    std::cout << "  [2] Process Recurring Rules for Current Month\n";
    std::cout << "  [3] Delete Recurring Rule\n";
    std::cout << "  [4] View Recurring Rules Table\n";
    std::cout << "  [0] Return to Dashboard\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int choice = readSubmenuChoice(" [?] Select option (0 - 4): ", 0, 4);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        if (wallets.getSize() == 0) {
            std::cout << "\n [ERROR] Please create a wallet first.\n";
            pauseScreen();
            return;
        }
        int id = 0;
        readInt(" Enter Recurring Rule ID: ", id);
        bool duplicate = false;
        for (int i = 0; i < recurringList.getSize(); ++i) {
            if (recurringList[i].getId() == id) {
                duplicate = true;
                break;
            }
        }
        if (duplicate) {
            std::cout << "\n [ERROR] Recurring Rule ID already exists.\n";
            pauseScreen();
            return;
        }

        int typeInt = readSubmenuChoice(" Type ([1] Income, [2] Expense): ", 1, 2);
        TransactionType txType = (typeInt == 1) ? Income : Expense;

        int srcOrCatId = 0;
        if (txType == Income) {
            if (sources.getSize() == 0) {
                std::cout << "\n [ERROR] No income sources available.\n";
                pauseScreen();
                return;
            }
            view(sources);
            readInt(" Enter Income Source ID: ", srcOrCatId);
            if (!existIncome(sources, srcOrCatId)) {
                std::cout << "\n [ERROR] Income Source ID not found.\n";
                pauseScreen();
                return;
            }
        } else {
            if (categories.getSize() == 0) {
                std::cout << "\n [ERROR] No expense categories available.\n";
                pauseScreen();
                return;
            }
            view(categories);
            readInt(" Enter Expense Category ID: ", srcOrCatId);
            if (!existExpense(categories, srcOrCatId)) {
                std::cout << "\n [ERROR] Expense Category ID not found.\n";
                pauseScreen();
                return;
            }
        }

        viewWallets(wallets);
        int walletId = 0;
        readInt(" Enter Target Wallet ID: ", walletId);
        if (!existWallet(wallets, walletId)) {
            std::cout << "\n [ERROR] Wallet ID not found.\n";
            pauseScreen();
            return;
        }

        double amount = 0.0;
        readDouble(" Enter Amount (VND): ", amount);

        Date startDate;
        readDate(" Enter Start Date (DD/MM/YYYY): ", startDate);

        Date endDate(1, 1, 1900);
        while (true) {
            std::cout << " Enter End Date (DD/MM/YYYY) or press [Enter] for ongoing: ";
            std::string line;
            std::getline(std::cin, line);
            std::string trimmed = trimInput(line);
            if (trimmed.empty()) {
                break;
            }
            Date parsedEnd;
            if (parseDate(trimmed, parsedEnd) && !parsedEnd.isBefore(startDate)) {
                endDate = parsedEnd;
                break;
            }
            std::cout << " [!] Invalid End Date (must be valid and >= Start Date).\n";
        }

        std::string desc = readNonEmptyLine(" Enter Description: ");
        recurringList.push(RecurringTransaction(id, txType, srcOrCatId, walletId, amount, startDate, endDate, "", desc));
        std::cout << "\n [SUCCESS] Recurring rule ID " << id << " added successfully!\n";
        pauseScreen();
    } else if (choice == 2) {
        std::cout << "\n";
        processRecurringTransactions(recurringList, transactions, wallets);
        std::cout << "\n [SUCCESS] Recurring transactions cycle processed successfully!\n";
        pauseScreen();
    } else if (choice == 3) {
        int id = 0;
        readInt(" Enter Recurring Rule ID to delete: ", id);
        int foundIdx = -1;
        for (int i = 0; i < recurringList.getSize(); ++i) {
            if (recurringList[i].getId() == id) {
                foundIdx = i;
                break;
            }
        }
        if (foundIdx != -1) {
            recurringList.pop(foundIdx);
            std::cout << "\n [SUCCESS] Recurring rule ID " << id << " deleted successfully!\n";
        } else {
            std::cout << "\n [ERROR] Recurring Rule ID not found.\n";
        }
        pauseScreen();
    } else if (choice == 4) {
        std::cout << "\n [SUCCESS] Recurring rules overview displayed successfully.\n";
        pauseScreen();
    }
}

void handleStatistics(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                  PERSONAL FINANCE MANAGER > STATISTICS & REPORTS                       \n";
    std::cout << "========================================================================================\n";
    std::cout << "  [1] Time-based Summary (From Date A to Date B)\n";
    std::cout << "  [2] Time & Wallet-based Breakdown\n";
    std::cout << "  [3] Annual Income/Expense Overview (Multi-Year)\n";
    std::cout << "  [4] Annual Income Breakdown by Income Source\n";
    std::cout << "  [5] Annual Expense Breakdown by Expense Category\n";
    std::cout << "  [6] View All Transactions History\n";
    std::cout << "  [0] Return to Dashboard\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int choice = readSubmenuChoice(" [?] Select report (0 - 6): ", 0, 6);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        reportTimeBasedSummary(transactions);
        std::cout << "\n [SUCCESS] Time-based summary report generated successfully.\n";
        pauseScreen();
    } else if (choice == 2) {
        reportWalletBreakdown(wallets, categories, sources, transactions);
        std::cout << "\n [SUCCESS] Time and wallet breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 3) {
        reportMultiYearOverview(transactions);
        std::cout << "\n [SUCCESS] Multi-year overview report generated successfully.\n";
        pauseScreen();
    } else if (choice == 4) {
        reportIncomeBreakdownBySource(sources, transactions);
        std::cout << "\n [SUCCESS] Annual income breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 5) {
        reportExpenseBreakdownByCategory(categories, transactions);
        std::cout << "\n [SUCCESS] Annual expense breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 6) {
        printTransactionTable(transactions, wallets, categories, sources);
        std::cout << "\n [SUCCESS] Transaction history displayed successfully.\n";
        pauseScreen();
    }
}

void handlePersistence(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    clearScreen();
    std::cout << "========================================================================================\n";
    std::cout << "                  PERSONAL FINANCE MANAGER > DATA PERSISTENCE                           \n";
    std::cout << "========================================================================================\n";
    std::cout << " Storage File: " << DATA_FILE << "\n\n";
    std::cout << "  [1] Save Current Data to Disk\n";
    std::cout << "  [2] Reload Data from Disk\n";
    std::cout << "  [0] Return to Dashboard\n";
    std::cout << "----------------------------------------------------------------------------------------\n";

    int choice = readSubmenuChoice(" [?] Select option (0 - 2): ", 0, 2);
    if (choice == 0) {
        return;
    }
    if (choice == 1) {
        if (saveDataToFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
            std::cout << "\n [SUCCESS] All financial data saved to '" << DATA_FILE << "' successfully!\n";
        } else {
            std::cout << "\n [ERROR] Failed to save financial data to '" << DATA_FILE << "'.\n";
        }
        pauseScreen();
    } else if (choice == 2) {
        if (loadDataFromFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
            std::cout << "\n [SUCCESS] All financial data reloaded from '" << DATA_FILE << "' successfully!\n";
        } else {
            std::cout << "\n [ERROR] Could not read '" << DATA_FILE << "' (missing file or invalid format).\n";
        }
        pauseScreen();
    }
}

void shutdownApp(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    saveDataToFile(DATA_FILE, wallets, categories, sources, transactions, recurringList);
    std::cout << "\n [SUCCESS] All financial data saved. Exiting Personal Finance Manager. Goodbye!\n";
}

void handleInvalidChoice() {
    std::cout << "\n [!] Invalid selection. Please enter a valid number from 0 to 7.\n";
    pauseScreen();
}
