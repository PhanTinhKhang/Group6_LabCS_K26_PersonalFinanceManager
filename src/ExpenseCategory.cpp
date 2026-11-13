#include "../include/DynamicArray.h"
#include "../include/ExpenseCategory.h"
#include <string>

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

void print(ExpenseCategory item)
{
    cout << item.get_id() << ": " << item.get_name() << '\n';
    return;
}

void add(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item)
{
    int add_idx;
    if (search(item.get_id(), storage, add_idx))
    {
        cout << "Item insertion unsuccessfully (ID already exist).\n";
    }
    else
    {
        storage.insert(item, add_idx);
        cout << "Item inserted successfully.\n";
    }
}

void del(DynamicArray<ExpenseCategory> &storage, ExpenseCategory item)
{
    int del_idx;
    if (search(item.get_id(), storage, del_idx))
    {
        storage.pop(del_idx);
        cout << "Item deleted successfully.\n";
    }
    else
    {
        cout << "Item not found.\n";
    }
}

void view(DynamicArray<ExpenseCategory> &storage)
{
    int sz = storage.getSize();
    for (int i = 0; i < sz; i++)
    {
        print(storage[i]);
    }
}

string getCategoryNameById(int ID, DynamicArray<ExpenseCategory> &storage)
{
    int idx;
    if (search(ID, storage, idx))
    {
        return storage[idx].get_name();
    }
    return "Item not found.";
}