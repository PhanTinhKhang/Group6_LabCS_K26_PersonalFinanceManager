# TASK COMPLETION REPORT & WEEKLY LOG

**Course:** Introduction to Programming / Introduction to Computer Science (CS160) - APCS  
**Faculty:** Department of Software Engineering - FIT - VNU-HCMUS  
**Project:** Personal Finance Manager (C++)  
**Assignee:** Nguyen Quoc Thinh (Student ID: 25125066)  
**Role:** UI / CLI & Planning Specialist  
**Group:** Group 6  

---

## I. SUMMARY OF COMPLETED WORK

In accordance with the official project requirements (*Final Project Personal Finance Manager* by the Software Engineering Department - FIT - HCMUS), I was responsible for and have completed the following milestones:

### Milestone 1 (Week 1): UI Planning & Team Git Collaboration
1. **CLI Dashboard Wireframes & System Navigation Flow (`docs/DASHBOARD_CLI_DESIGN.md`):**
   - Designed complete ASCII wireframes for the main financial dashboard and all functional sub-screens (Income, Expense, Master Data CRUD, Monthly Recurring Automation, 5 Statistical Reports).
   - Formalized the Mermaid State Diagram ensuring automated navigation back to the Dashboard upon operation completion.
2. **Team Git Workflow Guidelines (`docs/GIT_WORKFLOW_GUIDE.md`):**
   - Established the team branching model (`feature/<feature-name>`), 5-step daily routine, C++ modular conflict prevention, and grading policy alerts.

### Milestone 2 (Week 2): Implement Main Screen Dashboard & Navigation Menu
1. **Architecture & Header Specification (`include/Dashboard.h`):**
   - Defined `MenuAction` enum representing all valid navigation commands (`EXIT = 0`, `RECORD_INCOME = 1`, ..., `INVALID = -1`).
   - Declared core interfaces: `formatCurrency()`, `calculateTotalBalance()`, `renderDashboard()`, `promptMenuChoice()`, `clearScreen()`, and `pauseScreen()`.
2. **Core Implementation (`src/Dashboard.cpp`):**
   - **Total Balance Calculation:** Iterates through `DynamicArray<Wallet>` to aggregate net balances across all active accounts.
   - **Currency Formatter:** Custom formatting engine inserting commas for thousand separators and formatting fractional cents to two decimal places (`xx,xxx,xxx.00 VND`) without locale-dependent STL streams.
   - **ASCII Dashboard Table Rendering:** Uses `<iomanip>` to render a pixel-perfect 88-column ASCII table showing Wallet ID, Wallet Name, Balance, and Status.
   - **Navigation Menu & Input Capture:** Displays menu options `[1]` through `[7]` and `[0]` to exit. Safely parses input using `std::cin`, clearing error flags and discarding excess buffer to prevent infinite loops or crashes on non-numeric input.
3. **Automated Unit Testing (`test/test_dashboard.cpp`):**
   - Created test suite validating currency formatting (positive, negative, zero, fractional), balance aggregation across multiple wallets, and rendering output.

---

## II. INTERACTED & CREATED FILES

| File Path | Type | Description |
| :--- | :--- | :--- |
| `include/Dashboard.h` | Header | Declarations for dashboard calculations, table rendering, and `MenuAction` enum. |
| `src/Dashboard.cpp` | Source | Implementation of total balance aggregation, currency formatting, dashboard rendering, and safe input capture. |
| `test/test_dashboard.cpp` | Test Source | Standalone unit test suite verifying balance calculations and formatting. |
| `include/Wallet.h` | Header | Added `inline` specifier to `printWallet` free function to resolve multi-translation-unit ODR linker collisions. |
| `docs/DASHBOARD_CLI_DESIGN.md` | Design Spec | Text-based ASCII wireframes for dashboard and sub-screens. |
| `docs/GIT_WORKFLOW_GUIDE.md` | Team Guide | Git collaboration rules and conflict prevention guidelines. |
| `IndividualReadme/NguyenQuocThinh_README.md` | Documentation | Personal weekly activity log and task completion report. |

---

## III. COMPLIANCE WITH PROJECT RULES

* **Zero Code Annotations / Notes:** In strict adherence to project instructions *(please do not add any note into the code)*, no comments or notes were added inside any C++ source or header files (`src/`, `include/`, `test/`).
* **No STL Containers:** Uses strictly `DynamicArray<Wallet>` and standard `std::string`.
* **Standard Compilation:** Tested and verified with `g++ -std=c++11 -Wall -Wextra` with zero errors and zero warnings.

---

**Last Updated:** November 13, 2026  
**Assignee:** Nguyen Quoc Thinh (Student ID: 25125066)
