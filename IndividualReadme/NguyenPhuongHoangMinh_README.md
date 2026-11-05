# TASK COMPLETION REPORT

**Course:** Introduction to Programming  
**Project:** Personal Finance Manager (C++)  
**Assigned Task:** Define `Wallet` and `Transaction` (Income & Expense) Entities & Create Test Program  
**Assignee:** Nguyen Phuong Hoang Minh 

---

## I. SUMMARY OF COMPLETED WORK

I was responsible for implementing the **`Wallet`** and **`Transaction`** modules. `Wallet` represents an account that holds money (cash, bank account, ...). `Transaction` represents a single income or expense entry applied to a wallet.

### Key Contributions:
1. **Designed the `Wallet` class**: Stores ID, name and balance, with getters/setters and basic operations (`Deposit`, `Withdrawal`, `CheckID`).
2. **Designed the `Transaction` class**: Covers both Income and Expense using the `TransactionType` enum (`Income = 1`, `Expense = 2`).
3. **Developed a test program**: Verifies object creation, printing, and applying transactions to a wallet.

---

## II. INTERACTED & CREATED FILES

| File Path | Description |
| :--- | :--- |
| `include/Wallet.h` | Class definition for `Wallet`. |
| `include/Transaction.h` | Class definition for `Transaction` and the `TransactionType` enum. |
| `test/test_WALLET_TRANSACTION.cpp` | Test `main` for both classes. |

---

## III. TECHNICAL SPECIFICATIONS

### `Wallet`
* **`WALLET_ID` (`std::string`)**: Unique identifier of the wallet.
* **`NAME` (`std::string`)**: Display name of the wallet.
* **`BALANCE` (`double`)**: Current balance.
* **Operations**: `Deposit(amount)` adds money; `Withdrawal(amount)` subtracts money and returns `false` if the balance is insufficient; `CheckID(id)` compares IDs.
* **Helper**: `printWallet(const Wallet&)` prints a wallet (2 decimal places).

### `Transaction`
* **`TYPE` (`TransactionType`)**: Income or Expense.
* **`DATE` (`std::string`)**: Date of the transaction.
* **`SOURCE_OR_CATEGORY_ID` (`std::string`)**: SourceID for income, CategoryID for expense.
* **`AMOUNT` (`double`)**: Monetary value.
* **`WALLET_ID` (`std::string`)**: The wallet the transaction belongs to.
* **`DESCRIPTION` (`std::string`)**: Notes.
* **Helper**: `printTrans(const Transaction&)` prints a transaction (2 decimal places).

### Design notes:
* Data members are `private`; access is only through getters/setters.
* Both classes provide a default constructor and a full-parameter constructor.
* Parameters use `const std::string&` to avoid unnecessary copies.
* `TransactionType` is defined once in `Transaction.h`; `RecurringTransaction.h` should include this header instead of redefining the enum.

---

## IV. TESTING

* The test program creates wallets and transactions, prints them, then applies each transaction to the matching wallet (Income -> `Deposit`, Expense -> `Withdrawal`).
* Insufficient-balance case is checked through the return value of `Withdrawal`.
* Build and run:

---

## V. COMPLIANCE WITH PROJECT RULES

* **No STL Containers**: Only `std::string` is used.
* **Header-Only Definition**: All functions are short, so they are defined inside the header; free functions are marked `inline` to avoid multiple-definition errors.
* **Standard OOP Encapsulation**: Private data members, public getters/setters.
* **Git**: Work is done on branch `feature/Wallet_Transaction` and merged through a pull request.

---

## VI. FURTHER FEATURES

* **Transfer between wallets**: Add a `transfer(Wallet& from, Wallet& to, double amount)` operation that withdraws from one wallet and deposits into another, only if the source has enough balance.
* **Input validation**: Reject negative `AMOUNT`, empty `WALLET_ID`, or invalid `DATE` when creating a `Transaction`.
* **Savings wallet with interest**: Add a `SavingsWallet` (derived from `Wallet`) with an annual `interestRate`. A method `applyInterest(int months)` adds interest to the balance.

---

**Date of Completion:** November 05, 2026