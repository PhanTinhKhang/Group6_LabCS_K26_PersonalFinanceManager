#include "../include/Wallet.h"
#include "../include/Transaction.h"
using namespace std;
int main() {
    Wallet a("26125051", "Daily Wallet", 2362008);
    Wallet m;

    m.set_ID("26125037");
    m.set_NAME("Savings/Emergency");
    m.set_BALANCE(5502110);

    printWallet(a);
    cout << a.get_ID() << " " << a.get_NAME() << " " << a.get_BALANCE() << "\n";
    printWallet(m);
    cout << m.get_ID() << " " << m.get_NAME() << " " << m.get_BALANCE() << "\n";


    Transaction p;
    Transaction q(Expense , "Dec 25 2026" , "Gifts" , 3000000 , "26125051" , "Qua giang sinh");

    p.set_TYPE(Income);
    p.set_DATE("Dec 31 2027");
    p.set_SOURCE_OR_CATEGORY_ID("Salary");
    p.set_AMOUNT(15000000);
    p.set_WALLET("0012728010");
    p.set_DESC("Luong cuoi thang");
    
    printTrans(p);
    printTrans(q);
    
    cout << p.get_TYPE() <<" "<<p.get_DATE()<<" "<<p.get_SOURCE_OR_CATEGORY_ID()<<" "<<p.get_AMOUNT()<<" "<<p.get_WALLET()<<" "<<p.get_DESC()<<"\n";
    cout << q.get_TYPE() <<" "<<q.get_DATE()<<" "<<q.get_SOURCE_OR_CATEGORY_ID()<<" "<<q.get_AMOUNT()<<" "<<q.get_WALLET()<<" "<<q.get_DESC()<<"\n";
//
    Transaction a1(Income, "November 5 2026", "Gifts" , 200000, "26125051", " ");
    Transaction a2(Expense, "November 5 2026", "Food" , 70000, "26125051", "Dining out");
    for (const Transaction& t : {a1,a2}) {
        if(!a.CheckID(t.get_WALLET())) continue;
        if(t.get_TYPE() == Income) a.Deposit(t.get_AMOUNT());
        else if(!a.Withdrawal(t.get_AMOUNT())) cout << "Not enough money" << "\n";
    }
    printWallet(a);
    return 0;
}
// 26125051 Daily Wallet 2362008.00
// 26125051 Daily Wallet 2362008.00
// 26125037 Savings/Emergency 5502110.00
// 26125037 Savings/Emergency 5502110.00
// Income Dec 31 2027 Salary 15000000.00 0012728010 Luong cuoi thang
// Expense Dec 25 2026 Gifts 3000000.00 26125051 Qua giang sinh
// 1 Dec 31 2027 Salary 15000000.00 0012728010 Luong cuoi thang
// 2 Dec 25 2026 Gifts 3000000.00 26125051 Qua giang sinh
// 26125051 Daily Wallet 2492008.00