#include<bits/stdc++.h>
#include <cassert>
#include "../include/RecurringTransaction.h"

using namespace std;

int main(){
    RecurringTransaction item(101, Expense, 202, 1, 3500000.0, Date(1,10,2026), Date(), "", "Tien thue nha");
    assert(item.getId() == 101);
    assert(item.getType() == Expense);
    assert(item.getSourceOrCatId() == 202);
    assert(item.getWalletId() == 1);
    assert(item.getAmount() == 3500000.0);
    assert(item.getStartDate().isEqual(Date(1,10,2026)));
    assert(item.getEndDate().isEqual(Date()));
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