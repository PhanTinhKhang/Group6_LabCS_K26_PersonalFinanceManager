#include "../include/IncomeSource.h"
#include "../include/dynamicArray.h"
#include "../include/EditIncomeSource.h"

#include <iostream>
#include <string>
#include <iomanip>

int getIndexById(DynamicArray<IncomeSource>& Sources, int id) {
    for(int index = 0; index < Sources.getSize(); index++) {
        if(Sources[index].get_id() == id) return index;
    }
    return -1;
}


bool addSource(DynamicArray<IncomeSource>& Sources, const IncomeSource& NewSource){
    if(NewSource.get_id() <= 0) return false;
    int index = getIndexById(Sources,NewSource.get_id());
    if(index == -1) {
        Sources.push(NewSource);
        return true;
    }
    return false;
}

void viewIncomeSources(DynamicArray<IncomeSource>& Sources) {
    if(Sources.getSize() == 0) {
        std::cout <<"------- " << "There are no income sources" << " -------\n"; 
    } else {
        std::cout << "------ " << "Income sources" << " ------\n";
        std::cout << std::left << std::setw(6) << "ID" << "Name\n";
        for(int i = 0; i < Sources.getSize(); i++){
            std::cout << std::setw(6) << Sources[i].get_id()
                 << std::setw (20) << Sources[i].get_name() << "\n";
        }
        std::cout << std::right;
    }
}

std::string getSourceNameById(DynamicArray<IncomeSource>& Sources, int ID) {
    int index = getIndexById(Sources,ID);
    if(index != -1) return Sources[index].get_name();
    return "N/A";
}

bool editIncomeSource(DynamicArray<IncomeSource>& Sources, int ID, const std::string& Newname) {
    int index = getIndexById(Sources,ID);
    if(index == -1) {
        return false;
    }
    Sources[index].edit_IncomeSource(Newname); //trả về " " nếu không điền gì
    return true;
}

bool deleteIncomeSource(DynamicArray<IncomeSource>& Sources, int ID) {
    int index = getIndexById(Sources,ID);
    if(index == -1) return false;
    Sources.pop(index);
    return true;
}