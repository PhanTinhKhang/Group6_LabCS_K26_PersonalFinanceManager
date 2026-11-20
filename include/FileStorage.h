#ifndef FileStorage_H
#define FileStorage_H
#include <fstream>
#include <iostream>

#include "ExpenseCategory.h"
#include "IncomeSource.h"
#include "Wallet.h"
#include "Transaction.h"
#include "RecurringTransaction.h"

void write_string(const string &A, long long &addressptr, long long &str_ptr, ofstream &fout);
void write_date(const Date &A, long long &addressptr, ofstream &fout);
void read_date(long long &address, Date &store, ifstream &fin);
string read_string(long long &address, ifstream &fin);

bool save(DynamicArray<Wallet> &W, DynamicArray<ExpenseCategory> &Ex,
          DynamicArray<IncomeSource> &So, DynamicArray<Transaction> &Tran,
          DynamicArray<RecurringTransaction> &Recur);

bool load(DynamicArray<Wallet> &W, DynamicArray<ExpenseCategory> &Ex,
          DynamicArray<IncomeSource> &So, DynamicArray<Transaction> &Tran,
          DynamicArray<RecurringTransaction> &Recur);

#endif