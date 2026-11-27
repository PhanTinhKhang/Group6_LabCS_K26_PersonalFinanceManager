#include "../include/Statistics.h"
#include<bits/stdc++.h>

bool containsYear(DynamicArray<int>& years, int target){
    for(int i=0; i<years.getSize(); i++){
        if(years[i]==target){
            return true;
        }
    }
    return false;
}


void readYearsSelection(DynamicArray<int>& years){
    years.clear();
    int count=0;
    while(true){
        readInt(" How many years do you want to analyze (1 - 10)? ", count);
        if(count>=1 && count<=10){
            break;
        }
        std::cout << " [!] Please enter a count between 1 and 10.\n";
    }

    for(int i=0; i<count; i++){
        int y=0;
        while(true){
            readInt("  Enter Year #" + std::to_string(i+1) + " (1900 - 2100): ", y);
            if(y<1900 || y>2100){
                std::cout << "  [!] Year must be between 1900 and 2100.\n";
                continue;
            }
            if(containsYear(years, y)){
                std::cout << "  [!] Year already selected. Please enter a different year.\n";
                continue;
            }
            years.push(y);
            break;
        }
    }
}

void reportTimeBasedSummary(DynamicArray<Transaction>& transactions){
    Date fromDate, toDate;
    readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
    readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
    if(toDate.isBefore(fromDate)){
        std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
        return;
    }
    double totalIn=0.0, totalOut=0.0;
    int countIncome=0, countExpense=0;
    for(int i=0; i<transactions.getSize(); i++){
        if(transactions[i].get_DATE().isInRange(fromDate, toDate)){
            if(transactions[i].get_TYPE()==Income){
                totalIn+=transactions[i].get_AMOUNT();
                countIncome++;
            } 
            else{
                totalOut+=transactions[i].get_AMOUNT();
                ++countExpense;
            }
        }
    }
    double netBalance=totalIn-totalOut;
    std::cout << "\n========================================================================================\n";
    std::cout << " SUMMARY FROM " << fromDate.toString() << " TO " << toDate.toString() << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  Total Income   (" << std::setw(4) << countIncome  << " txn) : +" << formatCurrency(totalIn) << "\n";
    std::cout << "  Total Expense  (" << std::setw(4) << countExpense << " txn) : -" << formatCurrency(totalOut) << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  Net Balance                       :  " << formatCurrency(netBalance) << "\n";
    if(netBalance>0){
        std::cout << "  Status                            :  SURPLUS\n";
    } 
    else if(netBalance<0){
        std::cout << "  Status                            :  DEFICIT\n";
    } 
    else{
        std::cout << "  Status                            :  BALANCED\n";
    }
    std::cout << "========================================================================================\n";
}

void reportWalletBreakdown(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions
){
    if(wallets.getSize()==0){
        std::cout << "\n [ERROR] No wallets available.\n";
        return;
    }
    viewWallets(wallets);
    int walletId=0;
    readInt(" Enter Wallet ID: ", walletId);
    if(!existWallet(wallets, walletId)){
        std::cout << "\n [ERROR] Wallet ID not found.\n";
        return;
    }

    Date fromDate, toDate;
    readDate(" Enter Start Date (DD/MM/YYYY): ", fromDate);
    readDate(" Enter End Date (DD/MM/YYYY): ", toDate);
    if(toDate.isBefore(fromDate)){
        std::cout << "\n [ERROR] End Date cannot be before Start Date.\n";
        return;
    }
    double totalIn=0.0, totalOut=0.0;
    int countIncome=0, countExpense=0;
    DynamicArray<Transaction> filtered;
    for(int i=0; i<transactions.getSize(); i++){
        if(transactions[i].get_WALLET()==walletId &&
            transactions[i].get_DATE().isInRange(fromDate, toDate)){
            filtered.push(transactions[i]);
            if(transactions[i].get_TYPE()==Income){
                totalIn+=transactions[i].get_AMOUNT();
                countIncome++;
            } 
            else{
                totalOut+=transactions[i].get_AMOUNT();
                ++countExpense;
            }
        }
    }
    std::string walletName=getWalletNameById(walletId, wallets);
    double netFlow=totalIn-totalOut;
    std::cout << "\n========================================================================================\n";
    std::cout << " WALLET REPORT: " << walletName
              << " (ID: " << walletId << ")\n";
    std::cout << " Period: " << fromDate.toString() << " - " << toDate.toString() << "\n";
    std::cout << "========================================================================================\n";

    if(filtered.getSize()==0){
        std::cout << "  No transactions found for this wallet in the selected period.\n";
    } 
    else{
        printTransactionTable(filtered, wallets, categories, sources);
    }
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  Wallet Period Income  (" << std::setw(4) << countIncome  << " txn) : +" << formatCurrency(totalIn) << "\n";
    std::cout << "  Wallet Period Expense (" << std::setw(4) << countExpense << " txn) : -" << formatCurrency(totalOut) << "\n";
    std::cout << "  Wallet Net Flow                              :  " << formatCurrency(netFlow) << "\n";
    std::cout << "========================================================================================\n";
}

void reportMultiYearOverview(DynamicArray<Transaction>& transactions){
    DynamicArray<int> years;
    readYearsSelection(years);
    double grandIn=0.0, grandOut=0.0;
    std::cout << "\n========================================================================================\n";
    std::cout << " MULTI-YEAR INCOME / EXPENSE OVERVIEW\n";
    std::cout << "========================================================================================\n";
    std::cout << std::left << std::setw(8) << "Year"
              << std::right << std::setw(24) << "Total Income"
              << std::setw(24) << "Total Expense"
              << std::setw(24) << "Net Balance" << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    for(int i=0; i<years.getSize(); i++){
        int y=years[i];
        double yIn=0.0, yOut=0.0;
        for(int j=0; j<transactions.getSize(); j++){
            if(transactions[j].get_DATE().getYear()==y){
                if(transactions[j].get_TYPE()==Income) {
                    yIn+=transactions[j].get_AMOUNT();
                } 
                else {
                    yOut+=transactions[j].get_AMOUNT();
                }
            }
        }
        grandIn+=yIn;
        grandOut+=yOut;
        double net=yIn-yOut;
        std::cout << std::left << std::setw(8) << y
                  << std::right << std::setw(24) << formatCurrency(yIn)
                  << std::setw(24) << formatCurrency(yOut)
                  << std::setw(24) << formatCurrency(net) << "\n";
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
){
    DynamicArray<int> years;
    readYearsSelection(years);

    double totalIn=0.0;
    DynamicArray<double> perSource;
    for(int i=0; i<sources.getSize(); i++){
        perSource.push(0.0);
    }
    for(int i=0; i<transactions.getSize(); i++){
        if(transactions[i].get_TYPE()==Income &&
            containsYear(years, transactions[i].get_DATE().getYear())){
            totalIn+=transactions[i].get_AMOUNT();
            int idx=-1;
            if(search(transactions[i].get_SOURCE_OR_CATEGORY_ID(), sources, idx)){
                perSource[idx]+=transactions[i].get_AMOUNT();
            }
        }
    }
    std::string yearLabel="";
    for(int i=0; i<years.getSize(); i++){
        if(i>0) yearLabel+=", ";
        yearLabel+=std::to_string(years[i]);
    }
    std::cout << "\n========================================================================================\n";
    std::cout << " ANNUAL INCOME BREAKDOWN BY SOURCE\n";
    std::cout << " Year(s): " << yearLabel << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  " << std::left << std::setw(26) << "Source Name"
              << std::right << std::setw(22) << "Amount"
              << "    " << "Pct (%)" << "\n";
    std::cout << "  " << std::string(60, '-') << "\n";
    for(int i=0; i<sources.getSize(); i++){
        double pct=(totalIn > 0.0) ? (perSource[i]*100.0/totalIn):0.0;
        std::cout << "  " << std::left << std::setw(26) << sources[i].get_name()
                  << std::right << std::setw(22) << formatCurrency(perSource[i])
                  << "  (" << std::fixed << std::setprecision(1) << pct << "%)\n";
    }
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  TOTAL INCOME: " << formatCurrency(totalIn) << "\n";
    std::cout << "========================================================================================\n";
}

void reportExpenseBreakdownByCategory(
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<Transaction>& transactions
){
    DynamicArray<int> years;
    readYearsSelection(years);
    double totalOut=0.0;
    DynamicArray<double> perCategory;
    for(int i=0; i<categories.getSize(); i++){
        perCategory.push(0.0);
    }
    for(int i=0; i<transactions.getSize(); i++){
        if(transactions[i].get_TYPE()==Expense &&
            containsYear(years, transactions[i].get_DATE().getYear())){
            totalOut+=transactions[i].get_AMOUNT();
            int idx=-1;
            if (search(transactions[i].get_SOURCE_OR_CATEGORY_ID(), categories, idx)){
                perCategory[idx]+=transactions[i].get_AMOUNT();
            }
        }
    }

    std::string yearLabel="";
    for(int i=0; i<years.getSize(); i++){
        if (i>0) yearLabel+=", ";
        yearLabel+=std::to_string(years[i]);
    }

    std::cout << "\n========================================================================================\n";
    std::cout << " ANNUAL EXPENSE BREAKDOWN BY CATEGORY\n";
    std::cout << " Year(s): " << yearLabel << "\n";
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  " << std::left << std::setw(26) << "Category Name"
              << std::right << std::setw(22) << "Amount"
              << "    " << "Pct (%)" << "\n";
    std::cout << "  " << std::string(60, '-') << "\n";
    for(int i=0; i<categories.getSize(); i++){
        double pct=(totalOut > 0.0) ? (perCategory[i]*100.0/totalOut):0.0;
        std::cout << "  " << std::left << std::setw(26) << categories[i].get_name()
                  << std::right << std::setw(22) << formatCurrency(perCategory[i])
                  << "  (" << std::fixed << std::setprecision(1) << pct << "%)\n";
    }
    std::cout << "----------------------------------------------------------------------------------------\n";
    std::cout << "  TOTAL EXPENSE: " << formatCurrency(totalOut) << "\n";
    std::cout << "========================================================================================\n";
}
