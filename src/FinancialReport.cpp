#include "../include/FinancialReport.h"
#include "../include/Dashboard.h"
#include "../include/InputValidator.h"
#include "../include/RecurringTransaction.h"
#include <iostream>
#include <iomanip>
#include <cstdio>

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

    std::string periodTitle = "Period: " + fromDate.toString() + " - " + toDate.toString();
    std::cout << "\n+------------------------------------------------------------------------------+\n";
    std::cout << "|                        TIME-BASED FINANCIAL STATEMENT                        |\n";
    std::cout << "| " << std::left << std::setw(76) << periodTitle << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "| Metric Description                                   | Amount (VND)          |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  Total Revenue & Inflow (Income)                     | "
              << std::right << std::setw(21) << formatCurrency(totalIn) << " |\n";
    std::cout << "|  Total Expenditure & Outflow (Expense)               | "
              << std::right << std::setw(21) << formatCurrency(totalOut) << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  NET PERIOD CASH FLOW                                | "
              << std::right << std::setw(21) << formatCurrency(totalIn - totalOut) << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
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
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  Wallet Period Income                                | "
              << std::right << std::setw(21) << formatCurrency(totalIn) << " |\n";
    std::cout << "|  Wallet Period Expense                               | "
              << std::right << std::setw(21) << formatCurrency(totalOut) << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  WALLET PERIOD NET FLOW                              | "
              << std::right << std::setw(21) << formatCurrency(totalIn - totalOut) << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
}

void reportMultiYearOverview(DynamicArray<Transaction>& transactions) {
    DynamicArray<int> years;
    readYearsSelection(years);

    double grandIn = 0.0, grandOut = 0.0;
    std::cout << "\n+------+------------------------+------------------------+------------------------+\n";
    std::cout << "| Year | Total Income (VND)     | Total Expense (VND)    | Net Balance (VND)      |\n";
    std::cout << "+------+------------------------+------------------------+------------------------+\n";
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
        std::cout << "| " << std::left << std::setw(4) << y << " | "
                  << std::right << std::setw(22) << formatCurrency(yIn) << " | "
                  << std::right << std::setw(22) << formatCurrency(yOut) << " | "
                  << std::right << std::setw(22) << formatCurrency(yIn - yOut) << " |\n";
    }
    std::cout << "+------+------------------------+------------------------+------------------------+\n";
    std::cout << "| TOTAL| "
              << std::right << std::setw(22) << formatCurrency(grandIn) << " | "
              << std::right << std::setw(22) << formatCurrency(grandOut) << " | "
              << std::right << std::setw(22) << formatCurrency(grandIn - grandOut) << " |\n";
    std::cout << "+------+------------------------+------------------------+------------------------+\n";
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

    std::cout << "\n+------+--------------------------------+------------------------+------------+\n";
    std::cout << "| No.  | Income Source Name             | Total Amount (VND)     |  Share (%) |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
    for (int s = 0; s < sources.getSize(); ++s) {
        double pct = (totalIn > 0.0) ? (perSource[s] * 100.0 / totalIn) : 0.0;
        std::string numStr = (s + 1 < 10 ? "0" : "") + std::to_string(s + 1);
        std::string sName = sources[s].get_name();
        if (sName.length() > 30) {
            sName = sName.substr(0, 27) + "...";
        }
        std::string pctStr = "";
        {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.1f %%", pct);
            pctStr = buf;
        }

        std::cout << "|  " << std::setw(2) << numStr << "  | "
                  << std::left << std::setw(30) << sName << " | "
                  << std::right << std::setw(22) << formatCurrency(perSource[s]) << " | "
                  << std::right << std::setw(10) << pctStr << " |\n";
    }
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "|      | TOTAL INCOME                   | "
              << std::right << std::setw(22) << formatCurrency(totalIn) << " |    100.0 % |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
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

    std::cout << "\n+------+--------------------------------+------------------------+------------+\n";
    std::cout << "| No.  | Expense Category Name          | Total Amount (VND)     |  Share (%) |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
    for (int c = 0; c < categories.getSize(); ++c) {
        double pct = (totalOut > 0.0) ? (perCategory[c] * 100.0 / totalOut) : 0.0;
        std::string numStr = (c + 1 < 10 ? "0" : "") + std::to_string(c + 1);
        std::string cName = categories[c].get_name();
        if (cName.length() > 30) {
            cName = cName.substr(0, 27) + "...";
        }
        std::string pctStr = "";
        {
            char buf[32];
            snprintf(buf, sizeof(buf), "%.1f %%", pct);
            pctStr = buf;
        }

        std::cout << "|  " << std::setw(2) << numStr << "  | "
                  << std::left << std::setw(30) << cName << " | "
                  << std::right << std::setw(22) << formatCurrency(perCategory[c]) << " | "
                  << std::right << std::setw(10) << pctStr << " |\n";
    }
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "|      | TOTAL EXPENSE                  | "
              << std::right << std::setw(22) << formatCurrency(totalOut) << " |    100.0 % |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n";
}
