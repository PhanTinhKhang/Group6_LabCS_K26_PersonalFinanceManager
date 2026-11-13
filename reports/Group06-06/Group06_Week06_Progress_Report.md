# UNIVERSITY OF SCIENCE, VNU-HCM
## FACULTY OF INFORMATION TECHNOLOGY
---
# WEEKLY PROGRESS REPORT - WEEK 06 (LAB SPRINT 02)
### PROJECT: PERSONAL FINANCE MANAGER (C++)
**Course:** CS160 - Introduction to Computer Science (APCS K26)

> **Sprint Metadata:**
> * **Group:** Group 06 (APCS K26)
> * **Team Leader:** Phan Tinh Khang (Student ID: 26125034)
> * **Team Members:** Nguyen Phuong Hoang Minh (26125051), Lam Thanh Phuc (26125059), Truong Vinh Tho (26125079), Nguyen Quoc Thinh (25125066)
> * **GitHub Repository:** https://github.com/PhanTinhKhang/Group6_LabCS_K26_PersonalFinanceManager
> * **Sprint Period:** Lab Week 02 / Semester Week 06 (November 07, 2026 - November 13, 2026)

---

## 1. PROJECT OVERVIEW & WEEK 06 OBJECTIVES

The Personal Finance Manager project aims to engineer an extensible, console-based financial management suite implemented strictly in C++ using custom manual memory management (Non-STL constraint). The software allows users to manage financial accounts (wallets), classify income and expenses with explicit ID-to-Name separation, process recurring monthly transactions, compute real-time analytical statements, and maintain long-term session persistence via file storage.

During Lab Week 02 (Semester Week 06), the team focused on building core application operations and presentation:
1. Engineered the interactive CLI Dashboard and navigation menu with real-time balance aggregation and robust keyboard input capture.
2. Implemented CRUD management operations on dynamic arrays of `Wallet` instances.
3. Implemented master data manipulation functions in `ExpenseCategory.cpp` and `IncomeSource.cpp`.
4. Implemented transaction recording routines (Income and Expense mutations) with account balance checks.
5. Enhanced `DynamicArray<T>` with copy semantics (deep copy constructor).
6. Implemented tabular visualization for recurring transactions with ID-to-Name mapping.
7. Resolved multi-translation-unit ODR linker errors by standardizing header declarations.

---

## 2. WORK DIVISION & MEMBER CONTRIBUTIONS

| Member & ID | Role / Area | Key Tasks & Deliverables | Status |
| :--- | :--- | :--- | :---: |
| **Phan Tinh Khang**<br>ID: 26125034 | Team Leader, Core Architect | • Added submission guidelines (`docs/submitRule.txt`) and comprehensive Date tests (`test/test_date_full.cpp`).<br>• Implemented copy constructor in `DynamicArray<T>` ensuring safe deep copy semantics on reallocation/assignment.<br>• Developed Wallet CRUD operations in `src/Wallet.cpp` (create, edit, delete, view, balance summation) and `test/test_wallet_crud.cpp`.<br>• Initialized core dynamic array instances in `src/main.cpp` and coordinated team PR reviews/merges. | **100%** |
| **Nguyen Phuong Hoang Minh**<br>ID: 26125051 | Core Logic & Transactions | • Implemented Income and Expense recording logic in `src/Transaction.cpp`.<br>• Developed income source management functions and tests.<br>• Fixed ODR multiple-definition linker collisions across `Wallet.h`, `Transaction.h`, and `IncomeSource.h` headers.<br>• Completed Pull Request #6 (`feature/Income_Expense_Records`). | **100%** |
| **Lam Thanh Phuc**<br>ID: 26125059 | Recurring Logic Specialist | • Engineered recurring transactions table printing in `src/TransactionList.cpp`.<br>• Implemented static dictionary mappings resolving Category/Source IDs and Wallet IDs to descriptive display names.<br>• Developed `test/test_transactionlist.cpp` verifying table alignment and format.<br>• Completed Pull Request #4 (`feature/RecurringTransaction`). | **100%** |
| **Truong Vinh Tho**<br>ID: 26125079 | Master Data Specialist | • Implemented master data CRUD functions (`add`, `del`, `edit`, `view`) in `src/ExpenseCategory.cpp` and `src/IncomeSource.cpp`.<br>• Expanded `test/test_ExpenseCategory_and_IncomeSource.cpp` validating item insertion, lookup, and deletion routines. | **100%** |
| **Nguyen Quoc Thinh**<br>ID: 25125066 | UI & CLI Specialist | • Engineered main CLI Dashboard screen in `include/Dashboard.h` and `src/Dashboard.cpp`.<br>• Implemented aggregate total balance calculation and custom currency formatting with thousands separators (`xx,xxx,xxx.00 VND`).<br>• Rendered pixel-perfect 88-column ASCII wallet balances table and numeric navigation menu (`[1..7]` and `[0]`).<br>• Built robust input capture (`promptMenuChoice`) with stream error clearing preventing buffer overflow or infinite loops.<br>• Developed automated unit test suite `test/test_dashboard.cpp`; authored Pull Request #5 (`feature/Dashboard_CLI`). | **100%** |

---

## 3. TECHNICAL SPECIFICATIONS & ARCHITECTURAL HIGHLIGHTS

### 3.1. Main CLI Dashboard Engine & Navigation Architecture (`Dashboard.h`, `Dashboard.cpp`)
* **Aggregate Balance Computation:** The `calculateTotalBalance()` routine traverses `DynamicArray<Wallet>&` in $O(N)$ to compute the total liquid net worth.
* **Locale-Independent Currency Formatting:** The custom `formatCurrency(double amount)` routine formats numbers with comma thousands separators and two fixed decimal places (e.g., `28,450,000.00 VND`) without relying on heavy or locale-dependent standard streams.
* **Clean ASCII Terminal Aesthetics:** Employs strict 88-column text borders, fixed-width headers, and padded numeric fields ensuring uniform layout across Windows PowerShell, CMD, and Unix terminals.
* **Fault-Tolerant Key Capture:** The `promptMenuChoice()` dispatcher handles non-numeric inputs, spaces, and newline artifacts via `std::cin.clear()` and buffer discarding, completely preventing infinite loops on invalid input.

### 3.2. Wallet Management & CRUD Processing (`Wallet.cpp`)
* **Validation Safeguards:** `createWallet()` rejects empty identifiers/names, negative starting balances, and duplicate Wallet IDs.
* **In-Place Updates & Deletion:** `editWalletName()` updates names by unique ID; `deleteWallet()` removes the account while maintaining array packing via `pop(index)`.
* **Balance Extraction:** Helper `getTotalBalance()` and name resolver `getWalletNameById()` provide fast lookups.

### 3.3. Transaction Record Processing & Account Mutation (`Transaction.cpp`)
* **Record Processing:** Matches target Wallet ID within the wallet array. When processing an Expense, it invokes `Withdrawal(amount)` with insufficient funds checking; for Income, it calls `Deposit(amount)`.
* **Audit Preservation:** Transaction records remain immutable once recorded, ensuring financial audit fidelity.

### 3.4. Recurring Transactions Tabular Display & Identity Mapping (`TransactionList.cpp`)
* **ID-to-Name Resolution:** Employs static lookup dictionaries mapping abstract codes (`C01`, `S01`, `W01`) to human-friendly labels (`Internet & Utilities`, `Salary / Main Job`, `Techcombank Main`).
* **Aligned Output:** Formats IDs, cycle dates, amounts, and execution statuses into clean columnar tables.

### 3.5. Copy Semantics & Deep Copying in `DynamicArray<T>`
* **Deep Memory Duplication:** `DynamicArray(const DynamicArray& other)` allocates a new contiguous Heap buffer of identical capacity and copies elements individually, fully upholding RAII and preventing double-free runtime errors.

### 3.6. Linker Optimization & Header Modularization
* To resolve One Definition Rule (ODR) collisions during multi-file compilation, free functions defined in headers (`printWallet`, `printTrans`) were given `inline` specifiers or moved into dedicated translation units (`src/Wallet.cpp`, `src/Transaction.cpp`), allowing clean unified builds.

---

## 4. INTEGRATED TESTING & VERIFICATION

| Test Suite | Test Scope & Edge Cases Covered | Result |
| :--- | :--- | :---: |
| `test/test_dashboard.cpp` | Validates `formatCurrency()` across zero, positive, negative, and fractional values; asserts `calculateTotalBalance()` across empty and multi-account arrays; renders ASCII table. | **PASSED (100%)** |
| `test/test_wallet_crud.cpp` | Validates wallet creation, name modification, deletion, empty ID/name rejection, duplicate ID prevention, and negative initial balance handling. | **PASSED (100%)** |
| `test/test_transactionlist.cpp` | Validates recurring transaction table rendering, ID-to-Name resolution, and column alignment. | **PASSED (100%)** |
| `test/test_date_full.cpp` | Validates leap year edge cases, range checks (`isInRange`), string parsing (`DD/MM/YYYY`), and integration inside `DynamicArray<Date>`. | **PASSED (100%)** |
| `test/test_ExpenseCategory_and_IncomeSource.cpp` | Validates category and source insertion, ID lookup, deletion, and empty container safety. | **PASSED (100%)** |
| `test/test_WALLET_TRANSACTION.cpp` | Validates deposit/withdrawal balance updates and insufficient balance error flags. | **PASSED (100%)** |
| **Full Unified Project Compilation** | Unified build compiling all source files (`Date.cpp`, `ExpenseCategory.cpp`, `IncomeSource.cpp`, `TransactionList.cpp`, `Wallet.cpp`, `Transaction.cpp`, `Dashboard.cpp`, `main.cpp`). | **PASSED (100%)** |

---

## 5. GITHUB FILE REGISTRY & ARTIFACT REPOSITORY

| Repository Path | Artifact Type | Architectural Role & Description |
| :--- | :--- | :--- |
| `include/Dashboard.h` | C++ Header | `MenuAction` enum and Dashboard function prototypes |
| `src/Dashboard.cpp` | C++ Source | Dashboard rendering, currency formatting, and input capture |
| `test/test_dashboard.cpp` | C++ Test Source | Automated unit tests for Dashboard operations |
| `include/Wallet.h` | C++ Header | `Wallet` entity class definition and management prototypes |
| `src/Wallet.cpp` | C++ Source | Wallet CRUD logic, balance summation, and name lookups |
| `test/test_wallet_crud.cpp` | C++ Test Source | Automated unit tests for Wallet CRUD operations |
| `src/Transaction.cpp` | C++ Source | Income and Expense transaction execution logic |
| `src/TransactionList.cpp` | C++ Source | Recurring transaction table display with identity mapping |
| `test/test_transactionlist.cpp` | C++ Test Source | Unit tests for recurring transaction table rendering |
| `include/dynamicArray.h` | C++ Header (Template) | Added deep copy constructor to `DynamicArray<T>` |
| `src/main.cpp` | C++ Entry Point | Initialized core entity arrays for master data integration |
| `docs/submitRule.txt` | Guidelines | Course weekly submission format and packaging rules |
| `.mailmap` | Git Configuration | Unified author name and email mapping across members |
| `IndividualReadme/*.md` | Documentation | Updated individual weekly activity reports for all members |
| `Git Commit Log Total.md` | Audit Document | Full sanitized commit log from project inception |

---

*Ho Chi Minh City, November 13, 2026*  
**ON BEHALF OF GROUP 06 - TEAM LEADER**  
**Phan Tinh Khang**
