# TASK COMPLETION REPORT

**Course:** Introduction to Programming  
**Project:** Personal Finance Manager (C++)  
**Assigned Task:** Define `RecurringTransaction` Entity & Create Unit Test Suite  
**Assignee:** Lam Thanh Phuc  

---

## I. SUMMARY OF COMPLETED WORK

In this project, I was responsible for implementing and testing the **`RecurringTransaction`** module. This module is essential for handling recurring financial entries (e.g., monthly rent, salary, internet subscriptions) that automatically recur over a specified timeframe.

### Key Contributions:
1. **Designed the `RecurringTransaction` Data Model**: Built an encapsulated class structure conforming to standard object-oriented programming (OOP) principles.
2. **Implemented Immutability & Data Safeguards**: Restricted direct setters to dynamic attributes (`lastAppliedMonth`, `amount`) while protecting identity and structural properties via constructor initialization.
3. **Developed Automated Unit Tests**: Created a standalone unit testing framework using `<cassert>` to verify entity initialization and property updates.

---

## II. INTERACTED & CREATED FILES

| File Path | Description |
| :--- | :--- |
| `include/RecurringTransaction.h` | Class definition for `RecurringTransaction`. |
| `test_recurringtransaction(getter,setter).cpp` | Testing getter and setter functions.  |

---

## III. TECHNICAL SPECIFICATIONS (`RecurringTransaction.h`)

The `RecurringTransaction` class incorporates the following member attributes:

* **`id` (`int`)**: Primary identifier for the transaction record.
* **`type` (`TransactionType`)**: Enum type (`Income = 1`, `Expense = 2`) ensuring semantic clarity instead of raw numerical constants.
* **`sourceOrCatId` (`std::string`)**: References the specific `SourceID` (for income) or `CategoryID` (for expenses).
* **`walletId` (`std::string`)**: Identifies the destination/source `WalletID`.
* **`amount` (`double`)**: The monetary value of the transaction.
* **`startDate` (`std::string`)**: Effective start date of the recurring rule.
* **`endDate` (`std::string`)**: Expiration date (optional/empty string if ongoing).
* **`lastAppliedMonth` (`std::string`)**: Stores the most recent processed month (e.g., `"10/2026"`). Prevents duplicate applications when launching the app multiple times in the same monthly cycle.
* **`description` (`std::string`)**: Notes associated with the transaction.

### Encapsulation & Mutability Policy:
* **Constructors**: All structural fields (`id`, `type`, `sourceOrCatId`, `walletId`, `startDate`, `endDate`, `description`) are initialized via constructor and kept immutable to protect financial audit integrity.
* **Setters Provided**: Only `setLastAppliedMonth()` and `setAmount()` are exposed, allowing necessary state updates during execution.


---

## V. COMPLIANCE WITH PROJECT RULES

* **No STL Containers**: Implemented without reliance on `std::vector` or `std::map`.
* **Modular Header-Only Definition**: Kept inside `Recurring.h` to minimize merge conflicts across team branches on Git.
* **Standard OOP Encapsulation**: Data members remain `private`, exposing only essential getters/setters.

---

**Date of Completion:** November 04, 2026  