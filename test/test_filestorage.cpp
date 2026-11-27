#include "../include/FileStorage.h"
using namespace std;

// test result is good :)
// g++ -I../include test_filestorage.cpp ../src/FileStorage.cpp ../src/Date.cpp ../src/Wallet.cpp ../src/ExpenseCategory.cpp ../src/IncomeSource.cpp ../src/Transaction.cpp ../src/RecurringTransaction.cpp -o run

void Print(Wallet A)
{
    cout << "DISPLAYING A WALLET \n";
    cout << A.get_ID() << " " << A.get_BALANCE() << " " << A.get_NAME();
    cout << '\n';
}
void Print(Transaction A)
{
    cout << "DISPLAYING A Transaction \n";
    cout << A.get_TYPE() << " " << A.get_DATE() << " " << A.get_DESC() << " " << A.get_TYPE();
    cout << '\n';
}
void Print(RecurringTransaction A)
{
    cout << "DISPLAYING a RECURRING \n";
    cout << A.getDescription() << " " << A.getType() << " " << A.getStartDate() << " " << A.getLastAppliedMonth();
    cout << '\n';
}
void Print(ExpenseCategory A)
{
    cout << "DISPLAYING an Expense Category \n";
    cout << A.get_id() << " " << A.get_name();
    cout << '\n';
}
void Print(IncomeSource A)
{
    cout << "DISPLAYING an INCOME SOURCE \n";
    cout << A.get_id() << A.get_name();
    cout << '\n';
}

int main()
{
    DynamicArray<Wallet> wallets;
    DynamicArray<ExpenseCategory> categories;
    DynamicArray<IncomeSource> sources;
    DynamicArray<Transaction> transactions;
    DynamicArray<RecurringTransaction> recurringList;

    wallets.push(Wallet(123, "BIDV", 120000.0));
    wallets.push(Wallet(124, "MOMO", 100000.0));
    wallets.push(Wallet(122, "Cash", 500000.0));

    categories.push(ExpenseCategory(223, "HOUSING"));
    categories.push(ExpenseCategory(224, "FOOD"));
    categories.push(ExpenseCategory(225, "ENTERTAINMENT"));

    sources.push(IncomeSource(345, "Job1"));
    sources.push(IncomeSource(346, "Job2"));

    transactions.push(Transaction(Income, Date(21, 10, 2026), 888, 1000000.0, 1, "Nguon thu la"));
    transactions.push(Transaction(Expense, Date(20, 11, 2026), 1, 5000.0, 124, "Lum ngoai duong"));

    recurringList.push(RecurringTransaction(567, Income, 234, 345, 500000.0, Date(20, 10, 2026), Date(20, 11, 2026), "last", "Don't know haha hihi hehe keke more than 16 char"));
    recurringList.push(RecurringTransaction(567, Income, 235, 12345, 1200000.0, Date(10, 10, 2026), Date(11, 11, 2026), "bla bla bla", "blo blo blo blo blo blo blo blo blo"));

    categories[1].edit_Category("FOOOOOOOOOOOOD");

    save(wallets, categories, sources, transactions, recurringList);

    wallets.clear();
    categories.clear();
    sources.clear();
    transactions.clear();
    recurringList.clear();

    load(wallets, categories, sources, transactions, recurringList);

    for (int i = 0; i < wallets.getSize(); i++)
    {
        Print(wallets[i]);
    }
    cout << "\n ###################### \n";
    for (int i = 0; i < categories.getSize(); i++)
    {
        Print(categories[i]);
    }
    cout << "\n ###################### \n";
    for (int i = 0; i < sources.getSize(); i++)
    {
        Print(sources[i]);
    }
    cout << "\n ###################### \n";
    for (int i = 0; i < transactions.getSize(); i++)
    {
        Print(transactions[i]);
    }
    cout << "\n ###################### \n";
    for (int i = 0; i < recurringList.getSize(); i++)
    {
        Print(recurringList[i]);
    }
    cout << "\n\n\n Test completed";

    return 0;
}