# Personal Contribution & Weekly Log

* **Student Name:** Nguyễn Phương Hoàng Minh
* **Role:** Member (Wallet, Transaction, Income/Expense Record & Input Validation)
* **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS
* **Project:** Personal Finance Manager (C++)
* **Repository:** Group6_LabCS_K26_PersonalFinanceManager

---

## Weekly Activity Logs

### Week 1: Wallet & Transaction Entities
* **Branch:** `feature/Wallet_Transaction`

#### Tasks Completed:
- [x] **Wallet Entity:**
  - Defined `Wallet` (ID, name, balance) with `private` members, default and full constructors, getters and setters.
  - Implemented balance operations: `Deposit(amount)`, `Withdrawal(amount)` (returns `false` if the balance is insufficient), and `CheckID(id)`.
- [x] **Transaction Entity (Income & Expense):**
  - Defined `Transaction` (type, date, source/category ID, amount, wallet ID, description) with the `TransactionType` enum (`Income = 1`, `Expense = 2`).
  - Provided default and full constructors, getters and setters.
- [x] **Testing:**
  - Built `test/test_WALLET_TRANSACTION.cpp` to verify object creation, printing, and applying transactions to a wallet.

---

### Week 2: Income Record & Expense Record
* **Branch:** `feature/Income_Expense_Records`

#### Tasks Completed:
- [x] **Income Record:**
  - `inputIncome()` collects Date, Source ID, Amount, Wallet ID, Description.
  - `addIncome()` validates input, deposits into the wallet, and saves the `Transaction`.
- [x] **Expense Record:**
  - `inputExpense()` and `addExpense()` follow the same flow using Category ID and `Withdrawal()`.
  - A transaction is rejected and not saved when the balance is insufficient.
- [x] **Data Consistency:**
  - All checks run first; the wallet balance changes only after every check passes.

#### Key Commits / PRs:
* `add Income and Expense Record` (PR #6)

---

### Week 3: Input Validator & Record Integration
* **Branch:** `feature/InputValidator`

#### Tasks Completed:
- [x] **Input Parsing (string to value, returns `false` on invalid input):**
  - `parseDate()`: accepts `dd/mm/yyyy`, `dd-mm-yyyy`, `dd mm yyyy` and month names (`13-Sep-2026`); both separators must be the same type; extra spaces around separators are allowed; invalid dates (e.g. 31/02, year outside 1900-2100) are rejected.
  - `parseInt()`: positive integer IDs only (digits only, max 9 digits).
  - `parseDouble()`: accepts `.` or `,` as decimal mark, rounds to 3 decimals, rejects letters, negatives and zero.
  - `trimInput()`: removes leading/trailing whitespace.
  - Output parameters are assigned only when the input is valid.
- [x] **Re-prompt Helpers:**
  - `readDate()`, `readInt()`, `readDouble()` read a line with `getline`, parse it, and ask again on invalid input.
- [x] **ID Existence Checks:**
  - `existWallet()`, `existIncome()`, `existExpense()` reuse the existing search functions.
- [x] **Record Integration (Update Date):**
  - Updated `IncomeRecord` and `ExpenseRecord` to take a `Date` object and the validator; removed hand-written date checks and `cin >>`.
  - The team-wide migration of IDs to `int` and dates to the `Date` class was done in commit `standardlize all IDs to int and date to Date class`.
- [x] **Testing:**
  - `test/test_validator.cpp`: 60 cases pass (`parseInt`, `parseDouble`, `parseDate` valid/invalid formats, `existWallet`/`existIncome`/`existExpense`).
  - `test/test_income_expense.cpp`: 12 cases pass (valid income/expense, non-positive amount, missing wallet/source/category, insufficient balance).

#### Key Commits / PRs:
* `feat: add InputValidator, apply to Income/Expense records, update README`

---

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description |
| :--- | :--- | :--- |
| `include/Wallet.h` | Header | Wallet entity (ID, name, balance, deposit/withdrawal) |
| `include/Transaction.h` | Header | Transaction entity and `TransactionType` enum |
| `src/Transaction.cpp` | Source | `printTrans()` (moved out of header to avoid multiple definitions) |
| `include/IncomeRecord.h` | Header | Income record function declarations |
| `src/IncomeRecord.cpp` | Source | Income input and processing |
| `include/ExpenseRecord.h` | Header | Expense record function declarations |
| `src/ExpenseRecord.cpp` | Source | Expense input and processing |
| `include/InputValidator.h` | Header | Parsing, re-prompt and ID existence check declarations |
| `src/InputValidator.cpp` | Source | Implementation of `parseDate/Int/Double`, `read...`, `exist...` |
| `test/test_WALLET_TRANSACTION.cpp` | Test Source | Tests for Wallet and Transaction |
| `test/test_income_expense.cpp` | Test Source | Tests for Income/Expense records |
| `test/test_validator.cpp` | Test Source | Tests for InputValidator |
| `IndividualReadme/NguyenPhuongHoangMinh_README.md` | Documentation | Personal weekly log and milestone tracker |

---

### Week 4: Wallet Transfer
* **Branch:** `feature/WalletTransfer`

#### Tasks Completed:
- [x] **Transfer Logic:**
  - Implemented `transferBetweenWallets(wallets, fromId, toId, amount)` using the existing `Withdrawal()` and `Deposit()`.
  - Returns a `TransferResult` code (`TRANSFER_SUCCEEDED`, `TRANSFER_INVALID_AMOUNT`, `TRANSFER_SAME_WALLET`, `TRANSFER_WALLET_NOT_FOUND`, `TRANSFER_INSUFFICIENT_FUNDS`) instead of printing, so the UI layer decides the message.
  - Balances are changed only after every check passes, so a rejected transfer never alters any wallet.
- [x] **Transfer UI:**
  - Implemented `handleWalletTransfer(wallets)`: reads source wallet ID, destination wallet ID and amount with the validator (`readInt`, `readDouble`), calls the transfer function, and prints a `[SUCCESS]` / `[ERROR]` message matching the result code.
- [x] **Testing:**
  - Added `testTransfer()` to `test/test_wallet_crud.cpp`, covering a valid transfer, transferring the exact balance, insufficient funds, amount ≤ 0, same wallet, missing source/destination wallet, unchanged balances after rejections, and total balance preserved.

---

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description |
| :--- | :--- | :--- |
| `include/Wallet.h` | Header | Wallet entity (ID, name, balance, deposit/withdrawal) and `TransferResult` / `transferBetweenWallets` declarations |
| `src/Wallet.cpp` | Source | `transferBetweenWallets()` added alongside the wallet CRUD |
| `include/Transaction.h` | Header | Transaction entity and `TransactionType` enum |
| `src/Transaction.cpp` | Source | `printTrans()` (moved out of header to avoid multiple definitions) |
| `include/IncomeRecord.h` | Header | Income record function declarations |
| `src/IncomeRecord.cpp` | Source | Income input and processing |
| `include/ExpenseRecord.h` | Header | Expense record function declarations |
| `src/ExpenseRecord.cpp` | Source | Expense input and processing |
| `include/InputValidator.h` | Header | Parsing, re-prompt and ID existence check declarations |
| `src/InputValidator.cpp` | Source | Implementation of `parseDate/Int/Double`, `read...`, `exist...` |
| `include/WalletTransferUI.h` | Header | Declaration of `handleWalletTransfer()` |
| `src/WalletTransferUI.cpp` | Source | Wallet transfer input and result messages |
| `test/test_WALLET_TRANSACTION.cpp` | Test Source | Tests for Wallet and Transaction |
| `test/test_income_expense.cpp` | Test Source | Tests for Income/Expense records |
| `test/test_validator.cpp` | Test Source | Tests for InputValidator |
| `test/test_wallet_crud.cpp` | Test Source | Wallet CRUD tests, extended with wallet transfer tests |
| `IndividualReadme/NguyenPhuongHoangMinh_README.md` | Documentation | Personal weekly log and milestone tracker |

---
**Update date: 27/11/2026**