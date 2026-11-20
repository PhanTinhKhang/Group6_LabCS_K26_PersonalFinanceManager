#include "../include/ExpenseRecord.h"
#include "../include/InputValidator.h"
void inputExpense(Date &date, int &cateId, double &amount, int &walletId, std::string &desc) {
    std::cout << "----------Expense Record----------\n";
    readDate("Date: ", date);
    readInt("CategoryID: ", cateId);
    readDouble("Amount: ", amount);
    readInt("WalletID: ", walletId);
    std::cout << "Description: ";
    std::getline(std::cin, desc);
}
bool addExpense(DynamicArray<Wallet>& wallets, DynamicArray<ExpenseCategory>& categories,
                DynamicArray<Transaction>& transactions, const Date& date, int cateId,
                double amount, int walletId, const std::string& desc) {
    if (amount <= 0) return false;
    if (!existExpense(categories, cateId)) return false;
    int idx = findWalletIndexById(walletId, wallets);
    if (idx == -1) return false;

    if (!wallets[idx].Withdrawal(amount)) return false;   // thiếu tiền thì không lưu
    transactions.push(Transaction(Expense, date, cateId, amount, walletId, desc));
    return true;
}