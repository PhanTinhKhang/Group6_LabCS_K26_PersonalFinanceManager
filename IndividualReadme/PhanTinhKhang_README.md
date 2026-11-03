# Personal Contribution & Weekly Log

* **Student Name:** Phan Tịnh Khang
* **Role:** Team Leader (Core Architecture, Logic Implementer & Project Coordination)
* **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS
* **Project:** Personal Finance Manager (C++)
* **Repository:** Group6_PersonalFinanceManager

---

## Weekly Activity Logs

### Week 1: Project Initialization & Custom Dynamic Array
* **Branch:** `main`

#### Tasks Completed:
- [x] Initialized Git repository and configured standard C++ `.gitignore`.
- [x] Established project directory hierarchy: `include/`, `src/`, `test/`, `assets/`, `IndividualReadme/`.
- [x] Added all team members as repository collaborators.
- [x] Implemented raw pointer template `DynamicArray<T>` (strictly non-STL):
  - Dynamic resizing with doubling factor ($2\times$).
  - Insertion routines: `push(element)`, `insert(element, index)`.
  - Removal routines: `pop()`, `pop(index)`.
  - Accessors & memory maintenance: `operator[](index)`, `getSize()`, `clear()`, `print()`.
- [x] Built unit test suite in `test/test_dynamicarray01.cpp` to validate memory allocations, edge cases, and reallocations.

#### Key Commits / PRs:
* `Init repository tree and .gitignore`
* `Implement DynamicArray template with raw pointers`
* `Add basic unit tests for dynamic array`

---

## Cumulative Contributions & File Registry

| File / Component | Type | Responsibility / Description |
| :--- | :--- | :--- |
| `include/DynamicArray.h` | Header (Template) | Custom generic dynamic array engine |
| `test/test_dynamicarray01.cpp` | Test Source | Unit tests for dynamic array operations |
| `IndividualReadme/PhanTinhKhang_README.md` | Documentation | Personal weekly log and milestone tracker |