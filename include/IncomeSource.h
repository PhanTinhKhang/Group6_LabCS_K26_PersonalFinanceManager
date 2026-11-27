#ifndef IncomeSource_H
#define IncomeSource_H
#include "dynamicArray.h"
#include <string>
#include <iostream>
using namespace std;

class IncomeSource
{
private:
    int ID;
    string NAME;

public:
    IncomeSource() : ID(0), NAME("") {}

    IncomeSource(int ID, string NAME);
    int get_id() const;
    string get_name() const;
    void edit_IncomeSource(string newNAME);
};

void set_name(IncomeSource &item);

bool search(int ID, DynamicArray<IncomeSource> &storage, int &idx);

void print(const IncomeSource &item, ostream &fout);

bool add(DynamicArray<IncomeSource> &storage, IncomeSource item);

bool del(DynamicArray<IncomeSource> &storage, IncomeSource item);

void view(DynamicArray<IncomeSource> &storage, ostream &fout);

string getSourceNameById(int ID, DynamicArray<IncomeSource> &storage);

#endif