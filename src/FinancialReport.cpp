#include "../include/FinancialReport.h"
#include "../include/Dashboard.h"
#include "../include/InputValidator.h"
#include "../include/RecurringTransaction.h"
#include <iostream>
#include <iomanip>

static bool containsYear(DynamicArray<int>& years, int target) {
    for (int i = 0; i < years.getSize(); ++i) {
        if (years[i] == target) {
            return true;
        }
    }
    return false;
}

static void readYearsSelection(DynamicArray<int>& years) {
    years.clear();
    int count = 0;
    while (true) {
        readInt(" How many years do you want to analyze (1 - 10)? ", count);
        if (count >= 1 && count <= 10) {
            break;
        }
        std::cout << " [!] Please enter a count between 1 and 10.\n";
    }

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

void reportTimeBasedSummary(DynamicArray<Transaction>& transactions) {
    Date fromDate, toDate;
    readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
    readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
    if (toDate.isBefore(fromDate)) {
        std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
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
}

void reportWalletBreakdown(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
) {
    if (wallets.getSize() == 0) {
        std::cout << "\n [ERROR] No wallets available.\n";
        return;
    }
    viewWallets(wallets);
    int walletId = 0;
    readInt(" Enter Wallet ID: ", walletId);
    if (!existWallet(wallets, walletId)) {
        std::cout << "\n [ERROR] Wallet ID not found.\n";
        return;
    }

    Date fromDate, toDate;
    readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
    readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
    if (toDate.isBefore(fromDate)) {
        std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
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
}

void reportMultiYearOverview(DynamicArray<Transaction>& transactions) {
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
}

void reportIncomeBreakdownBySource(
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
) {
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
}

void reportExpenseBreakdownByCategory(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
) {
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
}
