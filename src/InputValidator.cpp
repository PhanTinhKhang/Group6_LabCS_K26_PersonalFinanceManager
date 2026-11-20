#include "../include/InputValidator.h"
#include "../include/Date.h"
#include <cmath>

std::string trimInput(const std::string& input) {
    size_t a = input.find_first_not_of(" \t\n\r");
    if(a == std::string::npos) return "";
    size_t b = input.find_last_not_of(" \t\n\r");
    return input.substr(a,b-a+1);
}
static bool isDig(char c) {
    return c >= '0' && c <= '9'; 
}
static bool isAlp(char c) { 
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}
static int monthFromName(const std::string& name) {
    static const char* names[12] = {"jan","feb","mar","apr","may","jun",
                                    "jul","aug","sep","oct","nov","dec"};
    if (name.size() != 3) return 0;
    std::string low;
    for (char c : name) low += (c >= 'A' && c <= 'Z') ? char(c - 'A' + 'a') : c;
    for (int i = 0; i < 12; i++)
        if (low == names[i]) return i + 1;
    return 0;
}
bool parseDate(const std::string& input, Date &output) {
    std::string s = trimInput(input);
    std::string token[3];
    char seps[2] = {0, 0};
    int t = 0;
    size_t i = 0, n = s.size();
    while(i<n) {
        if(isDig(s[i]) || isAlp(s[i])) {
            if(t > 2) return false;
            bool digits = isDig(s[i]);
            size_t j = i;
            while(j < n && (digits ? isDig(s[j]) : isAlp(s[j]))) j++;
            token[t++] = s.substr(i,j-i);
            i = j;
        } else {
            char sep = ' ';
            int symbols = 0;
            size_t start = i;
            while (i < n && (s[i] == ' ' || s[i] == '\t' || s[i] == '/' || s[i] == '-')) {
                if (s[i] == '/' || s[i] == '-') {
                     sep = s[i]; 
                     symbols++;
                    }
                i++;
            }
            if (i == start) return false;        
            if (symbols > 1) return false;       
            if (t == 0 || t > 2) return false;   
            seps[t - 1] = sep;
        }
    }
    if (t != 3 || seps[0] == 0 || seps[1] == 0 || seps[0] != seps[1]) return false;   


    for (char c : token[0]) {
        if (!isDig(c)) return false;
    }
    for (char c : token[2]) {
       if (!isDig(c)) return false; 
    } 
    if (token[0].size() > 2 || token[2].size() != 4) return false;

    //chuyển month -> số
    int m; 
    if (isDig(token[1][0])) {
        if (token[1].size() > 2) return false;
        m = std::stoi(token[1]);
    } else {
        m = monthFromName(token[1]);
        if (m == 0) return false;
    }

    Date tmp;
    if (!tmp.setDate(std::stoi(token[0]), m, std::stoi(token[2]))) return false;
    output = tmp;                  
    return true;
}
bool parseInt(const std::string& input, int& output) {
    std::string new_input = trimInput(input);
    if(new_input.empty() || new_input.size() > 9) return false;
    for(char c : new_input) {
        if( c < '0' || c > '9') return false;
    }
    if(std::stoi(new_input) <= 0) return false;
    output = std::stoi(new_input);
    return true;
}
bool parseDouble(const std::string& input, double& output) { 
    std::string new_input = trimInput(input);
    if(new_input.empty()) return false;
    size_t point = new_input.find_first_of(".,");
    std::string IntPart, DecPart;

    if(point == std::string::npos) {
        IntPart = new_input;
        DecPart = "";
    } else {
        IntPart = new_input.substr(0,point);
        DecPart = new_input.substr(point+1);
    }
    if(IntPart.empty() && DecPart.empty()) return false;
    for(char c : IntPart) {
        if(c < '0' || c > '9') return false;
    }
    for(char c : DecPart) {
        if(c < '0' || c > '9') return false;
    }
    if(IntPart.size() > 9 || DecPart.size() > 15) return false;
    double v = IntPart.empty() ? 0.0 : std::stod(IntPart);
    if (!DecPart.empty())
        v += std::stod(DecPart) / std::pow(10, (int)DecPart.size());
    
    double rounded = std::round(v * 1000) / 1000; 
    if (rounded <= 0) return false; 
    output = rounded;
    return true;
}


bool existWallet(DynamicArray<Wallet>& wallet, int id) {
    return findWalletIndexById(id, wallet) != -1;
}
bool existIncome(DynamicArray<IncomeSource>& source, int id) {
    int idx;
    return search(id, source, idx);
}

bool existExpense(DynamicArray<ExpenseCategory>& category, int id) {
    int idx;
    return search(id, category, idx);
}

void readDate(const std::string& prompt, Date& out) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (parseDate(line, out)) return;
        std::cout << "Invalid date, try again.\n";
    }
}
void readInt(const std::string& prompt, int& out) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (parseInt(line, out)) return;
        std::cout << "Invalid ID, try again.\n";
    }
}
void readDouble(const std::string& prompt, double& out) {
    std::string line;
    while (true) {
        std::cout << prompt;
        std::getline(std::cin, line);
        if (parseDouble(line, out)) return;
        std::cout << "Invalid amount, try again.\n";
    }
}