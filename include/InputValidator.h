#ifndef INPUTVALIDATOR_H
#define INPUTVALIDATOR_H

#include <string>
#include "DynamicArray.h"
#include "Date.h"
#include "Wallet.h"
#include "IncomeSource.h"
#include "ExpenseCategory.h"

std::string trimInput(const std::string& input);
void readDate(const std::string& prompt, Date& out);
void readInt(const std::string& prompt, int& out);
void readDouble(const std::string& prompt, double& out);
bool parseDate(const std::string& input, Date& output);
bool parseInt(const std::string& input, int& output);
bool parseDouble(const std::string& input, double& output);

bool existWallet(DynamicArray<Wallet>& wallet, int id);
bool existIncome(DynamicArray<IncomeSource>& source, int id);
bool existExpense(DynamicArray<ExpenseCategory>& category, int id);
#endif