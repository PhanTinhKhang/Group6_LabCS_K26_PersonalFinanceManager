#include "../include/NavigationFlow.h"
#include "../include/Persistence.h"
#include "../include/IncomeRecord.h"
#include "../include/ExpenseRecord.h"
#include "../include/InputValidator.h"
#include "../include/UITheme.h"
#include "../include/Statistics.h"
#include "../include/WalletTransferUI.h"
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
        std::cout << " " << Color::BOLD << Color::RED << "[!]" << Color::RESET << " Invalid choice. Please enter a number from " << minChoice << " to " << maxChoice << ".\n";
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
        std::cout << " " << Color::BOLD << Color::RED << "[!]" << Color::RESET << " Input cannot be empty. Please try again.\n";
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
        std::cout << " " << Color::BOLD << Color::RED << "[!]" << Color::RESET << " Invalid balance. Enter 0 or a positive number.\n";
    }
}

void initializeApp(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    initConsole();
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
    printHeader("RECORD INCOME TRANSACTION");

    if (sources.getSize() == 0 || wallets.getSize() == 0) {
        std::cout << " " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " You must have at least one Income Source and one Wallet before recording.\n";
        pauseScreen();
        return;
    }

    std::cout << " " << Color::BOLD << Color::WHITE << "Available Income Sources:" << Color::RESET << "\n";
    view(sources);
    std::cout << "\n " << Color::BOLD << Color::WHITE << "Available Wallets:" << Color::RESET << "\n";
    viewWallets(wallets);
    std::cout << "\n";

    Date date;
    int sourceId = 0;
    double amount = 0.0;
    int walletId = 0;
    std::string desc;

    inputIncome(date, sourceId, amount, walletId, desc);

    if (addIncome(wallets, sources, transactions, date, sourceId, amount, walletId, desc)) {
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recorded income +" << formatCurrency(amount)
                  << " into '" << getWalletNameById(walletId, wallets) << "' successfully!\n";
    } else {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Failed to record income. Please check Source ID, Wallet ID, and Amount.\n";
    }
    pauseScreen();
}

void handleRecordExpense(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
) {
    clearScreen();
    printHeader("RECORD EXPENSE TRANSACTION");

    if (categories.getSize() == 0 || wallets.getSize() == 0) {
        std::cout << " " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " You must have at least one Expense Category and one Wallet before recording.\n";
        pauseScreen();
        return;
    }

    std::cout << " " << Color::BOLD << Color::WHITE << "Available Expense Categories:" << Color::RESET << "\n";
    view(categories);
    std::cout << "\n " << Color::BOLD << Color::WHITE << "Available Wallets:" << Color::RESET << "\n";
    viewWallets(wallets);
    std::cout << "\n";

    Date date;
    int cateId = 0;
    double amount = 0.0;
    int walletId = 0;
    std::string desc;

    inputExpense(date, cateId, amount, walletId, desc);

    if (addExpense(wallets, categories, transactions, date, cateId, amount, walletId, desc)) {
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recorded expense -" << formatCurrency(amount)
                  << " from '" << getWalletNameById(walletId, wallets) << "' successfully!\n";
    } else {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Failed to record expense. Insufficient balance or invalid Category/Wallet ID.\n";
    }
    pauseScreen();
}

void handleWalletManagement(DynamicArray<Wallet>& wallets) {
    clearScreen();
    printHeader("WALLET MANAGEMENT");
    viewWallets(wallets);
    std::cout << "\n  " << Color::CYAN << "[1]" << Color::RESET << " Create New Wallet\n";
    std::cout << "  " << Color::CYAN << "[2]" << Color::RESET << " Edit Wallet Name\n";
    std::cout << "  " << Color::CYAN << "[3]" << Color::RESET << " Delete Wallet\n";
    std::cout << "  " << Color::CYAN << "[4]" << Color::RESET << " Transfer Between Wallets\n";
    std::cout << "  " << Color::CYAN << "[5]" << Color::RESET << " View Wallets Overview\n";
    std::cout << "  " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " Return to Dashboard\n";
    std::cout << Color::CYAN << "----------------------------------------------------------------------------------------\n" << Color::RESET;

    int choice = readSubmenuChoice("  ▸ Select option (0 - 5): ", 0, 5);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        int id = 0;
        readInt(" Enter new Wallet ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Wallet Name: ");
        double balance = readNonNegativeBalance(" Enter Initial Balance (VND): ");
        if (createWallet(wallets, id, name, balance)) {
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Wallet '" << name << "' (ID: " << id << ") created successfully!\n";
        }
        pauseScreen();
    } else if (choice == 2) {
        int id = 0;
        readInt(" Enter Wallet ID to rename: ", id);
        std::string newName = readNonEmptyLine(" Enter new Wallet Name: ");
        if (editWalletName(wallets, id, newName)) {
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Wallet ID " << id << " renamed to '" << newName << "' successfully!\n";
        }
        pauseScreen();
    } else if (choice == 3) {
        int id = 0;
        readInt(" Enter Wallet ID to delete: ", id);
        if (deleteWallet(wallets, id)) {
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Wallet ID " << id << " deleted successfully!\n";
        }
        pauseScreen();
    } else if (choice == 4) {
        handleWalletsTransfer(wallets);
    } else if (choice == 5) {
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Wallet overview displayed successfully.\n";
        pauseScreen();
    }
}

void handleMasterDataManagement(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    clearScreen();
    printHeader("MASTER DATA MANAGEMENT");
    std::cout << " " << Color::BOLD << Color::WHITE << "Expense Categories:" << Color::RESET << "\n";
    view(categories);
    std::cout << "\n " << Color::BOLD << Color::WHITE << "Income Sources:" << Color::RESET << "\n";
    view(sources);
    std::cout << "\n  " << Color::CYAN << "[1]" << Color::RESET << " Add Expense Category       " << Color::CYAN << "[4]" << Color::RESET << " Add Income Source\n";
    std::cout << "  " << Color::CYAN << "[2]" << Color::RESET << " Edit Expense Category      " << Color::CYAN << "[5]" << Color::RESET << " Edit Income Source\n";
    std::cout << "  " << Color::CYAN << "[3]" << Color::RESET << " Delete Expense Category    " << Color::CYAN << "[6]" << Color::RESET << " Delete Income Source\n";
    std::cout << "  " << Color::CYAN << "[7]" << Color::RESET << " View Master Data           " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " Return to Dashboard\n";
    std::cout << Color::CYAN << "----------------------------------------------------------------------------------------\n" << Color::RESET;

    int choice = readSubmenuChoice("  ▸ Select option (0 - 7): ", 0, 7);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        int id = 0;
        readInt(" Enter Expense Category ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Category Name: ");
        add(categories, ExpenseCategory(id, name));
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Expense Category '" << name << "' added successfully!\n";
        pauseScreen();
    } else if (choice == 2) {
        int id = 0;
        readInt(" Enter Expense Category ID to edit: ", id);
        int idx = -1;
        if (search(id, categories, idx)) {
            std::string newName = readNonEmptyLine(" Enter new Category Name: ");
            categories[idx].edit_Category(newName);
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Expense Category ID " << id << " updated to '" << newName << "' successfully!\n";
        } else {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Expense Category ID " << id << " not found.\n";
        }
        pauseScreen();
    } else if (choice == 3) {
        int id = 0;
        readInt(" Enter Expense Category ID to delete: ", id);
        del(categories, ExpenseCategory(id, ""));
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Expense Category ID " << id << " deletion processed successfully!\n";
        pauseScreen();
    } else if (choice == 4) {
        int id = 0;
        readInt(" Enter Income Source ID (positive integer): ", id);
        std::string name = readNonEmptyLine(" Enter Source Name: ");
        add(sources, IncomeSource(id, name));
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Income Source '" << name << "' added successfully!\n";
        pauseScreen();
    } else if (choice == 5) {
        int id = 0;
        readInt(" Enter Income Source ID to edit: ", id);
        int idx = -1;
        if (search(id, sources, idx)) {
            std::string newName = readNonEmptyLine(" Enter new Source Name: ");
            sources[idx].edit_IncomeSource(newName);
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Income Source ID " << id << " updated to '" << newName << "' successfully!\n";
        } else {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Income Source ID " << id << " not found.\n";
        }
        pauseScreen();
    } else if (choice == 6) {
        int id = 0;
        readInt(" Enter Income Source ID to delete: ", id);
        del(sources, IncomeSource(id, ""));
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Income Source ID " << id << " deletion processed successfully!\n";
        pauseScreen();
    } else if (choice == 7) {
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Master data list displayed successfully.\n";
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
    printHeader("RECURRING TRANSACTIONS (MONTHLY)");
    printRecurringTransactionsTable(recurringList, wallets, categories, sources);
    std::cout << "\n  " << Color::CYAN << "[1]" << Color::RESET << " Add Recurring Rule\n";
    std::cout << "  " << Color::CYAN << "[2]" << Color::RESET << " Process Recurring Rules for Current Month\n";
    std::cout << "  " << Color::CYAN << "[3]" << Color::RESET << " Delete Recurring Rule\n";
    std::cout << "  " << Color::CYAN << "[4]" << Color::RESET << " View Recurring Rules Table\n";
    std::cout << "  " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " Return to Dashboard\n";
    std::cout << Color::CYAN << "----------------------------------------------------------------------------------------\n" << Color::RESET;

    int choice = readSubmenuChoice("  ▸ Select option (0 - 4): ", 0, 4);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        if (wallets.getSize() == 0) {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Please create a wallet first.\n";
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
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Recurring Rule ID already exists.\n";
            pauseScreen();
            return;
        }

        int typeInt = readSubmenuChoice(" Type ([1] Income, [2] Expense): ", 1, 2);
        TransactionType txType = (typeInt == 1) ? Income : Expense;

        int srcOrCatId = 0;
        if (txType == Income) {
            if (sources.getSize() == 0) {
                std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " No income sources available.\n";
                pauseScreen();
                return;
            }
            view(sources);
            readInt(" Enter Income Source ID: ", srcOrCatId);
            if (!existIncome(sources, srcOrCatId)) {
                std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Income Source ID not found.\n";
                pauseScreen();
                return;
            }
        } else {
            if (categories.getSize() == 0) {
                std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " No expense categories available.\n";
                pauseScreen();
                return;
            }
            view(categories);
            readInt(" Enter Expense Category ID: ", srcOrCatId);
            if (!existExpense(categories, srcOrCatId)) {
                std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Expense Category ID not found.\n";
                pauseScreen();
                return;
            }
        }

        viewWallets(wallets);
        int walletId = 0;
        readInt(" Enter Target Wallet ID: ", walletId);
        if (!existWallet(wallets, walletId)) {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Wallet ID not found.\n";
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
            std::cout << " " << Color::BOLD << Color::RED << "[!]" << Color::RESET << " Invalid End Date (must be valid and >= Start Date).\n";
        }

        std::string desc = readNonEmptyLine(" Enter Description: ");
        recurringList.push(RecurringTransaction(id, txType, srcOrCatId, walletId, amount, startDate, endDate, "", desc));
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recurring rule ID " << id << " added successfully!\n";
        pauseScreen();
    } else if (choice == 2) {
        std::cout << "\n";
        processRecurringTransactions(recurringList, transactions, wallets);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recurring transactions cycle processed successfully!\n";
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
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recurring rule ID " << id << " deleted successfully!\n";
        } else {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Recurring Rule ID not found.\n";
        }
        pauseScreen();
    } else if (choice == 4) {
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Recurring rules overview displayed successfully.\n";
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
    printHeader("STATISTICS & REPORTS");
    std::cout << "  " << Color::CYAN << "[1]" << Color::RESET << " Time-based Summary (From Date A to Date B)\n";
    std::cout << "  " << Color::CYAN << "[2]" << Color::RESET << " Time & Wallet-based Breakdown\n";
    std::cout << "  " << Color::CYAN << "[3]" << Color::RESET << " Annual Income/Expense Overview (Multi-Year)\n";
    std::cout << "  " << Color::CYAN << "[4]" << Color::RESET << " Annual Income Breakdown by Income Source\n";
    std::cout << "  " << Color::CYAN << "[5]" << Color::RESET << " Annual Expense Breakdown by Expense Category\n";
    std::cout << "  " << Color::CYAN << "[6]" << Color::RESET << " View All Transactions History\n";
    std::cout << "  " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " Return to Dashboard\n";
    std::cout << Color::CYAN << "----------------------------------------------------------------------------------------\n" << Color::RESET;

    int choice = readSubmenuChoice("  ▸ Select report (0 - 6): ", 0, 6);
    if (choice == 0) {
        return;
    }

    if (choice == 1) {
        reportTimeBasedSummary(transactions);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Time-based summary report generated successfully.\n";
        pauseScreen();
    } else if (choice == 2) {
        reportWalletBreakdown(wallets, categories, sources, transactions);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Time and wallet breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 3) {
        reportMultiYearOverview(transactions);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Multi-year overview report generated successfully.\n";
        pauseScreen();
    } else if (choice == 4) {
        reportIncomeBreakdownBySource(sources, transactions);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Annual income breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 5) {
        reportExpenseBreakdownByCategory(categories, transactions);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Annual expense breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 6) {
        printTransactionTable(transactions, wallets, categories, sources);
        std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " Transaction history displayed successfully.\n";
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
    printHeader("DATA PERSISTENCE & STORAGE");
    std::cout << "  " << Color::GRAY << "Storage File: " << Color::WHITE << DATA_FILE << Color::RESET << "\n\n";
    std::cout << "  " << Color::CYAN << "[1]" << Color::RESET << " Save Current Data to Disk\n";
    std::cout << "  " << Color::CYAN << "[2]" << Color::RESET << " Reload Data from Disk\n";
    std::cout << "  " << Color::BOLD << Color::RED << "[0]" << Color::RESET << " Return to Dashboard\n";
    std::cout << Color::CYAN << "----------------------------------------------------------------------------------------\n" << Color::RESET;

    int choice = readSubmenuChoice("  ▸ Select option (0 - 2): ", 0, 2);
    if (choice == 0) {
        return;
    }
    if (choice == 1) {
        if (saveDataToFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " All financial data saved to '" << DATA_FILE << "' successfully!\n";
        } else {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Failed to save financial data to '" << DATA_FILE << "'.\n";
        }
        pauseScreen();
    } else if (choice == 2) {
        if (loadDataFromFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
            std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " All financial data reloaded from '" << DATA_FILE << "' successfully!\n";
        } else {
            std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Could not read '" << DATA_FILE << "' (missing file or invalid format).\n";
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
    std::cout << "\n " << Color::BOLD << Color::GREEN << "[SUCCESS]" << Color::RESET << " All financial data saved. Exiting Personal Finance Manager. Goodbye!\n";
}

void handleInvalidChoice() {
    std::cout << "\n " << Color::BOLD << Color::RED << "[!]" << Color::RESET << " Invalid selection. Please enter a valid number from 0 to 7.\n";
    pauseScreen();
}
