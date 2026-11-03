#include <bits/stdc++.h>
#include "../include/DynamicArray.h"
using namespace std;

int main(){
    DynamicArray<int> arr;
    arr.push(1);
    arr.print();
    arr.push(2);
    arr.print();
    arr.insert(0, 1);
    arr.print();
    arr[2] =3;
    arr.print();
    auto n = arr.pop();
    cout << "n " <<n<<endl;
    arr.print();
    cout << arr.getSize() << endl;
    arr.push(1);
    arr.push(9);
    arr.push(1);
    arr.push(2);
    arr.print();
    auto m = arr.pop(3);
    cout << "m " <<m<<endl;
    arr.print();
    arr.clear();
    arr.print();


    return 0;
}
/*
1 2 
1 0 2 
1 0 3 
n 3
1 0 
2
1 0 1 9 1 2 
m 9
1 0 1 1 

*/