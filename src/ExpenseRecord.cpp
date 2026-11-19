#include "../include/ExpenseRecord.h"

void inputExpense(std::string &date, int &CateId, double &Amount, 
    int &walletId,std::string &desc){
        std::cout <<"----------Expense Record----------\n";
        std::cout <<"Date: "; std::getline(std::cin, date);
        std::cout <<"CategoryId: "; std::cin >> CateId;
        std::cout <<"Amount: "; std::cin  >> Amount;
        std::cout <<"WalletID: "; std::cin >> walletId;
        std::cin.ignore(10000, '\n');
        std::cout <<"Description: "; std::getline(std::cin,desc);
}

bool addExpense(DynamicArray<Wallet> &wallets, DynamicArray<ExpenseCategory> &expenses,
    DynamicArray<Transaction> &transaction, const std::string &date, 
    const int &ExpenseId,double Amount, const int &walletId,const std::string &desc){
    if(date.size() != 10 || date[2] != '/' || date[5] != '/') return false;
    for(int i=0; i < 10;i++) {
        if(i==2 || i==5) continue;
        if(date[i] < '0' || date[i] > '9') return false;
    }
    Date dt;
    int d,m,y;
    d = std::stoi(date.substr(0,2));
    m = std::stoi(date.substr(3,2));
    y = std::stoi(date.substr(6,4));
    if(!dt.setDate(d,m,y)) return false;

    if(Amount <= 0) return false;


    int id = -1;
    for(int i = 0; i < wallets.getSize();i++) {
        if(wallets[i].CheckID(walletId)) {
            id = i;
            break;      
        }
    }
    if(id == -1) return false;

    if (ExpenseId <= 0) return false;
    bool FindExpenseSource = false;
    for (int i = 0; i < expenses.getSize(); i++) {
        if (expenses[i].get_id() == ExpenseId) {
            FindExpenseSource = true;
            break;
        }
    }
    if (!FindExpenseSource) return false;

    if(!wallets[id].Withdrawal(Amount)) return false;
    transaction.push(Transaction(Expense, dt, ExpenseId, Amount, walletId,desc));
    return true;
}