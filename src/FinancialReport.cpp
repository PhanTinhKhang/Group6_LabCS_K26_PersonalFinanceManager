#include "../include/FinancialReport.h"
#include "../include/Dashboard.h"
#include "../include/InputValidator.h"
#include "../include/RecurringTransaction.h"
#include "../include/UITheme.h"
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
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " End Date cannot be before Start Date.\n";
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

    double netFlow = totalIn - totalOut;
    const char* netColor = (netFlow >= 0.0) ? Color::GREEN : Color::RED;

    std::string periodTitle = "Period: " + fromDate.toString() + " - " + toDate.toString();
    std::cout << "\n" << Color::CYAN << "+------------------------------------------------------------------------------+\n";
    std::cout << "| " << Color::BOLD << Color::WHITE << "                       TIME-BASED FINANCIAL STATEMENT                        " << Color::RESET << Color::CYAN << "|\n";
    std::cout << "| " << Color::GRAY << std::left << std::setw(76) << periodTitle << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "| " << Color::WHITE << std::left << std::setw(52) << "Metric Description" << Color::RESET << Color::CYAN << " | "
              << Color::WHITE << std::left << std::setw(21) << "Amount (VND)" << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  Total Revenue & Inflow (Income)                     | "
              << Color::BOLD << Color::GREEN << std::right << std::setw(21) << formatCurrency(totalIn) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "|  Total Expenditure & Outflow (Expense)               | "
              << Color::BOLD << Color::RED << std::right << std::setw(21) << formatCurrency(totalOut) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  " << Color::BOLD << Color::WHITE << "NET PERIOD CASH FLOW                                " << Color::RESET << Color::CYAN << "| "
              << Color::BOLD << netColor << std::right << std::setw(21) << formatCurrency(netFlow) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n" << Color::RESET;
}

void reportWalletBreakdown(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
) {
    if (wallets.getSize() == 0) {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " No wallets available.\n";
        return;
    }
    viewWallets(wallets);
    int walletId = 0;
    readInt(" Enter Wallet ID: ", walletId);
    if (!existWallet(wallets, walletId)) {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " Wallet ID not found.\n";
        return;
    }

    Date fromDate, toDate;
    readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
    readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
    if (toDate.isBefore(fromDate)) {
        std::cout << "\n " << Color::BOLD << Color::RED << "[ERROR]" << Color::RESET << " End Date cannot be before Start Date.\n";
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

    double netFlow = totalIn - totalOut;
    const char* netColor = (netFlow >= 0.0) ? Color::GREEN : Color::RED;

    std::cout << "\n " << Color::BOLD << Color::WHITE << "WALLET REPORT: " << Color::YELLOW << getWalletNameById(walletId, wallets)
              << Color::GRAY << " (" << fromDate.toString() << " - " << toDate.toString() << ")" << Color::RESET << "\n";
    printTransactionTable(filtered, wallets, categories, sources);
    std::cout << Color::CYAN << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  Wallet Period Income                                | "
              << Color::BOLD << Color::GREEN << std::right << std::setw(21) << formatCurrency(totalIn) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "|  Wallet Period Expense                               | "
              << Color::BOLD << Color::RED << std::right << std::setw(21) << formatCurrency(totalOut) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n";
    std::cout << "|  " << Color::BOLD << Color::WHITE << "WALLET PERIOD NET FLOW                              " << Color::RESET << Color::CYAN << "| "
              << Color::BOLD << netColor << std::right << std::setw(21) << formatCurrency(netFlow) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------------------------------------------------------+-----------------------+\n" << Color::RESET;
}

void reportMultiYearOverview(DynamicArray<Transaction>& transactions) {
    DynamicArray<int> years;
    readYearsSelection(years);

    double grandIn = 0.0, grandOut = 0.0;
    std::cout << "\n" << Color::CYAN << "+------+------------------------+------------------------+------------------------+\n";
    std::cout << "| Year | Total Income (VND)     | Total Expense (VND)    | Net Balance (VND)      |\n";
    std::cout << "+------+------------------------+------------------------+------------------------+\n" << Color::RESET;
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
        double net = yIn - yOut;
        const char* netColor = (net >= 0.0) ? Color::GREEN : Color::RED;

        std::cout << Color::CYAN << "| " << Color::YELLOW << std::left << std::setw(4) << y << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << Color::GREEN << std::right << std::setw(22) << formatCurrency(yIn) << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << Color::RED << std::right << std::setw(22) << formatCurrency(yOut) << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << netColor << std::right << std::setw(22) << formatCurrency(net) << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }
    double grandNet = grandIn - grandOut;
    const char* grandNetColor = (grandNet >= 0.0) ? Color::GREEN : Color::RED;

    std::cout << Color::CYAN << "+------+------------------------+------------------------+------------------------+\n";
    std::cout << "| " << Color::BOLD << Color::WHITE << "TOTAL" << Color::RESET << Color::CYAN << "| "
              << Color::BOLD << Color::GREEN << std::right << std::setw(22) << formatCurrency(grandIn) << Color::RESET << Color::CYAN << " | "
              << Color::BOLD << Color::RED << std::right << std::setw(22) << formatCurrency(grandOut) << Color::RESET << Color::CYAN << " | "
              << Color::BOLD << grandNetColor << std::right << std::setw(22) << formatCurrency(grandNet) << Color::RESET << Color::CYAN << " |\n";
    std::cout << "+------+------------------------+------------------------+------------------------+\n" << Color::RESET;
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

    std::cout << "\n" << Color::CYAN << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "| No.  | Income Source Name             | Total Amount (VND)     |  Share (%) |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n" << Color::RESET;
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

        std::cout << Color::CYAN << "|  " << Color::RESET << std::setw(2) << numStr << Color::CYAN << "  | "
                  << Color::WHITE << std::left << std::setw(30) << sName << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << Color::GREEN << std::right << std::setw(22) << formatCurrency(perSource[s]) << Color::RESET << Color::CYAN << " | "
                  << Color::CYAN << std::right << std::setw(10) << pctStr << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }
    std::cout << Color::CYAN << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "|      | " << Color::BOLD << Color::WHITE << "TOTAL INCOME                   " << Color::RESET << Color::CYAN << "| "
              << Color::BOLD << Color::GREEN << std::right << std::setw(22) << formatCurrency(totalIn) << Color::RESET << Color::CYAN << " |    100.0 % |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n" << Color::RESET;
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

    std::cout << "\n" << Color::CYAN << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "| No.  | Expense Category Name          | Total Amount (VND)     |  Share (%) |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n" << Color::RESET;
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

        std::cout << Color::CYAN << "|  " << Color::RESET << std::setw(2) << numStr << Color::CYAN << "  | "
                  << Color::WHITE << std::left << std::setw(30) << cName << Color::RESET << Color::CYAN << " | "
                  << Color::BOLD << Color::RED << std::right << std::setw(22) << formatCurrency(perCategory[c]) << Color::RESET << Color::CYAN << " | "
                  << Color::CYAN << std::right << std::setw(10) << pctStr << Color::RESET << Color::CYAN << " |\n" << Color::RESET;
    }
    std::cout << Color::CYAN << "+------+--------------------------------+------------------------+------------+\n";
    std::cout << "|      | " << Color::BOLD << Color::WHITE << "TOTAL EXPENSE                  " << Color::RESET << Color::CYAN << "| "
              << Color::BOLD << Color::RED << std::right << std::setw(22) << formatCurrency(totalOut) << Color::RESET << Color::CYAN << " |    100.0 % |\n";
    std::cout << "+------+--------------------------------+------------------------+------------+\n" << Color::RESET;
}
