#include "../include/IncomeRecord.h"
#include <iostream>
#include <string>

void inputIncome(std::string &date, std::string &SourceID, double &Amount,
                 std::string &walletId, std::string &desc) {
    std::cout<<"-------------Income Record-------------\n";
    std::cout<<"Date: "; std::getline(std::cin,date);
    std::cout<<"SourceID: "; std::cin >> SourceID;
    std::cout<<"Amount: "; std::cin >> Amount;
    std::cout<<"WalletID: "; std::cin >> walletId;
    std::cin.ignore();
    std::cout<<"Description: "; std::getline(std::cin,desc);
}

bool addIncome(DynamicArray<Wallet>& wallets,DynamicArray<IncomeSource>& sources,
               DynamicArray<Transaction>& transactions, const std::string& date, const std::string& sourceId,
               double Amount, const std::string& walletId,
               const std::string& desc){
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


    int Id = -1;
    for(int i=0; i < wallets.getSize(); i++) {
        if(wallets[i].CheckID(walletId)) {
            Id = i;
            break;
        }
    }
    if(Id == -1) return false;

    if(sourceId.empty() || (int)sourceId.size() > 9) return false;
    for(int i = 0; i < sourceId.size();i++) {
        if(sourceId[i] < '0' || sourceId[i] > '9') {
            return false;
        }
    }
    bool FindSource = false;
    for(int i=0;i < sources.getSize();i++) {
        if(sources[i].get_id() == std::stoi(sourceId)) {
            FindSource = true;
            break;
        }
    }
    if(!FindSource) return false;

    wallets[Id].Deposit(Amount);
    transactions.push(Transaction(Income, date, sourceId, Amount, walletId, desc));
    return true;
}
