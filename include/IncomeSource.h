#ifndef IncomeSource_H
#define IncomeSource_H
#include "dynamicArray.h"
#include <bits/stdc++.h>
using namespace std;

class IncomeSource
{
private:
    int ID;
    string NAME;

public:
    IncomeSource() : ID(0), NAME("") {}

    IncomeSource(int ID, string NAME)
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
    void edit_IncomeSource(string newNAME)
    {
        this->NAME = newNAME;
    }
};

bool search(int ID, DynamicArray<IncomeSource> &storage, int &idx);

void print(IncomeSource item);

bool operator<(IncomeSource item1, IncomeSource item2);

void add(DynamicArray<IncomeSource> &storage, IncomeSource item);

void del(DynamicArray<IncomeSource> &storage, IncomeSource item);

void view(DynamicArray<IncomeSource> &storage);

string getSourceNameById(int ID, DynamicArray<IncomeSource> &storage);

#endif