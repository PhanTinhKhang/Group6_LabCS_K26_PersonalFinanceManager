#ifndef ExpenseCategory_H
#define ExpenseCategory_H
#include <bits/stdc++.h>
using namespace std;

class ExpenseCategory
{
private:
    int ID;
    string NAME;

public:
    ExpenseCategory(int ID, string NAME)
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
    void edit_Category(string newNAME)
    {
        this->NAME = newNAME;
    }
};

void print(ExpenseCategory item)
{
    cout << item.get_id() << " " << item.get_name() << '\n';
}

#endif