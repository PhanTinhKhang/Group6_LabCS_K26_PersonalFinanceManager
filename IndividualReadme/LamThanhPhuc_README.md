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

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description | 
| ----- | ----- | ----- | 
| `include/RecurringTransaction.h` | Header | Declaration and inline definition of `RecurringTransaction` class & `TransactionType` enum | 
| `test/test_recurringtransaction(getter,setter).cpp` | Test Source | Verifying getters and setters using `assert` | 
| `src/TransactionList.cpp` | Source | Printing formatted transactions list with ID-to-Name mapping  | 
| `test/test_transactionlist.cpp` | Test Source | Testing new features | 
| `IndividualReadme/Weekly_Log.md` | Documentation | Personal weekly progress log and milestone tracker | 
