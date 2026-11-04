#ifndef IncomeSource_H
#define IncomeSource_H
#include <bits/stdc++.h>
using namespace std;

class IncomeSource
{
private:
    int ID;
    string NAME;

public:
    IncomeSource(int ID, string NAME)
    {
        this->ID = ID;
        this->NAME = NAME;
    }
    int get_id()
    {
        return this->ID;
    }
    string get_name()
    {
        return this->NAME;
    }
    void edit_IncomeSource(string newNAME)
    {
        this->NAME = newNAME;
    }
};

void print(IncomeSource item)
{
    cout << item.get_id() << " " << item.get_name() << '\n';
}

#endif