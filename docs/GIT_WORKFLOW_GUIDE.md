# GIT WORKFLOW & CONFLICT PREVENTION GUIDE
## Project: Personal Finance Manager (C++)
**Course:** Introduction to Programming / Introduction to Computer Science (CS160) - APCS  
**Department:** Department of Software Engineering - FIT - VNU-HCMUS  
**Group:** Group 6  
**Objective:** Establish a standardized Git workflow ensuring all 5 team members collaborate concurrently without merge conflicts or code loss.

---

> [!CAUTION]
> **COURSE GRADING POLICY (SECTION 3, PAGE 7/8 OF OFFICIAL SPECIFICATION):**
> * **Mandatory GitHub Usage:** Every team member must contribute via individual commits using their own personal GitHub account.
> * **Grading Penalty:** *Any team member who fails to commit code to the repository will receive a score of zero.*
> * Ensure your local Git environment is configured with the correct `user.name` and `user.email` matching your GitHub account before making any commits.

---

## I. INITIAL GIT IDENTITY SETUP

Each team member must verify and configure their Git identity in the terminal:

```bash
# Set your full display name (e.g., Nguyen Quoc Thinh)
git config --global user.name "Nguyen Quoc Thinh"

# Set your registered GitHub email address
git config --global user.email "your_email@example.com"

# Verify current configuration
git config user.name
git config user.email
```

---

## II. CORE COLLABORATION RULES

1. **Never Push Directly to `main`:**
   - The `main` branch is the production-ready trunk. Direct pushes to `main` are strictly forbidden. All code merges into `main` exclusively through peer-reviewed **Pull Requests (PR)**.
2. **Dedicated Feature Branches:**
   - Every assignment or task must be developed on an isolated branch prefixed with `feature/` (e.g., `feature/Dashboard_UI`).
3. **Always Synchronize `main` Before Starting Work:**
   - Before writing any code, pull the latest changes from GitHub to ensure your local working copy is up to date.
4. **Enforce Modular OOP Separation:**
   - Keep class definitions and logic segregated into independent header/source pairs:
     - `Wallet.h` / `Wallet.cpp`
     - `Transaction.h` / `Transaction.cpp`
     - `ExpenseCategory.h` / `ExpenseCategory.cpp`
     - `IncomeSource.h` / `IncomeSource.cpp`
     - `RecurringTransaction.h` / `RecurringTransaction.cpp`
     - `DynamicArray.h`
   - By working on separate files, Member A modifying `Wallet` will never interfere with Member B modifying `RecurringTransaction`, eliminating 95% of merge conflicts.
5. **Strict `.gitignore` Maintenance:**
   - Never commit compiler artifacts, binaries, or IDE temporary files (`.exe`, `.o`, `.obj`, `build/`, `.vscode/`, `.vs/`).

---

## III. BRANCH & COMMIT CONVENTIONS

### 1. Branch Naming Standard
Format: `<type>/<feature-name>`

| Branch Type | Prefix | Real Project Examples |
| :--- | :--- | :--- |
| New feature implementation | `feature/` | `feature/Dashboard_UI`<br>`feature/Wallet_Transaction`<br>`feature/RecurringTransaction` |
| Bug fixing | `fix/` | `fix/dynamic_array_leak`<br>`fix/recurring_month_check` |
| Documentation & Testing | `docs/` or `test/` | `docs/git_workflow`<br>`test/unit_test_wallet` |

### 2. Conventional Commit Messages
Commit messages should be concise and descriptive:
- `feat: <description>`: New feature or layout addition (e.g., `feat: implement ASCII layout for CLI dashboard`)
- `fix: <description>`: Bug correction (e.g., `fix: validate positive transaction amount`)
- `test: <description>`: Unit tests addition (e.g., `test: add unit test for recurring transactions`)
- `docs: <description>`: Documentation update (e.g., `docs: update git workflow guide`)
- `refactor: <description>`: Code cleanup without altering business logic

---

## IV. STANDARDIZED 5-STEP CONFLICT-FREE WORKFLOW

Follow this routine for all daily development tasks:

### STEP 1: Update Local `main`
Before starting any new task, ensure your local `main` branch matches the remote:
```bash
# 1. Switch to main
git checkout main

# 2. Pull the latest commits from remote
git pull origin main
```

---

### STEP 2: Create a Dedicated Feature Branch
Branch off the freshly updated `main`:
```bash
# Create and switch to the new feature branch
git checkout -b feature/Dashboard_UI
```

---

### STEP 3: Develop & Make Atomic Commits
Work incrementally and commit frequently with clear, conventional messages:
```bash
# Review modified files
git status

# Stage only files relevant to your assignment
git add docs/DASHBOARD_CLI_DESIGN.md

# Commit your changes
git commit -m "feat: complete text-based ASCII wireframe for CLI dashboard"
```

---

### STEP 4: Synchronize `main` Prior to Pushing (CRITICAL STEP)
Before publishing your branch, integrate any new changes that other teammates might have merged into `main`:
```bash
# 1. Fetch remote tracking branches without altering your work tree
git fetch origin

# 2. Merge latest main into your feature branch
git merge origin/main
```
> [!NOTE]
> Since tasks are isolated across distinct files, Git will cleanly auto-merge (`Already up to date` or `Fast-forward`). Compile and run your tests to verify integration integrity.

---

### STEP 5: Push Branch & Submit Pull Request (PR)
```bash
# Push the branch to GitHub
git push -u origin feature/Dashboard_UI
```
Next:
1. Navigate to the GitHub repository: `https://github.com/PhanTinhKhang/Group6_LabCS_K26_PersonalFinanceManager`
2. Click **"Compare & pull request"**.
3. Provide a clear summary of your completed work.
4. Request a review from the Team Leader or another teammate.
5. Once approved and checks pass, click **Merge pull request**.
6. Switch back to your local repository: `git checkout main && git pull origin main`.

---

## V. STEP-BY-STEP CONFLICT RESOLUTION

If two teammates edit the exact same line in the same file, Git will pause the merge and flag `CONFLICT (content)`:

### 1. Identify Conflict Markers
Open the conflicted file in your editor:
```text
<<<<<<< HEAD (Your local feature branch modifications)
std::cout << "=== Personal Finance Manager v1.0 ===" << std::endl;
=======
std::cout << "========================================" << std::endl;
std::cout << "    PERSONAL FINANCE MANAGER DASHBOARD  " << std::endl;
std::cout << "========================================" << std::endl;
>>>>>>> origin/main (Incoming modifications from main)
```

### 2. Resolution Steps
1. **Communicate:** Coordinate with the author of the conflicting commit to agree on the correct consolidated logic.
2. **Clean up markers:** Delete all conflict markers (`<<<<<<<`, `=======`, `>>>>>>>`) and keep only the correct code.
3. **Compile & Test:** Run the compiler to ensure syntax and unit tests pass cleanly.
4. **Finalize the merge:**
   ```bash
   git add <resolved_file_path>
   git commit -m "fix: resolve merge conflict between feature branch and main"
   ```

### 3. Safe Abort Command
If you make an error while resolving or need to reset to a clean state:
```bash
git merge --abort
```
This safely rolls back your branch to the exact state before the merge attempt.

---

## VI. QUICK GIT CHEAT SHEET

| Operation | Command |
| :--- | :--- |
| Check working directory status | `git status` |
| Compact commit tree history | `git log --oneline --graph` |
| Switch to `main` branch | `git checkout main` |
| Pull latest updates from remote | `git pull origin main` |
| Create and switch to new branch | `git checkout -b <branch_name>` |
| Stage file for commit | `git add <file_path>` |
| Commit staged changes | `git commit -m "<message>"` |
| Fetch latest remote branches | `git fetch origin` |
| Merge latest `main` into active branch | `git merge origin/main` |
| Push branch to remote with upstream tracking | `git push -u origin <branch_name>` |
| Subsequent pushes | `git push` |
| Abort an ongoing merge safely | `git merge --abort` |
