#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H
#include <bits/stdc++.h>
using namespace std;
//declare dynamicarray class

template <typename T>
class DynamicArray{

    private:

    T* data;
    int capacity;
    int size;
    void reallocate(){
        capacity *= 2;
        T* newdata = new T[capacity];
        for (int i = 0; i< size; ++i){
            newdata[i] = data[i];
        }
        delete[] data;
        data = newdata;
        newdata = nullptr;
    }

    public:

    DynamicArray(): capacity(4), size(0){
        data = new T[capacity];
    }
    ~DynamicArray(){
        delete[] data;
    }

    T& operator[](int index){
        return data[index];
    }
    
    int getSize(){
        return size;
    }

    void push(const T& element){
        if (size == capacity){reallocate();}
        data[size++] = element;
    }

    void insert(const T& element, int index){
        if (size == capacity){reallocate();}
        for (int i=size; i > index; --i ){
            data[i] = data[i-1];
        }
        data[index] = element;
        size++;
    }

    T pop(int index){
        T temp = data[index];
        size--;
        for (int i=index; i < size; ++i ){
            data[i] = data[i+1];
        }
        return temp;
    }

    T pop(){
        T temp = data[--size];
        return temp;
    }

    void clear(){
        size = 0;
        capacity = 4;
        T* newdata = new T[capacity];
        delete[] data;
        data = newdata;
        newdata = nullptr;
    }

    void print(){
        for (int i =0; i< size; i++){
            cout << data[i] << " ";
        }
        cout << "\n";
    }
};

#endif
