# Personal Contribution & Weekly Log

- **Student name:** Trương Vĩnh Thọ
- **Role:** Team member
- **Course:** Introduction to Computer Science (CS160) - APCS - HCMUS
- **Project:** Personal Finance Manager (C++)
- **Repository:** Group6_PersonalFinancialManager

---

## Weekly Actovity Logs

### Week 1: Define IncomeSource and ExpenseCategory

- **Branch** `main`

#### Tasks Completed:

- [x] Define IncomeSource.h
- [x] Define ExpenseCategory.h

#### Key Commits:

- `Create and add basic function for ExpenseCategory.h and IncomeSource.h`

---

## Cumulative Contributions & File Registry

| File / Component                             | Type          | Description                               |
| :------------------------------------------- | :------------ | :---------------------------------------- |
| `include/ExpenseCategory.h`                  | Header        | declare function for ExpenseCategory      |
| `include/IncomeSource.h`                     | Header        | declare function for IncomeSource         |
| `test/test_ExpenseCategory_and_IncomeSource` | Test Source   | Test writen function/class                |
| `IndivisualReadme/TruongVinhTho_README.md`   | Documentation | Personal weekly log and milestone tracker |

### Week 2: Declare IncomeSource, ExpenseCategory functions

- **Branch** `main`

#### Tasks Completed:

- [x] Define IncomeSource.cpp, including add, del, getSourceNameById, search, view, set_name, print.
- [x] Define ExpenseCategory.cpp, including add, del, getCategoryNameById, search, view, set_name, print.

#### Key Commits:

- `Declare add, del,... functions in ExpenseCategory.cpp and IncomeSource.cpp`

---

## Cumulative Contributions & File Registry

| File / Component                             | Type          | Description                                       |
| :------------------------------------------- | :------------ | :------------------------------------------------ |
| `include/ExpenseCategory.h`                  | Header        | add declaration for functions in ExpenseCategory  |
| `include/IncomeSource.h`                     | Header        | add declaration for function in IncomeSource      |
| `src/IncomeSource.cpp`                       | Source        | define add, del,... functions for IncomeSource    |
| `src/ExpenseCategory.cpp`                    | Source        | define add, del,... functions for ExpenseCategory |
| `test/test_ExpenseCategory_and_IncomeSource` | Test Source   | Test new function                                 |
| `IndivisualReadme/TruongVinhTho_README.md`   | Documentation | Personal weekly log and milestone tracker         |

### Week 3: Declare load and save function.

- **Branch:** `main`

#### Tasks Completed:

- [x] **Declare save function:** use to write all data about wallet, income source, expense category, transaction, recurring transaction to a binary file for later use, mostly used when closing app.

- [x] **Declare load function:** use to read from the binary file(same file as save function) to get data for running, mostly used when re-opening app.

#### Key Commits:

- `Declare save and load function`
- `Adding test source and storing address for save and load function, fix some bug in FileStorage.cpp`

---

## Cumulative Contributions & File Registry

| File / Component                           | Type          | Description                                                              |
| :----------------------------------------- | :------------ | :----------------------------------------------------------------------- |
| `test/Storage.bin`                         | Binary file   | temporary storing address used to build up save and load function        |
| `include/FileStorage.h`                    | Header        | declare function for reading and writing user information to binary file |
| `src/FileStorage.cpp`                      | Source        | define function for reading and writing user information to binary file  |
| `test/test_filestorage.cpp`                | Test Source   | test save and load function declared in include/FileStorage.h            |
| `IndivisualReadme/TruongVinhTho_README.md` | Documentation | Personal weekly log and milestone tracker                                |

### Week 4: Improve declared function

- **Brach:** `main`

#### Work done:

- [x] **IncomeSource and ExpenseCategory:** Separate declaration and implementation for ExpenseCategory and IncomeSource's functions.

- [x] **FileStorage:** Replace C-style(char*) cast with C++ reinterpret_cast<char*> in FileStorage.cpp

#### Key Commits:

    - Separate class implementations and casting style in FileStorage.cpp

---

## Cumulative Contributions & File Registry

| File / Component                           | Type          | Description                                                   |
| :----------------------------------------- | :------------ | :------------------------------------------------------------ |
| `include/IncomeSource.h`                   | Header        | moving implementation to 'src/IncomeSource.cpp'               |
| `src/FileStorage.cpp`                      | Source        | replace char* with reinterpret_cast<char*>                    |
| `test/test_filestorage.cpp`                | Test Source   | test save and load function declared in include/FileStorage.h |
| `IndivisualReadme/TruongVinhTho_README.md` | Documentation | Personal weekly log and milestone tracker                     |
