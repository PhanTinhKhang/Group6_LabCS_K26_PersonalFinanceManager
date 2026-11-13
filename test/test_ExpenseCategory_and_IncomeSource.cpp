#include <bits/stdc++.h>
#include "../include/ExpenseCategory.h"
#include "../include/IncomeSource.h"
#include "../include/dynamicArray.h"
using namespace std;

/*  COMPILE INTRODUCTION:
    - cd to: "D:\Introduction to CS\GROUP_PROJECT\Group6_LabCS_K26_PersonalFinanceManager-1\test"
    - run: g++ test_ExpenseCategory_and_IncomeSource.cpp ../src/ExpenseCategory.cpp ../src/IncomeSource.cpp -o test
*/

int main()
{
    /*  WEEK1_TEST

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
    */

    //   WEEK2_TEST
    cout << "----------EXPENSE CATEGORY TEST----------\n";
    ExpenseCategory Expense1{123, "FOOD"}, Expense2{234, "ENTERTAINMENT"}, Expense3{345, "FUEL"}, Expense4{1, "BILLS"};
    DynamicArray<ExpenseCategory> Expense_list;
    cout << "___ADD FUNCTION TEST___\n";
    add(Expense_list, Expense1);
    add(Expense_list, Expense3);
    add(Expense_list, Expense2);
    cout << "___VIEW LIST TEST___\n";
    view(Expense_list);
    cout << "___GET NAME BY ID___ \n";
    cout << getCategoryNameById(234, Expense_list) << '\n';
    cout << getCategoryNameById(12, Expense_list) << '\n';
    cout << "___DELETE TEST AND VIEW AGAIN___\n";
    del(Expense_list, Expense1);
    del(Expense_list, Expense4);
    view(Expense_list);

    cout << "----------INCOME SOURCE TEST----------\n";
    IncomeSource Source1{111, "Salary"}, Source2{222, "Mom"}, Source3{333, "Dad"}, Source4{14, "SGDD"};
    DynamicArray<IncomeSource> Source_list;
    cout << "___ADD FUNCTION TEST___\n";
    add(Source_list, Source1);
    add(Source_list, Source2);
    add(Source_list, Source3);
    cout << "___VIEW LIST TEST___\n";
    view(Source_list);
    cout << "___GET NAME BY ID___ \n";
    cout << getSourceNameById(222, Source_list) << '\n';
    cout << getSourceNameById(14, Source_list) << '\n';
    cout << "___DELETE TEST AND VIEW AGAIN___\n";
    del(Source_list, Source1);
    del(Source_list, Source4);
    view(Source_list);

    return 0;
}

/* WEEK 1:
Expect output:
1234 FOOD
1234 ENTERTAINMENT
1234 ENTERTAINMENT
5678 Salary
5678 Salary
5678 Bonus
*/

/*  WEEK 2 _ Expect output:
    ----------EXPENSE CATEGORY TEST----------
    ___ADD FUNCTION TEST___
    Item inserted successfully.
    Item inserted successfully.
    Item inserted successfully.
    ___VIEW LIST TEST___
    123: FOOD
    234: ENTERTAINMENT
    345: FUEL
    ___GET NAME BY ID___
    ENTERTAINMENT
    Item not found.
    ___DELETE TEST AND VIEW AGAIN___
    Item deleted successfully.
    Item not found.
    234: ENTERTAINMENT
    345: FUEL
    ----------INCOME SOURCE TEST----------
    ___ADD FUNCTION TEST___
    Item inserted successfully.
    Item inserted successfully.
    Item inserted successfully.
    ___VIEW LIST TEST___
    111: Salary
    222: Mom
    333: Dad
    ___GET NAME BY ID___
    Mom
    Item not found.
    ___DELETE TEST AND VIEW AGAIN___
    Item deleted successfully.
    Item not found.
    222: Mom
    333: Dad
*/