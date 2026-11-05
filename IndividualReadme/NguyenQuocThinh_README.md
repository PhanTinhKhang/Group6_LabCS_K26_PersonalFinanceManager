# TASK COMPLETION REPORT & WEEKLY LOG

**Course:** Introduction to Programming / Introduction to Computer Science (CS160) - APCS  
**Faculty:** Department of Software Engineering - FIT - VNU-HCMUS  
**Project:** Personal Finance Manager (C++)  
**Assigned Task:** UI / Planning - Dashboard CLI Mockup & Git Workflow Rules  
**Assignee:** Nguyen Quoc Thinh (Student ID: 25125066)  
**Role:** UI / Planning Specialist  
**Group:** Group 6  

---

## I. SUMMARY OF COMPLETED WORK

In accordance with the official project requirements (*Final Project Personal Finance Manager* by the Software Engineering Department - FIT - HCMUS), I was responsible for and have successfully completed the **UI / Planning** module:

### 1. CLI Dashboard ASCII Design & User Flow (CLI Dashboard Mockup)
* **Main Dashboard Screen:**
  - Integrated the **Total Balance** summary aggregating all wallet holdings.
  - Formatted individual **Wallet Balances** with account ID, display name, currency formatted to two decimal places, and status.
  - Implemented the **System Startup Log** to handle automated processing and notifications for monthly recurring transactions upon application launch.
  - Built an intuitive numeric navigation menu (options `[1]` through `[7]` and `[0]` to exit).
* **Functional Sub-screens:**
  - **Transaction Entry (Income & Expense):** Followed the core requirement of strictly separating logic storage (`SourceID`, `CategoryID`, `WalletID`) from user-facing display names.
  - **Master Data Management:** Full CRUD operations (Add, Edit, Delete) for Expense Categories, Income Sources, and Wallets.
  - **Recurring Transactions Management:** Monthly recurring rules, mandatory start dates, optional end dates, and cycle duplicate prevention.
  - **Comprehensive Financial Reports:** Detailed layouts for all 5 report categories:
    1. Time-based Income / Expense / Net Balance (From Date A to Date B).
    2. Time & Wallet-based specific expense breakdowns.
    3. Multi-year overview with total income, expense, and net balance across selected years.
    4. Annual income breakdown by income source.
    5. Annual expense breakdown by expense category with ASCII percentage bars.
* **Automated Navigation Flow:**
  - Formalized the Mermaid State Diagram ensuring that upon completing any user action, the system informs the user and **automatically navigates back to the Dashboard**.

### 2. Git Workflow Standards & Conflict Prevention Guide
* **Branching Strategy:** Main branch protection; isolated development on `feature/<feature_name>` branches.
* **Conflict Prevention in C++:** Leveraged modular object-oriented programming (one class per header/source pair) and configured a comprehensive `.gitignore` excluding all compiler binaries and temporary IDE files.
* **Grading Policy Alert:** Highlighted the course regulation requiring individual GitHub commits from each member to avoid receiving a score of zero.
* **Standard 5-Step Daily Routine:** Pull `main` $\rightarrow$ Branch $\rightarrow$ Atomic Commits $\rightarrow$ Merge/Rebase `main` $\rightarrow$ Push & Pull Request (PR).
* **Conflict Resolution Guide & Quick Cheat Sheet.**

---

## II. INTERACTED & CREATED FILES

| File Path | Type | Description |
| :--- | :--- | :--- |
| `docs/DASHBOARD_CLI_DESIGN.md` | Design Specification | Text-based ASCII wireframes for the main dashboard, 5 report screens, I/O specifications, and navigation flow diagram. |
| `docs/GIT_WORKFLOW_GUIDE.md` | Team Guide | Comprehensive Git branching strategy, conflict-free commit/push workflow, and grading policy alerts. |
| `IndividualReadme/NguyenQuocThinh_README.md` | Documentation | Personal task completion report and activity log for Nguyen Quoc Thinh. |
| `README.md` | Project Documentation | Updated repository index with direct links to the new design and Git workflow guides. |

---

## III. COMPLIANCE WITH PROJECT RULES

* **Documentation & Codebase Integrity:** In strict accordance with the user instruction *(please do not add any note into the code)*, no comments or notes were added into the C++ source files (`src/`, `include/`, `test/`). All design models and workflow guidelines are cleanly decoupled in `docs/` and `IndividualReadme/`.
* **Standard Folder Hierarchy:** Fully adheres to the project hierarchy recommended on page 6 of the project specification.

---

**Date of Completion:** November 05, 2026  
**Assignee:** Nguyen Quoc Thinh (Student ID: 25125066)
