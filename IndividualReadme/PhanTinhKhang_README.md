# Personal Contribution & Weekly Log

- **Student Name:** Phan Tịnh Khang
- **Role:** Team Leader (Core Architecture, Logic Implementer & Project Coordination)
- **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS
- **Project:** Personal Finance Manager (C++)
- **Repository:** Group6_PersonalFinanceManager

---

## Weekly Activity Logs

### Week 1: Project Initialization, Custom Dynamic Array & Encapsulated Date Class

- **Branch:** `main`

#### Tasks Completed:

- [x] **Project Infrastructure & Setup (Task 1):**
  - Initialized Git repository and configured standard C++ `.gitignore`.
  - Established clean directory hierarchy: `include/`, `src/`, `test/`, `assets/`, `IndividualReadme/`.
  - Added all team members as repository collaborators and set up Git workflow rules.
- [x] **Custom Generic Dynamic Array (Task 2):**
  - Implemented raw pointer template `DynamicArray<T>` (strictly non-STL, manual memory management):
    - Dynamic resizing with doubling capacity factor ($2\times$).
    - Insertion routines: `push(element)`, `insert(element, index)`.
    - Removal routines: `pop()`, `pop(index)`.
    - Accessors & memory maintenance: `operator[](index)`, `getSize()`, `clear()`, `print()`.
  - Built unit test suite in `test/test_dynamicarray01.cpp` to validate memory allocations, edge cases, and reallocations.
- [x] **Core Date Model & Date Arithmetic (Task 3):**
  - Designed encapsulated `Date` class (`private` members: `day`, `month`, `year`) ensuring class invariants against invalid states.
  - Implemented static calendar utilities: `isLeapYear(y)`, `getDaysInMonth(m, y)`.
  - Built robust date validation and safe mutation layer: `setDate(d, m, y)`, `isValid()`.
  - Implemented chronological comparison and range filtering: `isBefore()`, `isEqual()`, `isInRange()` for statistical analysis.
  - Added recurring transaction helper: `isSameMonth(const Date& other)` utilizing `const &` passing.
  - Developed stream parsers and string formatters: `toString()`, `fromString()`, and stream extraction `operator<<`.
  - Built comprehensive test suite (`test/test_date_full.cpp`) covering leap years, edge-case invalid dates, formatting, and seamless integration with `DynamicArray<Date>`.

#### Key Commits / PRs:

- `Init repository tree and .gitignore`
- `Implement DynamicArray template with raw pointers`
- `Add basic unit tests for dynamic array`
- `Implement encapsulated Date class with validation and range logic`
- `Optimize isSameMonth to take const Date reference`
- `Add comprehensive test suite for Date and DynamicArray integration`

---

### Week 2: Wallet Management (CRUD), Header Integration Fixes & Main Entrypoint Setup

- **Branch:** `main`

#### Tasks Completed:

- [x] **Wallet Management CRUD & Balance Aggregation (Task 10):**
  - Declared and implemented `findWalletIndexById()`, `createWallet()`, `editWalletName()`, `deleteWallet()`, `viewWallets()`, `getTotalBalance()`, and `getWalletNameById()` in `include/Wallet.h` and `src/Wallet.cpp`.
  - Enforced input validation on wallet creation and renaming (non-empty ID/name, non-negative initial balance, duplicate ID prevention).
  - Moved `printWallet()` definition from `include/Wallet.h` into `src/Wallet.cpp` to prevent multiple-definition linker errors.
  - Built unit test suite in `test/test_wallet_crud.cpp` verifying empty state, validation rules, renaming, deletion, and total balance calculation.
- [x] **Cross-Module Integration & Header Fixes:**
  - Implemented deep-copy Copy Constructor and Copy Assignment `operator=` in `include/DynamicArray.h` (Rule of Three) to prevent shallow-copy double-free crashes.
  - Resolved `enum TransactionType` redeclaration by removing the duplicate definition in `include/RecurringTransaction.h` and including `Transaction.h`.
  - Separated `printTrans()` definition from `include/Transaction.h` into `src/Transaction.cpp` to eliminate multiple-definition linker errors.
  - Fixed case-sensitive `#include "DynamicArray.h"` across headers and sources (`include/ExpenseCategory.h`, `include/IncomeSource.h`, `include/RecurringTransaction.h`, `src/ExpenseCategory.cpp`, `src/IncomeSource.cpp`, `src/TransactionList.cpp`).
  - Updated `src/main.cpp` to include all core module headers and declare the main `DynamicArray` containers (`wallets`, `categories`, `sources`, `transactions`, `recurringList`).

#### Key Commits / PRs:

- `feat: implement Wallet CRUD management and getTotalBalance`
- `fix: resolve header linker errors, DynamicArray Rule of Three, and include casing`
- `docs: update main entrypoint containers and personal weekly log`

---

### Week 3: Cross-Module ID Standardization, Date Migration & Integration Fixes

- **Branch:** `main`

#### Tasks Completed:

- [x] **System-Wide `int` ID Standardization:**
  - Unified all entity identifiers (`Wallet`, `Transaction`, `RecurringTransaction`, `IncomeRecord`, `ExpenseRecord`) to `int` to match `ExpenseCategory` and `IncomeSource` and simplify upcoming binary persistence.
  - Updated `include/Wallet.h` and `src/Wallet.cpp` (`WALLET_ID`, getters/setters, `CheckID()`, and all CRUD functions) to use positive integer IDs.
  - Updated `include/Transaction.h`, `include/RecurringTransaction.h`, `include/IncomeRecord.h`, `src/IncomeRecord.cpp`, `include/ExpenseRecord.h`, and `src/ExpenseRecord.cpp` to use `int` IDs, removing redundant string-to-int parsing loops and `-Wsign-compare` warnings.
  - Updated `src/Dashboard.cpp` (`std::to_string(wallets[i].get_ID())`) and `test/test_WALLET_TRANSACTION.cpp` to align with `int` IDs.
- [x] **`Date` Class Migration & Input/Header Hygiene:**
  - Migrated `Transaction::DATE` in `include/Transaction.h` from `std::string` to `Date`, updating `src/IncomeRecord.cpp`, `src/ExpenseRecord.cpp`, `src/RecurringManager.cpp`, and `test/test_WALLET_TRANSACTION.cpp` accordingly.
  - Fixed input buffer handling (`std::cin.ignore(10000, '\n')`) in `src/IncomeRecord.cpp` and `src/ExpenseRecord.cpp`.
  - Removed duplicate `#include "Transaction.h"` in `include/RecurringTransaction.h` and standardized `#include "DynamicArray.h"` casing in `include/Dashboard.h`, `include/IncomeRecord.h`, and `include/ExpenseRecord.h`.

#### Key Commits / PRs:

- `refactor: standardize all entity IDs to int and migrate Transaction date to Date class`
- `docs: update personal weekly log for Week 3`

---

## Cumulative Contributions & File Registry

| File / Component                                              | Type              | Responsibility / Description                                                  |
| :------------------------------------------------------------ | :---------------- | :---------------------------------------------------------------------------- |
| `include/DynamicArray.h`                                      | Header (Template) | Custom generic dynamic array engine (non-STL) with Rule of Three              |
| `test/test_dynamicarray01.cpp`                                | Test Source       | Unit tests for dynamic array operations                                       |
| `include/Date.h`                                              | Header            | Declaration of encapsulated `Date` class & utilities                          |
| `src/Date.cpp`                                                | Source            | Implementation of calendar logic, validation, comparisons, and parsing        |
| `test/test_date_full.cpp`                                     | Test Source       | Complete test suite for `Date` and `DynamicArray<Date>` integration           |
| `include/Wallet.h`                                            | Header            | Wallet entity (`int` ID) & CRUD function declarations                         |
| `src/Wallet.cpp`                                              | Source            | Implementation of Wallet CRUD, `getTotalBalance()`, and table formatting      |
| `test/test_wallet_crud.cpp`                                   | Test Source       | Unit tests for Wallet CRUD operations and edge cases                          |
| `include/Transaction.h` & `src/Transaction.cpp`               | Header / Source   | Transaction entity (`int` IDs, `Date` type) and `printTrans()` implementation |
| `include/RecurringTransaction.h` & `src/RecurringManager.cpp` | Header / Source   | Standardized `int` IDs and `Date` integration for recurring transactions      |
| `include/IncomeRecord.h` & `src/IncomeRecord.cpp`             | Header / Source   | Refactored `int` ID validation, `Date` integration, and buffer handling       |
| `include/ExpenseRecord.h` & `src/ExpenseRecord.cpp`           | Header / Source   | Refactored `int` ID validation, `Date` integration, and buffer handling       |
| `include/Dashboard.h` & `src/Dashboard.cpp`                   | Header / Source   | Fixed include casing and `int` ID string formatting for CLI table             |
| `src/main.cpp`                                                | Source            | Main entrypoint integrating all headers and primary `DynamicArray` containers |
| `IndividualReadme/PhanTinhKhang_README.md`                    | Documentation     | Personal weekly log and milestone tracker                                     |
