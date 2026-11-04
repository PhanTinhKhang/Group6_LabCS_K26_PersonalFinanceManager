#include <bits/stdc++.h>
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
using namespace std;

int main()
{
    ExpenseCategory expense1(1234, "FOOD");
    print(expense1);
    expense1.edit_Category("ENTERTAINMENT");
    print(expense1);
    cout << expense1.get_id() << " " << expense1.get_name() << '\n';

    IncomeSource income1(5678, "Salary");
    print(income1);
    cout << income1.get_id() << " " << income1.get_name() << '\n';
    income1.edit_IncomeSource("Bonus");
    print(income1);

    return 0;
}

/*
Expect output:
1234 FOOD
1234 ENTERTAINMENT
1234 ENTERTAINMENT
5678 Salary
5678 Salary
5678 Bonus
*/