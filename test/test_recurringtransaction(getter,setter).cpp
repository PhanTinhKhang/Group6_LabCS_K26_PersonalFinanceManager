#include<bits/stdc++.h>
#include <cassert>
#include "../include/RecurringTransaction.h"

using namespace std;

int main(){
    RecurringTransaction item(101, Expense, "C02", "W01", 3500000.0, "01/10/2026", "", "", "Tien thue nha");
    assert(item.getId() == 101);
    assert(item.getType() == Expense);
    assert(item.getSourceOrCatId() == "C02");
    assert(item.getWalletId() == "W01");
    assert(item.getAmount() == 3500000.0);
    assert(item.getStartDate() == "01/10/2026");
    assert(item.getEndDate() == "");
    assert(item.getLastAppliedMonth() == "");
    assert(item.getDescription() == "Tien thue nha");
    cout << "GETTER PASSED!\n";
    item.setAmount(16000000.0);
    assert(item.getAmount() == 16000000.0);
    item.setLastAppliedMonth("10/2026");
    assert(item.getLastAppliedMonth() == "10/2026");
    cout << "SETTER PASSED\n";
    return 0;
}
// GETTER PASSED!
// SETTER PASSED!