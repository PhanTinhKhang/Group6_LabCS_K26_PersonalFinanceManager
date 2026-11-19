# Personal Contribution & Weekly Log

* **Student Name:** Lâm Thanh Phúc

* **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS

* **Project:** Personal Finance Manager (C++)

* **Repository:** Group6_LabCS_K26_PersonalFinanceManager

## Weekly Activity Logs

### Week 1: Core Entity Definition (`RecurringTransaction`) & Automated Unit Testing

* **Branch:** `feature/RecurringTransaction`

#### Tasks Completed:

* \[x\] **`RecurringTransaction` Entity Implementation (Task 1):**

  * Designed and implemented the encapsulated `RecurringTransaction` class inside `include/RecurringTransaction.h`.

  * Defined the `TransactionType` enumeration with values `Income = 1` and `Expense = 2`.

  * Applied explicit member initialization lists in both default constructor (`id(0)`, `type(Expense)`, `amount(0.0)`) and parameterized constructor.

  * Enforced financial data integrity through immutable structural getters (`getId`, `getType`, `getSourceOrCatId`, `getWalletId`, `getStartDate`, `getEndDate`, `getDescription`).

  * Exposed restricted mutation methods (`setLastAppliedMonth`, `setAmount`) to allow monthly execution tracking and variable amount updates.

* \[x\] **Unit Testing with `assert` (Task 2):**

  * Built comprehensive tests using `<cassert>` to validate getters and setters.

#### Key Commits / PRs:

* `define RecurringTransaction and testing`

### Week 2: Transaction Table Display & ID-to-Name Mapping

* **Branch:** `feature/RecurringTransaction`

#### Tasks Completed:

* \[x\] **Linear Master Data Lookup (Task 1):**

  * Resolved internal foreign keys (`sourceOrCatId`, `walletId`) into human-readable master data names (`Name`).

  * Implemented safe fallback responses (e.g., `"Unknown Category"`) for unmapped IDs.

* \[x\] **Formatted Console Table Output (Task 2):**

  * Mapped raw transaction entity IDs to translated Names in real-time during table iteration.

  * Formatted headers, column boundaries, and decimal precision for currency alignment.

#### Key Commits / PRs:

* `feat: implement recurring transaction table printing with ID-to-Name mapping`

### Week 3: Automated Recurring Transaction Engine & Lifecycle Processing

* **Branch:** `feature/RecurringTransaction`

#### Tasks Completed:

* \[x\] **Entity Refactoring to Typed `Date` (Task 1):**

  * Migrated `startDate` and `endDate` members in `RecurringTransaction` from raw `std::string` to encapsulated `Date` objects.

  * Updated constructors, getters, and table display formatting in `src/TransactionList.cpp` to call `Date::toString()`.

* \[x\] **Automated Startup Cycle Verification & Execution (Task 2):**

  * Designed and implemented `processRecurringTransactions()` in `src/RecurringManager.cpp`.

  * Integrated system clock resolution via `<ctime>` (`localtime`) to dynamically determine the active monthly cycle (`MM/YYYY`).

  * Enforced cycle idempotency: compared `lastAppliedMonth` against the active cycle string to strictly prevent duplicate transaction posting on repeated app startups.

  * Implemented lifecycle boundary evaluation: checked `StartDate` activation and optional `EndDate` expiration via `hasValidEndDate()`.

  * Managed account balance mutations: credited wallet balance via `Deposit()` for Income; debited balance via `Withdrawal()` for Expense with insufficient funds checks.

  * Synthesized executed transaction records and appended them into `DynamicArray<Transaction>&` while updating `lastAppliedMonth`.

* \[x\] **Automated Lifecycle Unit Testing (Task 3):**

  * Engineered a comprehensive unit test suite in `test/test_recurring_manager.cpp` utilizing `<cassert>`.

  * Validated full execution lifecycle: initial execution, multi-wallet balance synchronization, insufficient balance rejection, active cycle duplicate suppression, and boundary date filtering.

#### Key Commits / PRs:

* `feat: migrate RecurringTransaction to use Date class for start and end dates`
* `feat: implement processRecurringTransactions engine with duplicate prevention and wallet updates`
* `test: add comprehensive automated unit test suite for RecurringManager`
* `fix: fix TransactionList.cpp and testing`

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description | 
| ----- | ----- | ----- | 
| `include/RecurringTransaction.h` | Header | Declaration and inline definition of `RecurringTransaction` class & `processRecurringTransactions` prototype | 
| `test/test_recurringtransaction(getter,setter).cpp` | Test Source | Verifying getters and setters using `assert` | 
| `src/TransactionList.cpp` | Source | Printing formatted transactions list with ID-to-Name mapping  | 
| `test/test_transactionlist.cpp` | Test Source | Testing formatted recurring transactions table printing | 
| `src/RecurringManager.cpp` | Source | Automated recurring transaction processing engine on startup | 
| `test/test_recurring_manager.cpp` | Test Source | Automated unit testing for recurring transactions execution and duplicate prevention | 
| `IndividualReadme/LamThanhPhuc_README.md` | Documentation | Personal weekly progress log and milestone tracker | 
