# Personal Contribution & Weekly Log

* **Student Name:** Phan Tịnh Khang
* **Role:** Team Leader (Core Architecture, Logic Implementer & Project Coordination)
* **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS
* **Project:** Personal Finance Manager (C++)
* **Repository:** Group6_PersonalFinanceManager

---

## Weekly Activity Logs

### Week 1: Project Initialization, Custom Dynamic Array & Encapsulated Date Class
* **Branch:** `main`

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
* `Init repository tree and .gitignore`
* `Implement DynamicArray template with raw pointers`
* `Add basic unit tests for dynamic array`
* `Implement encapsulated Date class with validation and range logic`
* `Optimize isSameMonth to take const Date reference`
* `Add comprehensive test suite for Date and DynamicArray integration`

---

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description |
| :--- | :--- | :--- |
| `include/DynamicArray.h` | Header (Template) | Custom generic dynamic array engine (non-STL) |
| `test/test_dynamicarray01.cpp` | Test Source | Unit tests for dynamic array operations |
| `include/Date.h` | Header | Declaration of encapsulated `Date` class & utilities |
| `src/Date.cpp` | Source | Implementation of calendar logic, validation, comparisons, and parsing |
| `test/test_date_full.cpp` | Test Source | Complete test suite for `Date` and `DynamicArray<Date>` integration |
| `IndividualReadme/PhanTinhKhang_README.md` | Documentation | Personal weekly log and milestone tracker |