#include <iostream>
#include "../include/DynamicArray.h"
#include "../include/Date.h"
#include "../include/Wallet.h"
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include "../include/Transaction.h"
#include "../include/RecurringTransaction.h"

using namespace std;

int main(){
    //Declaration of main dynamic arrays
    DynamicArray<Wallet> wallets;
    DynamicArray<ExpenseCategory> categories;
    DynamicArray<IncomeSource> sources;
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringTransaction> recurringList;

    return 0;
}