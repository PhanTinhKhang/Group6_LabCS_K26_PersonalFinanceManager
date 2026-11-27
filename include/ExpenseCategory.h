#ifndef ExpenseCategory_H
#define ExpenseCategory_H
#include "dynamicArray.h"
#include<string>
#include<iostream>
using namespace std;

class ExpenseCategory
{
private:
    int ID;
    string NAME;

public:
    ExpenseCategory() : ID(0), NAME("") {}

    ExpenseCategory(int ID, string NAME);
    int get_id() const;
    string get_name() const;
    void edit_Category(string newNAME);
};

void set_name(ExpenseCategory &item);

bool search(int ID, DynamicArray<ExpenseCategory> &storage, int &idx);

void print(ExpenseCategory item, ostream &fout);

bool add(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item);

bool del(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item);

void view(DynamicArray<ExpenseCategory> &storage, ostream &fout);

string getCategoryNameById(int ID, DynamicArray<ExpenseCategory> &storage);

#endif