#include "../include/RecurringTransaction.h"
#include <bits/stdc++.h>

bool hasValidEndDate(const RecurringTransaction& tx) {
    Date end = tx.getEndDate();
    Date start = tx.getStartDate();
    if (end.isBefore(start)) return false;
    return true;
}

void processRecurringTransactions(
    DynamicArray<RecurringTransaction>& recurringList,
    DynamicArray<Transaction>& transactions,
    DynamicArray<Wallet>& wallets
) {
    time_t now=time(0);
    tm *ltm=localtime(&now);
    Date currentDate=Date(ltm->tm_mday,ltm->tm_mon+1,ltm->tm_year+1900);
    int currentMonth = currentDate.getMonth();
    int currentYear = currentDate.getYear();
    std::ostringstream oss;
    oss << (currentMonth < 10 ? "0" : "") << currentMonth << "/" << currentYear;
    std::string currentCycleStr = oss.str();
    std::string altCycleStr = std::to_string(currentMonth) + "/" + std::to_string(currentYear);
    int size = recurringList.getSize();
    std::cout << "  -> Kiem tra giao dich dinh ky cho chu ky: " << currentCycleStr << "...\n";
    for(int i=0; i<size; i++) {
        RecurringTransaction& tx=recurringList[i];
        std::string lastApplied=tx.getLastAppliedMonth();
        if(lastApplied==currentCycleStr || lastApplied==altCycleStr){
            continue;
        }
        Date start=tx.getStartDate();
        if(currentYear < start.getYear() || (currentYear==start.getYear() && currentMonth < start.getMonth())){
            continue;
        }
        if(hasValidEndDate(tx)) {
            Date end=tx.getEndDate();
            if (currentYear > end.getYear() || (currentYear==end.getYear() && currentMonth > end.getMonth())) {
                continue;
            }
        }
        int walletIndex=-1;
        for (int i=0; i<wallets.getSize(); i++) {
            if (wallets[i].get_ID()==tx.getWalletId()) {
                walletIndex=i;
                break;
            }
        }
        if(walletIndex==-1){
            std::cout << "     [!] Bo qua #" << tx.getId()
                      << ": Khong tim thay vi ID '" << tx.getWalletId() << "'\n";
            continue;
        }
        bool walletUpdated = false;
        if (tx.getType()==Income) {
            wallets[walletIndex].Deposit(tx.getAmount());
            walletUpdated=true;
        } 
        else if(tx.getType()==Expense) {
            if (wallets[walletIndex].Withdrawal(tx.getAmount())) {
                walletUpdated=true;
            } else {
                std::cout << "     [X] Xu ly #" << tx.getId()
                          << " that bai: Vi '" << wallets[walletIndex].get_NAME()
                          << "' (" << tx.getWalletId() << ") khong du so du de thanh toan "
                          << std::fixed << std::setprecision(0) << tx.getAmount() << " VND!\n";
            }
        }

        if (walletUpdated) {
            int txDay = start.getDay();
            Date txDate(txDay, currentMonth, currentYear);
            transactions.push(Transaction(
                tx.getType(),
                txDate.toString(),
                tx.getSourceOrCatId(),
                tx.getAmount(),
                tx.getWalletId(),
                tx.getDescription()
            ));
            tx.setLastAppliedMonth(currentCycleStr);
            std::cout << "     [" << (tx.getType() == Income ? "+" : "-") << "] "
                      << (tx.getType() == Income ? "Income " : "Expense")
                      << " [" << tx.getDescription() << "] : "
                      << (tx.getType() == Income ? "+" : "-")
                      << std::fixed << std::setprecision(0) << tx.getAmount() << " VND -> Vi: "
                      << wallets[walletIndex].get_NAME() << " (" << tx.getWalletId() << ")\n";
        }
    }
}
