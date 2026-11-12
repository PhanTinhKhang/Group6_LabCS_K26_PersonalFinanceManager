#ifndef EDITINCOMESOURCE_H
#define EDITINCOMESOURCE_H

#include <string>
#include "IncomeSource.h"
#include "dynamicArray.h"

int getIndexById(DynamicArray<IncomeSource>& Sources, int id);
bool addSource(DynamicArray<IncomeSource>& Sources, const IncomeSource& NewSource);
void viewIncomeSources(DynamicArray<IncomeSource>& Sources);
std::string getSourceNameById(DynamicArray<IncomeSource>& Sources, int ID);
bool editIncomeSource(DynamicArray<IncomeSource>& Sources, int ID, const std::string& Newname);
bool deleteIncomeSource(DynamicArray<IncomeSource>& Sources, int ID);

#endif