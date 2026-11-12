#include <iostream>
#include "../include/EditIncomeSource.h"

int main() {
    std::cout << std::boolalpha;
    DynamicArray<IncomeSource> sources;

    viewIncomeSources(sources);

  
    std::cout << addSource(sources, IncomeSource(1, "Luong")) << "\n";     
    std::cout << addSource(sources, IncomeSource(3, "Thuong")) << "\n";     
    std::cout << addSource(sources, IncomeSource(4, "Freelance")) << "\n";  


    std::cout << addSource(sources, IncomeSource(1, "Trung")) << "\n";     
    std::cout << addSource(sources, IncomeSource(0, "SaiID")) << "\n";     
    viewIncomeSources(sources);                                             


    std::cout << getSourceNameById(sources, 3) << "\n";                     
    std::cout << getSourceNameById(sources, 9) << "\n";                     

 
    std::cout << editIncomeSource(sources, 3, "Bonus") << "\n";          
    std::cout << editIncomeSource(sources, 9, "Khong co") << "\n";        
    std::cout << getSourceNameById(sources, 3) << "\n";                   

    // 6. Xóa phần tử ở giữa, rồi xóa ID không có
    std::cout << deleteIncomeSource(sources, 3) << "\n";                 
    std::cout << deleteIncomeSource(sources, 9) << "\n";                   
    viewIncomeSources(sources);                  

    return 0;
}
/*
------- There are no income sources -------
true
true
true
false
false
------ Income sources ------
ID    Name
1     Luong               
3     Thuong              
4     Freelance
Thuong
N/A
true
false
Bonus
true
false
------ Income sources ------
ID    Name
1     Luong
4     Freelance     
*/      