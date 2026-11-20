#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include "../include/Wallet.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include "../include/Transaction.h"
#include "../include/RecurringTransaction.h"
#include "../include/Dashboard.h"
#include "../include/InputValidator.h"
#include "../include/IncomeRecord.h"
#include "../include/ExpenseRecord.h"

static const std::string DATA_FILE = "finance_data.bin";
static const std::string DATA_MAGIC = "PFM_BIN_V1";

void writeString(std::ofstream& out, const std::string& str) {
    size_t len = str.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        out.write(str.data(), static_cast<std::streamsize>(len));
    }
}

bool readString(std::ifstream& in, std::string& str) {
    size_t len = 0;
    if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) {
        return false;
    }
    if (len > 1000000) {
        return false;
    }
    str.resize(len);
    if (len > 0 && !in.read(&str[0], static_cast<std::streamsize>(len))) {
        return false;
    }
    return true;
}

void writeDate(std::ofstream& out, const Date& dt) {
    int d = dt.getDay();
    int m = dt.getMonth();
    int y = dt.getYear();
    out.write(reinterpret_cast<const char*>(&d), sizeof(d));
    out.write(reinterpret_cast<const char*>(&m), sizeof(m));
    out.write(reinterpret_cast<const char*>(&y), sizeof(y));
}

bool readDateBin(std::ifstream& in, Date& dt) {
    int d = 1, m = 1, y = 2026;
    if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) return false;
    if (!in.read(reinterpret_cast<char*>(&m), sizeof(m))) return false;
    if (!in.read(reinterpret_cast<char*>(&y), sizeof(y))) return false;
    dt.setDate(d, m, y);
    return true;
}

bool saveDataToFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    writeString(out, DATA_MAGIC);

    int wCount = wallets.getSize();
    out.write(reinterpret_cast<const char*>(&wCount), sizeof(wCount));
    for (int i = 0; i < wCount; ++i) {
        int id = wallets[i].get_ID();
        double bal = wallets[i].get_BALANCE();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, wallets[i].get_NAME());
        out.write(reinterpret_cast<const char*>(&bal), sizeof(bal));
    }

    int cCount = categories.getSize();
    out.write(reinterpret_cast<const char*>(&cCount), sizeof(cCount));
    for (int i = 0; i < cCount; ++i) {
        int id = categories[i].get_id();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, categories[i].get_name());
    }

    int sCount = sources.getSize();
    out.write(reinterpret_cast<const char*>(&sCount), sizeof(sCount));
    for (int i = 0; i < sCount; ++i) {
        int id = sources[i].get_id();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, sources[i].get_name());
    }

    int tCount = transactions.getSize();
    out.write(reinterpret_cast<const char*>(&tCount), sizeof(tCount));
    for (int i = 0; i < tCount; ++i) {
        int typeInt = (transactions[i].get_TYPE() == Income) ? 1 : 2;
        int srcCatId = transactions[i].get_SOURCE_OR_CATEGORY_ID();
        double amt = transactions[i].get_AMOUNT();
        int wId = transactions[i].get_WALLET();
        out.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));
        writeDate(out, transactions[i].get_DATE());
        out.write(reinterpret_cast<const char*>(&srcCatId), sizeof(srcCatId));
        out.write(reinterpret_cast<const char*>(&amt), sizeof(amt));
        out.write(reinterpret_cast<const char*>(&wId), sizeof(wId));
        writeString(out, transactions[i].get_DESC());
    }

    int rCount = recurringList.getSize();
    out.write(reinterpret_cast<const char*>(&rCount), sizeof(rCount));
    for (int i = 0; i < rCount; ++i) {
        int id = recurringList[i].getId();
        int typeInt = (recurringList[i].getType() == Income) ? 1 : 2;
        int srcCatId = recurringList[i].getSourceOrCatId();
        int wId = recurringList[i].getWalletId();
        double amt = recurringList[i].getAmount();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        out.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));
        out.write(reinterpret_cast<const char*>(&srcCatId), sizeof(srcCatId));
        out.write(reinterpret_cast<const char*>(&wId), sizeof(wId));
        out.write(reinterpret_cast<const char*>(&amt), sizeof(amt));
        writeDate(out, recurringList[i].getStartDate());
        writeDate(out, recurringList[i].getEndDate());
        writeString(out, recurringList[i].getLastAppliedMonth());
        writeString(out, recurringList[i].getDescription());
    }

    return true;
}

bool loadDataFromFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    std::string magic;
    if (!readString(in, magic) || magic != DATA_MAGIC) {
        return false;
    }

    DynamicArray<Wallet> newWallets;
    DynamicArray<ExpenseCategory> newCategories;
    DynamicArray<IncomeSource> newSources;
    DynamicArray<Transaction> newTransactions;
    DynamicArray<RecurringTransaction> newRecurring;

    int wCount = 0;
    if (!in.read(reinterpret_cast<char*>(&wCount), sizeof(wCount)) || wCount < 0) return false;
    for (int i = 0; i < wCount; ++i) {
        int id = 0;
        double bal = 0.0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        if (!in.read(reinterpret_cast<char*>(&bal), sizeof(bal))) return false;
        newWallets.push(Wallet(id, name, bal));
    }

    int cCount = 0;
    if (!in.read(reinterpret_cast<char*>(&cCount), sizeof(cCount)) || cCount < 0) return false;
    for (int i = 0; i < cCount; ++i) {
        int id = 0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        newCategories.push(ExpenseCategory(id, name));
    }

    int sCount = 0;
    if (!in.read(reinterpret_cast<char*>(&sCount), sizeof(sCount)) || sCount < 0) return false;
    for (int i = 0; i < sCount; ++i) {
        int id = 0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        newSources.push(IncomeSource(id, name));
    }

    int tCount = 0;
    if (!in.read(reinterpret_cast<char*>(&tCount), sizeof(tCount)) || tCount < 0) return false;
    for (int i = 0; i < tCount; ++i) {
        int typeInt = 1, srcCatId = 0, wId = 0;
        double amt = 0.0;
        Date dt;
        std::string desc;
        if (!in.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt))) return false;
        if (!readDateBin(in, dt)) return false;
        if (!in.read(reinterpret_cast<char*>(&srcCatId), sizeof(srcCatId))) return false;
        if (!in.read(reinterpret_cast<char*>(&amt), sizeof(amt))) return false;
        if (!in.read(reinterpret_cast<char*>(&wId), sizeof(wId))) return false;
        if (!readString(in, desc)) return false;
        TransactionType tType = (typeInt == 1) ? Income : Expense;
        newTransactions.push(Transaction(tType, dt, srcCatId, amt, wId, desc));
    }

    int rCount = 0;
    if (!in.read(reinterpret_cast<char*>(&rCount), sizeof(rCount)) || rCount < 0) return false;
    for (int i = 0; i < rCount; ++i) {
        int id = 0, typeInt = 2, srcCatId = 0, wId = 0;
        double amt = 0.0;
        Date startDt, endDt;
        std::string lastApplied, desc;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!in.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt))) return false;
        if (!in.read(reinterpret_cast<char*>(&srcCatId), sizeof(srcCatId))) return false;
        if (!in.read(reinterpret_cast<char*>(&wId), sizeof(wId))) return false;
        if (!in.read(reinterpret_cast<char*>(&amt), sizeof(amt))) return false;
        if (!readDateBin(in, startDt)) return false;
        if (!readDateBin(in, endDt)) return false;
        if (!readString(in, lastApplied)) return false;
        if (!readString(in, desc)) return false;
        TransactionType tType = (typeInt == 1) ? Income : Expense;
        newRecurring.push(RecurringTransaction(id, tType, srcCatId, wId, amt, startDt, endDt, lastApplied, desc));
    }

    wallets = newWallets;
    categories = newCategories;
    sources = newSources;
    transactions = newTransactions;
    recurringList = newRecurring;
    return true;
}

void seedDefaultData(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    createWallet(wallets, 1, "Physical Cash", 3450000.0);
    createWallet(wallets, 2, "Techcombank Debit", 18500000.0);
    createWallet(wallets, 3, "MoMo E-Wallet", 1500000.0);

    categories.push(ExpenseCategory(1, "Food & Dining"));
    categories.push(ExpenseCategory(2, "Transportation"));
    categories.push(ExpenseCategory(3, "House Rent"));
    categories.push(ExpenseCategory(4, "Utilities"));
    categories.push(ExpenseCategory(5, "Shopping"));

    sources.push(IncomeSource(1, "Monthly Salary"));
    sources.push(IncomeSource(2, "Project Bonus"));
    sources.push(IncomeSource(3, "Freelance"));
}

int readSubmenuChoice(const std::string& prompt, int minChoice, int maxChoice) {
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

std::string readNonEmptyLine(const std::string& prompt) {
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

double readNonNegativeBalance(const std::string& prompt) {
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

bool containsYear(DynamicArray<int>& years, int target) {
    for (int i = 0; i < years.getSize(); ++i) {
        if (years[i] == target) {
            return true;
        }
    }
    return false;
}

void readYearsSelection(DynamicArray<int>& years) {
    years.clear();
    int count = readSubmenuChoice(" How many years do you want to analyze (1 - 10)? ", 1, 10);
    for (int i = 0; i < count; ++i) {
        int y = 0;
        while (true) {
            readInt("  Enter Year #" + std::to_string(i + 1) + " (1900 - 2100): ", y);
            if (y < 1900 || y > 2100) {
                std::cout << "  [!] Year must be between 1900 and 2100.\n";
                continue;
            }
            if (containsYear(years, y)) {
                std::cout << "  [!] Year already selected. Please enter a different year.\n";
                continue;
            }
            years.push(y);
            break;
        }
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
        Date fromDate, toDate;
        readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
        readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
        if (toDate.isBefore(fromDate)) {
            std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
            pauseScreen();
            return;
        }

        double totalIn = 0.0, totalOut = 0.0;
        for (int i = 0; i < transactions.getSize(); ++i) {
            if (transactions[i].get_DATE().isInRange(fromDate, toDate)) {
                if (transactions[i].get_TYPE() == Income) {
                    totalIn += transactions[i].get_AMOUNT();
                } else {
                    totalOut += transactions[i].get_AMOUNT();
                }
            }
        }

        std::cout << "\n========================================================================================\n";
        std::cout << " SUMMARY FROM " << fromDate.toString() << " TO " << toDate.toString() << "\n";
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << "  Total Income  : +" << formatCurrency(totalIn) << "\n";
        std::cout << "  Total Expense : -" << formatCurrency(totalOut) << "\n";
        std::cout << "  Net Balance   :  " << formatCurrency(totalIn - totalOut) << "\n";
        std::cout << "========================================================================================\n";
        std::cout << "\n [SUCCESS] Time-based summary report generated successfully.\n";
        pauseScreen();
    } else if (choice == 2) {
        if (wallets.getSize() == 0) {
            std::cout << "\n [ERROR] No wallets available.\n";
            pauseScreen();
            return;
        }
        viewWallets(wallets);
        int walletId = 0;
        readInt(" Enter Wallet ID: ", walletId);
        if (!existWallet(wallets, walletId)) {
            std::cout << "\n [ERROR] Wallet ID not found.\n";
            pauseScreen();
            return;
        }

        Date fromDate, toDate;
        readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
        readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
        if (toDate.isBefore(fromDate)) {
            std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
            pauseScreen();
            return;
        }

        double totalIn = 0.0, totalOut = 0.0;
        DynamicArray<Transaction> filtered;
        for (int i = 0; i < transactions.getSize(); ++i) {
            if (transactions[i].get_WALLET() == walletId &&
                transactions[i].get_DATE().isInRange(fromDate, toDate)) {
                filtered.push(transactions[i]);
                if (transactions[i].get_TYPE() == Income) {
                    totalIn += transactions[i].get_AMOUNT();
                } else {
                    totalOut += transactions[i].get_AMOUNT();
                }
            }
        }

        std::cout << "\n WALLET REPORT: " << getWalletNameById(walletId, wallets)
                  << " (" << fromDate.toString() << " - " << toDate.toString() << ")\n";
        printTransactionTable(filtered, wallets, categories, sources);
        std::cout << "  Wallet Period Income  : +" << formatCurrency(totalIn) << "\n";
        std::cout << "  Wallet Period Expense : -" << formatCurrency(totalOut) << "\n";
        std::cout << "  Wallet Net Flow       :  " << formatCurrency(totalIn - totalOut) << "\n";
        std::cout << "\n [SUCCESS] Time and wallet breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 3) {
        DynamicArray<int> years;
        readYearsSelection(years);

        double grandIn = 0.0, grandOut = 0.0;
        std::cout << "\n========================================================================================\n";
        std::cout << std::left << std::setw(8) << "Year"
                  << std::right << std::setw(24) << "Total Income"
                  << std::setw(24) << "Total Expense"
                  << std::setw(24) << "Net Balance" << "\n";
        std::cout << "----------------------------------------------------------------------------------------\n";
        for (int yi = 0; yi < years.getSize(); ++yi) {
            int y = years[yi];
            double yIn = 0.0, yOut = 0.0;
            for (int ti = 0; ti < transactions.getSize(); ++ti) {
                if (transactions[ti].get_DATE().getYear() == y) {
                    if (transactions[ti].get_TYPE() == Income) {
                        yIn += transactions[ti].get_AMOUNT();
                    } else {
                        yOut += transactions[ti].get_AMOUNT();
                    }
                }
            }
            grandIn += yIn;
            grandOut += yOut;
            std::cout << std::left << std::setw(8) << y
                      << std::right << std::setw(24) << formatCurrency(yIn)
                      << std::setw(24) << formatCurrency(yOut)
                      << std::setw(24) << formatCurrency(yIn - yOut) << "\n";
        }
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << std::left << std::setw(8) << "TOTAL"
                  << std::right << std::setw(24) << formatCurrency(grandIn)
                  << std::setw(24) << formatCurrency(grandOut)
                  << std::setw(24) << formatCurrency(grandIn - grandOut) << "\n";
        std::cout << "========================================================================================\n";
        std::cout << "\n [SUCCESS] Multi-year overview report generated successfully.\n";
        pauseScreen();
    } else if (choice == 4) {
        DynamicArray<int> years;
        readYearsSelection(years);

        double totalIn = 0.0;
        DynamicArray<double> perSource;
        for (int s = 0; s < sources.getSize(); ++s) {
            perSource.push(0.0);
        }

        for (int ti = 0; ti < transactions.getSize(); ++ti) {
            if (transactions[ti].get_TYPE() == Income &&
                containsYear(years, transactions[ti].get_DATE().getYear())) {
                totalIn += transactions[ti].get_AMOUNT();
                int idx = -1;
                if (search(transactions[ti].get_SOURCE_OR_CATEGORY_ID(), sources, idx)) {
                    perSource[idx] += transactions[ti].get_AMOUNT();
                }
            }
        }

        std::cout << "\n========================================================================================\n";
        std::cout << " ANNUAL INCOME BREAKDOWN BY SOURCE\n";
        std::cout << "----------------------------------------------------------------------------------------\n";
        for (int s = 0; s < sources.getSize(); ++s) {
            double pct = (totalIn > 0.0) ? (perSource[s] * 100.0 / totalIn) : 0.0;
            std::cout << "  " << std::left << std::setw(26) << sources[s].get_name()
                      << std::right << std::setw(22) << formatCurrency(perSource[s])
                      << "  (" << std::fixed << std::setprecision(1) << pct << "%)\n";
        }
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << "  TOTAL INCOME: " << formatCurrency(totalIn) << "\n";
        std::cout << "========================================================================================\n";
        std::cout << "\n [SUCCESS] Annual income breakdown report generated successfully.\n";
        pauseScreen();
    } else if (choice == 5) {
        DynamicArray<int> years;
        readYearsSelection(years);

        double totalOut = 0.0;
        DynamicArray<double> perCategory;
        for (int c = 0; c < categories.getSize(); ++c) {
            perCategory.push(0.0);
        }

        for (int ti = 0; ti < transactions.getSize(); ++ti) {
            if (transactions[ti].get_TYPE() == Expense &&
                containsYear(years, transactions[ti].get_DATE().getYear())) {
                totalOut += transactions[ti].get_AMOUNT();
                int idx = -1;
                if (search(transactions[ti].get_SOURCE_OR_CATEGORY_ID(), categories, idx)) {
                    perCategory[idx] += transactions[ti].get_AMOUNT();
                }
            }
        }

        std::cout << "\n========================================================================================\n";
        std::cout << " ANNUAL EXPENSE BREAKDOWN BY CATEGORY\n";
        std::cout << "----------------------------------------------------------------------------------------\n";
        for (int c = 0; c < categories.getSize(); ++c) {
            double pct = (totalOut > 0.0) ? (perCategory[c] * 100.0 / totalOut) : 0.0;
            std::cout << "  " << std::left << std::setw(26) << categories[c].get_name()
                      << std::right << std::setw(22) << formatCurrency(perCategory[c])
                      << "  (" << std::fixed << std::setprecision(1) << pct << "%)\n";
        }
        std::cout << "----------------------------------------------------------------------------------------\n";
        std::cout << "  TOTAL EXPENSE: " << formatCurrency(totalOut) << "\n";
        std::cout << "========================================================================================\n";
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

int main() {
    DynamicArray<Wallet> wallets;
    DynamicArray<ExpenseCategory> categories;
    DynamicArray<IncomeSource> sources;
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringTransaction> recurringList;

    if (!loadDataFromFile(DATA_FILE, wallets, categories, sources, transactions, recurringList)) {
        seedDefaultData(wallets, categories, sources);
    }

    clearScreen();
    processRecurringTransactions(recurringList, transactions, wallets);

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
                saveDataToFile(DATA_FILE, wallets, categories, sources, transactions, recurringList);
                std::cout << "\n [SUCCESS] All financial data saved. Exiting Personal Finance Manager. Goodbye!\n";
                running = false;
                break;
            default:
                std::cout << "\n [!] Invalid selection. Please enter a valid number from 0 to 7.\n";
                pauseScreen();
                break;
        }
    }

    return 0;
}
