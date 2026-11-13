#include "../include/Transaction.h"
#include <iostream>
#include <iomanip>
// Đưa code qua đây chứ để trong header là bị lỗi trùng khai báo
void printTrans(const Transaction& a) {
    std::cout << std::fixed << std::setprecision(2);
    std::cout << (a.get_TYPE() == Income ? "Income" : "Expense") << " " << a.get_DATE() << " ";
    std::cout << a.get_SOURCE_OR_CATEGORY_ID() << " " << a.get_AMOUNT() << " " << a.get_WALLET() << " " << a.get_DESC() << "\n";
}