#include "../include/FileStorage.h"
using namespace std;

// Thống nhất sử dụng string, không đổi vị trí declaration các thuộc tính của private trong các class nữa nha.

void write_string(const string &A, long long &addressptr, long long &str_ptr, ofstream &fout)
{
    fout.seekp(addressptr, ios::beg);
    fout.write(reinterpret_cast<char *>(&str_ptr), 8);
    int len = A.length();
    fout.write(reinterpret_cast<char *>(&len), 4);
    fout.seekp(str_ptr, ios::beg);
    fout.write(A.data(), len);
    str_ptr += len;
    addressptr += 12;
    return;
}

void write_date(const Date &A, long long &addressptr, ofstream &fout)
{
    int d = A.getDay();
    int m = A.getMonth();
    int y = A.getYear();

    fout.seekp(addressptr, ios::beg);
    fout.write(reinterpret_cast<const char *>(&d), sizeof(int));
    fout.write(reinterpret_cast<const char *>(&m), sizeof(int));
    fout.write(reinterpret_cast<const char *>(&y), sizeof(int));
    addressptr += 12;
    return;
}

void read_date(long long &address, Date &store, ifstream &fin)
{
    fin.seekg(address, ios::beg);
    fin.read(reinterpret_cast<char *>(&store), 12);
    address += 12;
    return;
}

string read_string(long long &address, ifstream &fin)
{
    long long str_ptr = 0;
    int len = 0;

    fin.seekg(address, ios::beg);
    fin.read(reinterpret_cast<char *>(&str_ptr), 8);
    fin.read(reinterpret_cast<char *>(&len), 4);
    address += 12;

    if (len <= 0)
        return "";

    string result(len, '\0');
    fin.seekg(str_ptr, ios::beg);
    fin.read(&result[0], len);
    return result;
}

bool save(DynamicArray<Wallet> &W, DynamicArray<ExpenseCategory> &Ex,
          DynamicArray<IncomeSource> &So, DynamicArray<Transaction> &Tran,
          DynamicArray<RecurringTransaction> &Recur)
{
    ofstream fout("Storage.bin", ios_base::binary);

    if (!fout)
    {
        cerr << "File open error. \n";
        return false;
    }
    int W_size = W.getSize(), Ex_size = Ex.getSize(), So_size = So.getSize(), Tran_size = Tran.getSize(), Recur_size = Recur.getSize();

    fout.write(reinterpret_cast<char *>(&W_size), sizeof(int));
    fout.write(reinterpret_cast<char *>(&Ex_size), sizeof(int));
    fout.write(reinterpret_cast<char *>(&So_size), sizeof(int));
    fout.write(reinterpret_cast<char *>(&Tran_size), sizeof(int));
    fout.write(reinterpret_cast<char *>(&Recur_size), sizeof(int));

    long long str_pointer = 5 * sizeof(int) +
                            W_size * 24 +
                            Ex_size * 16 +
                            So_size * 16 +
                            Tran_size * 44 +
                            Recur_size * 72;
    long long cur = 5 * sizeof(int);
    for (int i = 0; i < W_size; i++)
    {
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&W[i]), 4);
        cur += 4;

        write_string(W[i].get_NAME(), cur, str_pointer, fout);

        double balance = W[i].get_BALANCE();
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&balance), sizeof(double));
        cur += 8;
    }

    for (int i = 0; i < Ex_size; i++)
    {
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&Ex[i]), 4);
        cur += 4;
        write_string(Ex[i].get_name(), cur, str_pointer, fout);
    }

    for (int i = 0; i < So_size; i++)
    {
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&So[i]), 4);
        cur += 4;
        write_string(So[i].get_name(), cur, str_pointer, fout);
    }

    for (int i = 0; i < Tran_size; i++)
    {
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&Tran[i]), 4);
        cur += 4;

        write_date(Tran[i].get_DATE(), cur, fout);

        int S_or_C_id = Tran[i].get_SOURCE_OR_CATEGORY_ID();
        double amount = Tran[i].get_AMOUNT();
        int walletID = Tran[i].get_WALLET();
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&S_or_C_id), sizeof(int));
        fout.write(reinterpret_cast<char *>(&amount), sizeof(double));
        fout.write(reinterpret_cast<char *>(&walletID), sizeof(int));
        cur += 16;
        write_string(Tran[i].get_DESC(), cur, str_pointer, fout);
    }

    for (int i = 0; i < Recur_size; i++)
    {
        fout.seekp(cur, ios::beg);
        fout.write(reinterpret_cast<char *>(&Recur[i]), 24);
        cur += 24;

        write_date(Recur[i].getStartDate(), cur, fout);
        write_date(Recur[i].getEndDate(), cur, fout);

        write_string(Recur[i].getLastAppliedMonth(), cur, str_pointer, fout);
        write_string(Recur[i].getDescription(), cur, str_pointer, fout);
    }
    bool done = fout.good();
    fout.close();
    return done;
}

bool load(DynamicArray<Wallet> &W, DynamicArray<ExpenseCategory> &Ex,
          DynamicArray<IncomeSource> &So, DynamicArray<Transaction> &Tran,
          DynamicArray<RecurringTransaction> &Recur)
{
    int W_size, Ex_size, So_size, Tran_size, Recur_size;
    ifstream fin("Storage.bin", ios_base::binary);
    if (!fin)
    {
        cerr << "File open error. \n";
        return false;
    }
    fin.read((char *)(&W_size), 4);
    fin.read((char *)(&Ex_size), 4);
    fin.read((char *)(&So_size), 4);
    fin.read((char *)(&Tran_size), 4);
    fin.read((char *)(&Recur_size), 4);
    long long cur = 5 * sizeof(int);

    for (int i = 0; i < W_size; i++)
    { // int string double
        fin.seekg(cur, ios::beg);
        int ID;
        string name;
        double amount;
        fin.read((char *)(&ID), 4);
        cur += 4;
        name = read_string(cur, fin);
        fin.seekg(cur, ios::beg);
        fin.read((char *)(&amount), 8);
        cur += 8;
        W.push(Wallet(ID, name, amount));
    }
    for (int i = 0; i < Ex_size; i++)
    {
        fin.seekg(cur, ios::beg);
        int ID;
        string name;
        fin.read((char *)(&ID), 4);
        cur += 4;
        name = read_string(cur, fin);
        Ex.push(ExpenseCategory(ID, name));
    }
    for (int i = 0; i < So_size; i++)
    {
        fin.seekg(cur, ios::beg);
        int ID;
        string name;
        fin.read((char *)(&ID), 4);
        cur += 4;
        name = read_string(cur, fin);
        So.push(IncomeSource(ID, name));
    }
    for (int i = 0; i < Tran_size; i++)
    { // int date int double int string
        fin.seekg(cur, ios::beg);
        TransactionType num1;
        int num2, num3;
        Date date1;
        double dou1;
        string str1;
        fin.read((char *)(&num1), 4);
        cur += 4;
        read_date(cur, date1, fin);
        fin.seekg(cur, ios::beg);
        fin.read((char *)(&num2), 4);
        fin.read((char *)(&dou1), 8);
        fin.read((char *)(&num3), 4);
        cur += 16;
        str1 = read_string(cur, fin);
        Tran.push(Transaction(num1, date1, num2, dou1, num3, str1));
    }
    for (int i = 0; i < Recur_size; i++)
    { // int tran int int dou date date str str
        fin.seekg(cur, ios::beg);
        int num1, num2, num3;
        TransactionType num4;
        double dou1;
        Date date1, date2;
        string str1, str2;

        fin.read((char *)(&num1), 4);
        fin.read((char *)(&num4), 4);
        fin.read((char *)(&num2), 4);
        fin.read((char *)(&num3), 4);
        fin.read((char *)(&dou1), 8);
        cur += 24;
        read_date(cur, date1, fin);
        read_date(cur, date2, fin);
        str1 = read_string(cur, fin);
        str2 = read_string(cur, fin);
        Recur.push(RecurringTransaction(num1, num4, num2, num3, dou1, date1, date2, str1, str2));
    }
    bool check = fin.good();
    fin.close();
    return check;
}