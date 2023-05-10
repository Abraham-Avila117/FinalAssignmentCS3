#ifndef vector_h
#define vector_h 

#include <iostream>
#include <cassert>
#include <cctype>

using namespace std;

template <class T>
class Vector{
public:
    Vector();
    Vector(int);
    T getTop();
    T getBottom();
    void push(T); // insert into the vector list
    void remove(T); // delete or pop certain element
    int search(T);  // search for element in list
    void pop();     // remove last element
    void clear();   // clear the list
    bool isEmpty()const; // check if list is empty
    bool isFull()const;  // check if list is full to increase size 
    void print() const; 
    T* getList();       //get list so far
    int getsize()const; //get the size of list so far

    ~Vector();

private:
    T* vec;
    int size;
    int maxSize;
};

template <class T>
Vector<T>::Vector(){
    vec = new T[10];
    size = 0;
    maxSize = 10;
}

template <class T>
Vector<T>::Vector(int max){
    this->maxSize = max;
    this->size = 0;
    vec = new T[this->maxSize];
}

template <class T>
T Vector<T>::getBottom(){
    return vec[0];
}

template <class T>
T Vector<T>::getTop(){
    return vec[size];
}

template <class T>
void Vector<T>::push(T elem){
    if(isFull()){
        maxSize *= 2;
        T* tmp = new T[maxSize];
        assert(tmp!=nullptr);
        for(int i = 0; i < maxSize; i++)
            tmp[i] = vec[i];

        delete [] vec;
        vec = tmp;
        tmp = nullptr;
        vec[size] = elem;
        size++;

    }else{
        vec[size] = elem;
        size++;
    }
}

template <class T>
void Vector<T>::remove(T elem){
    if(isEmpty()){
        cout << "No more elements can be added to the list" << endl;
        return;

    }else{
        int pivot = search(elem);
        for(; pivot < size-1; pivot++){
            if(pivot>=size-1){
                return;
            }
            vec[pivot] = vec[pivot+1];
        }
    }
}

template <class T>
int Vector<T>::search(T elem){
    for(int i = 0; i < size-1; i++){
        if(vec[i]==elem){
            return i;
        }
    }
    return -1;
}

template <class T>
void Vector<T>::pop(){
    if(isEmpty()){
        cout << "No more elements to pop" << endl;
        return;
    }
    --size;  
}

template <class T>
void Vector<T>::clear(){
    delete [] vec;
    size = 0;
    vec = new T[maxSize];
}

template <class T>
bool Vector<T>::isEmpty() const {
    return (size<=0);
}

template <class T>
bool Vector<T>::isFull() const {
    return (size>=maxSize);
}

template <class T>
void Vector<T>::print() const{
    for(int i = 0; i < size; i++){
        cout << vec[i] << ' ';
    }
    cout << endl;
}

template <class T>
T* Vector<T>::getList(){
    T* list = new T[size];

    // assert(list!=nullptr);
    // cout << "vector size is: "<<size << endl;
    // cout << "list before copy: " <<list << endl;
    // cout << "strlen before copy " << strlen(list) << endl;
    for(int i = 0; i < size; i++){
        if(isalpha(vec[i])){
            list[i] = vec[i];
        }
        // cout << vec[i] << endl;
        // cout << list[i] << endl;
    }
    // cout << "list: " << list << endl;
    // cout << "strlen(list): " << strlen(list) << endl;
    return list;
}

template <class T>
int Vector<T>::getsize()const{
    return size;
}

template <class T>
Vector<T>::~Vector(){
    delete [] vec;
}

#endif