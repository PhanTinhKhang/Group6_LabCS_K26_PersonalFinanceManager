#include "../include/DynamicArray.h"
#include "../include/IncomeSource.h"
#include <string>

IncomeSource::IncomeSource(int ID, string NAME)
{
    this->ID = ID;
    this->NAME = NAME;
}

int IncomeSource::get_id() const
{
    return (this->ID);
}

string IncomeSource::get_name() const
{
    return this->NAME;
}

void IncomeSource::edit_IncomeSource(string newNAME)
{
    this->NAME = newNAME;
}

void set_name(IncomeSource &item)
{
    string nName;
    getline(cin, nName);
    item.edit_IncomeSource(nName);
}

bool search(int ID, DynamicArray<IncomeSource> &storage, int &idx)
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

void print(const IncomeSource &item, ostream &fout)
{
    fout << item.get_id() << ": " << item.get_name() << '\n';
    return;
}

bool add(DynamicArray<IncomeSource> &storage, IncomeSource item)
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

bool del(DynamicArray<IncomeSource> &storage, IncomeSource item)
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

void view(DynamicArray<IncomeSource> &storage, ostream &fout)
{
    int sz = storage.getSize();
    if(sz == 0){
        fout << "Income source list is empty. \n";
        return;
    }
    for (int i = 0; i < sz; i++)
    {
        print(storage[i], fout);
    }
    return;
}

string getSourceNameById(int ID, DynamicArray<IncomeSource> &storage)
{
    int idx;
    if (search(ID, storage, idx))
    {
        return storage[idx].get_name();
    }
    return (string)("Item not found.");
}