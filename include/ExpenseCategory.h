#ifndef ExpenseCategory_H
#define ExpenseCategory_H
#include "DynamicArray.h"
#include <bits/stdc++.h>
using namespace std;

class ExpenseCategory
{
private:
    int ID;
    string NAME;

public:
    ExpenseCategory() : ID(0), NAME("") {}

    ExpenseCategory(int ID, string NAME)
    {
        this->ID = ID;
        this->NAME = NAME;
    }
    int get_id() const
    {
        return this->ID;
    }
    string get_name() const
    {
        return this->NAME;
    }
    void edit_Category(string newNAME)
    {
        this->NAME = newNAME;
    }
};

void set_name(ExpenseCategory &item);

bool operator<(ExpenseCategory item1, ExpenseCategory item2);

bool search(int ID, DynamicArray<ExpenseCategory> &storage, int &idx);

void print(ExpenseCategory item);

void add(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item);

void del(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item);

void view(DynamicArray<ExpenseCategory> &storage);

string getCategoryNameById(int ID, DynamicArray<ExpenseCategory> &storage);

#endif