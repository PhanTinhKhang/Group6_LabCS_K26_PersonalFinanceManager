#include "../include/DynamicArray.h"
#include "../include/ExpenseCategory.h"
#include <string>

ExpenseCategory::ExpenseCategory(int ID, string NAME)
{
    this->ID = ID;
    this->NAME = NAME;
}

int ExpenseCategory::get_id() const
{
    return this->ID;
}

string ExpenseCategory::get_name() const
{
    return this->NAME;
}

void ExpenseCategory::edit_Category(string newNAME)
{
    this->NAME = newNAME;
}

void set_name(ExpenseCategory &item)
{
    string nName;
    getline(cin, nName);
    item.edit_Category(nName);
}

bool search(int ID, DynamicArray<ExpenseCategory> &storage, int &idx)
{
    int sz = storage.getSize();
    int L = 0, R = sz - 1;
    while (L <= R)
    {
        int mid = L + (R - L) / 2;
        if (ID == storage[mid].get_id())
        {
            idx = mid;
            return true;
        }
        if (storage[mid].get_id() < ID)
        {
            L = mid + 1;
        }
        else
        {
            R = mid - 1;
        }
    }
    idx = L;
    return false;
}

void print(ExpenseCategory item, ostream &fout)
{
    fout << item.get_id() << ": " << item.get_name() << '\n';
    return;
}

bool add(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item)
{
    int add_idx;
    if (search(item.get_id(), storage, add_idx))
    {
        return false;
    }
    else
    {
        storage.insert(item, add_idx);
        return true;
    }
}

bool del(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item)
{
    int del_idx;
    if (search(item.get_id(), storage, del_idx))
    {
        storage.pop(del_idx);
        return true;
    }
    else
    {
        return false;
    }
}

void view(DynamicArray<ExpenseCategory> &storage, ostream &fout)
{
    int sz = storage.getSize();
    if (sz == 0)
    {
        fout << "Expense category list is empty.\n";
        return;
    }
    for (int i = 0; i < sz; i++)
    {
        print(storage[i], fout);
    }
    return;
}

string getCategoryNameById(int ID, DynamicArray<ExpenseCategory> &storage)
{
    int idx;
    if (search(ID, storage, idx))
    {
        return storage[idx].get_name();
    }
    return (string)("Item not found.");
}