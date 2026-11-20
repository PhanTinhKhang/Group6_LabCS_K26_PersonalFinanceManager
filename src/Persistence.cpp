#include "../include/Persistence.h"
#include <fstream>

static const std::string DATA_MAGIC = "PFM_BIN_V1";

static void writeString(std::ofstream& out, const std::string& str) {
    size_t len = str.size();
    out.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len > 0) {
        out.write(str.data(), static_cast<std::streamsize>(len));
    }
}

static bool readString(std::ifstream& in, std::string& str) {
    size_t len = 0;
    if (!in.read(reinterpret_cast<char*>(&len), sizeof(len))) {
        return false;
    }
    if (len > 1000000) {
        return false;
    }
    str.resize(len);
    if (len > 0 && !in.read(&str[0], static_cast<std::streamsize>(len))) {
        return false;
    }
    return true;
}

static void writeDate(std::ofstream& out, const Date& dt) {
    int d = dt.getDay();
    int m = dt.getMonth();
    int y = dt.getYear();
    out.write(reinterpret_cast<const char*>(&d), sizeof(d));
    out.write(reinterpret_cast<const char*>(&m), sizeof(m));
    out.write(reinterpret_cast<const char*>(&y), sizeof(y));
}

static bool readDateBin(std::ifstream& in, Date& dt) {
    int d = 1, m = 1, y = 2026;
    if (!in.read(reinterpret_cast<char*>(&d), sizeof(d))) return false;
    if (!in.read(reinterpret_cast<char*>(&m), sizeof(m))) return false;
    if (!in.read(reinterpret_cast<char*>(&y), sizeof(y))) return false;
    dt.setDate(d, m, y);
    return true;
}

bool saveDataToFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    std::ofstream out(filename.c_str(), std::ios::binary);
    if (!out.is_open()) {
        return false;
    }

    writeString(out, DATA_MAGIC);

    int wCount = wallets.getSize();
    out.write(reinterpret_cast<const char*>(&wCount), sizeof(wCount));
    for (int i = 0; i < wCount; ++i) {
        int id = wallets[i].get_ID();
        double bal = wallets[i].get_BALANCE();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, wallets[i].get_NAME());
        out.write(reinterpret_cast<const char*>(&bal), sizeof(bal));
    }

    int cCount = categories.getSize();
    out.write(reinterpret_cast<const char*>(&cCount), sizeof(cCount));
    for (int i = 0; i < cCount; ++i) {
        int id = categories[i].get_id();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, categories[i].get_name());
    }

    int sCount = sources.getSize();
    out.write(reinterpret_cast<const char*>(&sCount), sizeof(sCount));
    for (int i = 0; i < sCount; ++i) {
        int id = sources[i].get_id();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        writeString(out, sources[i].get_name());
    }

    int tCount = transactions.getSize();
    out.write(reinterpret_cast<const char*>(&tCount), sizeof(tCount));
    for (int i = 0; i < tCount; ++i) {
        int typeInt = (transactions[i].get_TYPE() == Income) ? 1 : 2;
        int srcCatId = transactions[i].get_SOURCE_OR_CATEGORY_ID();
        double amt = transactions[i].get_AMOUNT();
        int wId = transactions[i].get_WALLET();
        out.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));
        writeDate(out, transactions[i].get_DATE());
        out.write(reinterpret_cast<const char*>(&srcCatId), sizeof(srcCatId));
        out.write(reinterpret_cast<const char*>(&amt), sizeof(amt));
        out.write(reinterpret_cast<const char*>(&wId), sizeof(wId));
        writeString(out, transactions[i].get_DESC());
    }

    int rCount = recurringList.getSize();
    out.write(reinterpret_cast<const char*>(&rCount), sizeof(rCount));
    for (int i = 0; i < rCount; ++i) {
        int id = recurringList[i].getId();
        int typeInt = (recurringList[i].getType() == Income) ? 1 : 2;
        int srcCatId = recurringList[i].getSourceOrCatId();
        int wId = recurringList[i].getWalletId();
        double amt = recurringList[i].getAmount();
        out.write(reinterpret_cast<const char*>(&id), sizeof(id));
        out.write(reinterpret_cast<const char*>(&typeInt), sizeof(typeInt));
        out.write(reinterpret_cast<const char*>(&srcCatId), sizeof(srcCatId));
        out.write(reinterpret_cast<const char*>(&wId), sizeof(wId));
        out.write(reinterpret_cast<const char*>(&amt), sizeof(amt));
        writeDate(out, recurringList[i].getStartDate());
        writeDate(out, recurringList[i].getEndDate());
        writeString(out, recurringList[i].getLastAppliedMonth());
        writeString(out, recurringList[i].getDescription());
    }

    return true;
}

bool loadDataFromFile(
    const std::string& filename,
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources,
    DynamicArray<Transaction>& transactions,
    DynamicArray<RecurringTransaction>& recurringList
) {
    std::ifstream in(filename.c_str(), std::ios::binary);
    if (!in.is_open()) {
        return false;
    }

    std::string magic;
    if (!readString(in, magic) || magic != DATA_MAGIC) {
        return false;
    }

    DynamicArray<Wallet> newWallets;
    DynamicArray<ExpenseCategory> newCategories;
    DynamicArray<IncomeSource> newSources;
    DynamicArray<Transaction> newTransactions;
    DynamicArray<RecurringTransaction> newRecurring;

    int wCount = 0;
    if (!in.read(reinterpret_cast<char*>(&wCount), sizeof(wCount)) || wCount < 0) return false;
    for (int i = 0; i < wCount; ++i) {
        int id = 0;
        double bal = 0.0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        if (!in.read(reinterpret_cast<char*>(&bal), sizeof(bal))) return false;
        newWallets.push(Wallet(id, name, bal));
    }

    int cCount = 0;
    if (!in.read(reinterpret_cast<char*>(&cCount), sizeof(cCount)) || cCount < 0) return false;
    for (int i = 0; i < cCount; ++i) {
        int id = 0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        newCategories.push(ExpenseCategory(id, name));
    }

    int sCount = 0;
    if (!in.read(reinterpret_cast<char*>(&sCount), sizeof(sCount)) || sCount < 0) return false;
    for (int i = 0; i < sCount; ++i) {
        int id = 0;
        std::string name;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!readString(in, name)) return false;
        newSources.push(IncomeSource(id, name));
    }

    int tCount = 0;
    if (!in.read(reinterpret_cast<char*>(&tCount), sizeof(tCount)) || tCount < 0) return false;
    for (int i = 0; i < tCount; ++i) {
        int typeInt = 1, srcCatId = 0, wId = 0;
        double amt = 0.0;
        Date dt;
        std::string desc;
        if (!in.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt))) return false;
        if (!readDateBin(in, dt)) return false;
        if (!in.read(reinterpret_cast<char*>(&srcCatId), sizeof(srcCatId))) return false;
        if (!in.read(reinterpret_cast<char*>(&amt), sizeof(amt))) return false;
        if (!in.read(reinterpret_cast<char*>(&wId), sizeof(wId))) return false;
        if (!readString(in, desc)) return false;
        TransactionType tType = (typeInt == 1) ? Income : Expense;
        newTransactions.push(Transaction(tType, dt, srcCatId, amt, wId, desc));
    }

    int rCount = 0;
    if (!in.read(reinterpret_cast<char*>(&rCount), sizeof(rCount)) || rCount < 0) return false;
    for (int i = 0; i < rCount; ++i) {
        int id = 0, typeInt = 2, srcCatId = 0, wId = 0;
        double amt = 0.0;
        Date startDt, endDt;
        std::string lastApplied, desc;
        if (!in.read(reinterpret_cast<char*>(&id), sizeof(id))) return false;
        if (!in.read(reinterpret_cast<char*>(&typeInt), sizeof(typeInt))) return false;
        if (!in.read(reinterpret_cast<char*>(&srcCatId), sizeof(srcCatId))) return false;
        if (!in.read(reinterpret_cast<char*>(&wId), sizeof(wId))) return false;
        if (!in.read(reinterpret_cast<char*>(&amt), sizeof(amt))) return false;
        if (!readDateBin(in, startDt)) return false;
        if (!readDateBin(in, endDt)) return false;
        if (!readString(in, lastApplied)) return false;
        if (!readString(in, desc)) return false;
        TransactionType tType = (typeInt == 1) ? Income : Expense;
        newRecurring.push(RecurringTransaction(id, tType, srcCatId, wId, amt, startDt, endDt, lastApplied, desc));
    }

    wallets = newWallets;
    categories = newCategories;
    sources = newSources;
    transactions = newTransactions;
    recurringList = newRecurring;
    return true;
}

void seedDefaultData(
    DynamicArray<Wallet>& wallets,
    DynamicArray<ExpenseCategory>& categories,
    DynamicArray<IncomeSource>& sources
) {
    createWallet(wallets, 1, "Physical Cash", 3450000.0);
    createWallet(wallets, 2, "Techcombank Debit", 18500000.0);
    createWallet(wallets, 3, "MoMo E-Wallet", 1500000.0);

    categories.push(ExpenseCategory(1, "Food & Dining"));
    categories.push(ExpenseCategory(2, "Transportation"));
    categories.push(ExpenseCategory(3, "House Rent"));
    categories.push(ExpenseCategory(4, "Utilities"));
    categories.push(ExpenseCategory(5, "Shopping"));

    sources.push(IncomeSource(1, "Monthly Salary"));
    sources.push(IncomeSource(2, "Project Bonus"));
    sources.push(IncomeSource(3, "Freelance"));
}
