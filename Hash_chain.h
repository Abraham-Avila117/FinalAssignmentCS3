#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H
/*
This header file was made and developed by Abraham Avila

We used a header file for this project to make the hash chaining 
data structure to implement the object hash and store the data in
the table.
*/

#include <iostream>
#include <cassert>
#include <cstring>
#include "Vector.h"

using namespace std;

template <class T>
struct Node{
    int length = 0;
    T item;
    Node<T>* next;
    Node<T>* tail;
};

template <class T>
class Hash_chain{
public:
    Hash_chain();
    Hash_chain(T, int);
    
    int getSize()const;     // gets size of hash table
    T search(int)const;    // searches the item given a hash index
    int search(T);     // searches the hash index given an item
    void insert(T, int);    // insertion to hash table
    void insertCharArray(char*, int);   // insertion specific to char*
    void print()const;          // prints the entire table
    void printIdx(int)const;    // prints a specific hash index item and its linklist
    bool isEmpty()const;        // checks if hash table is empty
    bool isFull(Node<T>[], int)const;
    bool exceedSize(int)const;  // function to prevent out of range array access
    bool isIn(T, int)const;     // checks if the given itam and hash index is in the table
    bool isInChar(char*,int)const; // this is specific to char* isIn function
    void optimize();

    ~Hash_chain();
private:
    Node<T>* array;
    T buffer;
    int size;
    void reSize(int);
    int nullSum(Node<T>[], int);
};

template <class T>
Hash_chain<T>::Hash_chain(){
    size = 1000;
    buffer = nullptr;
    array = new Node<T>[size];
    assert(array!=nullptr);
    for(int i = 0; i < size; i++){
        array[i].item = buffer;
        array[i].next = nullptr;
        array[i].tail = nullptr;
    }
}

template <class T>
Hash_chain<T>::Hash_chain(T initalize, int size){
    this->size = size;
    buffer = initalize;
    array = new Node<T>[this->size];
    assert(array!=nullptr);
    for(int i = 0; i < this->size; i++){
        array[i].item = buffer;
        array[i].next = nullptr;
        array[i].tail = nullptr;
    }
}

template <class T>
int Hash_chain<T>::getSize()const{
    return size;
}

template <class T>
T Hash_chain<T>::search(int hashIdx)const{
    return array[hashIdx].item;
}

template <class T>
int Hash_chain<T>::search(T findItem){
    int sum = 0;
    for(int i = 0; i < strlen(findItem); i++){
        sum += findItem[i];
    }
    return sum%size;
}

template <class T>
void Hash_chain<T>::reSize(int oldSize){
    Vector<T> vec;
    int sum = 0, idx = 0, newSize = oldSize - 1, numberOfElements = 0;
    T tmp;
    Node<T>* newArray = new Node<T>[newSize], *curr = nullptr;  
    assert(newArray!=nullptr);  

    for(int i = 0; i < newSize; i++){ // initalize new list (trust)
        newArray[i].item = buffer;
        newArray[i].next = nullptr;
        newArray[i].tail = nullptr;
    } 

    for(int i = 0; i < size; i++){          // preserve everything from the previous list (trust)
        if(array[i].item == buffer) continue;
        else{
            vec.push(array[i].item);
            curr = array[i].next;
            while(curr != nullptr){
                vec.push(curr->item);
                curr = curr->next;
            }
        }
    }
    
    numberOfElements = vec.getsize();
    for(int i = 0; i < numberOfElements; i++){   // everything from vec list gets re-hashed (trust)
        sum = 0;
        tmp = vec.getTop();
        vec.pop();
        for(int j = 0; j < strlen(tmp); j++){
            sum += tmp[j];
        }
        idx = sum % newSize; 

        if(newArray[idx].item != buffer){
            if(newArray[idx].next == nullptr){
                curr = new Node<T>;
                assert(curr!=nullptr);
                curr->item = tmp;
                curr->next = nullptr;
                curr->tail = &newArray[idx];
                newArray[idx].next = curr;
                newArray[idx].tail = curr;
                curr = nullptr;
                newArray[idx].length++;
            }else{
                curr = new Node<T>;
                assert(curr!=nullptr);
                curr->item = tmp;
                curr->next = nullptr;
                newArray[idx].tail->next = curr;
                curr->tail = newArray[idx].tail;
                newArray[idx].tail = curr;
                curr = nullptr;
                newArray[idx].length++;                
            }
        }else if(newArray[idx].item == buffer){
            newArray[idx].item = tmp;
            newArray[idx].length++;  
        }
    }
    vec.clear();

    if(!isFull(newArray, newSize)){
        delete [] newArray;
        reSize(newSize);
    }else{
        array = newArray;
        newArray = nullptr;  
        size = newSize;      
    }
}

template <class T>
void Hash_chain<T>::insertCharArray(char* newitem, int idx){
    try{
        if(exceedSize(idx))
            throw idx;           
        else if(isInChar(newitem, idx)){ //this conditional is the only difference to insert
            return;
        }
        else if(array[idx].item != buffer){
            Node<T>* curr;
            if(array[idx].next == nullptr){
                curr = new Node<T>;
                assert(curr!=nullptr);
                curr->item = newitem;
                curr->next = nullptr;
                curr->tail = &array[idx];
                array[idx].next = curr;
                array[idx].tail = curr;
                curr = nullptr;
                array[idx].length++;
                return;
            }

            curr = new Node<T>;
            assert(curr!=nullptr);
            curr->item = newitem;
            curr->next = nullptr;
            array[idx].tail->next = curr;
            curr->tail = array[idx].tail;
            array[idx].tail = curr;
            curr = nullptr;
            array[idx].length++;
            return;   
        }
        else if(array[idx].item == buffer){
            array[idx].item = newitem;
            array[idx].length++;
        }
    }catch(out_of_range& ex){
        cerr << ex.what() << endl;
        return;
    }
}

template <class T>
void Hash_chain<T>::insert(T newitem, int idx){
    try{
        if(exceedSize(idx))
            throw idx;           
        else if(isIn(newitem, idx)){
            return;
        }
        else if(array[idx].item != buffer){
            Node<T>* curr;
            if(array[idx].next == nullptr){
                curr = new Node<T>;
                assert(curr!=nullptr);
                curr->item = newitem;
                curr->next = nullptr;
                curr->tail = &array[idx];
                array[idx].next = curr;
                array[idx].tail = curr;
                curr = nullptr;
                array[idx].length++;
                return;
            }

            curr = new Node<T>;
            assert(curr!=nullptr);
            curr->item = newitem;
            curr->next = nullptr;
            array[idx].tail->next = curr;
            curr->tail = array[idx].tail;
            array[idx].tail = curr;
            curr = nullptr;
            array[idx].length++;
            return;   
        }
        else if(array[idx].item == buffer){
            array[idx].item = newitem;
            array[idx].length++;
        }
    }catch(out_of_range& ex){
        cerr << ex.what() << endl;
        return;
    }
}

template <class T>
void Hash_chain<T>::print()const{
    Node<T>* tmp;
    int chainLength = 0;
    int nullCounter = 0;
    int c = 0;
    for(int i = 0; i < size; i++){
        if(array[i].item == nullptr && array[i].next == nullptr){
            nullCounter++;
            continue;
        } 
        else{
            if(array[i].length > chainLength)
                chainLength = array[i].length;
            cout << array[i].item << " -> ";
            c++;
            tmp = &array[i];
            tmp = tmp->next;
            while(tmp != nullptr){
                cout << tmp->item << ", ";
                tmp = tmp->next;
                c++;
            }
            cout << "|" << endl;            
        }
    }
    cout << "Nulls in table is: " << nullCounter << endl;
    cout << "max chain length: " << chainLength << endl;
    cout << "size of table array: " << size << endl;
    cout << "Number of elements in table: " << c << endl;
    tmp = nullptr;
}

template <class T>
void Hash_chain<T>::printIdx(int idx)const{
    Node<T>* tmp = array[idx].next;

    cout << array[idx].item << " -> ";

    while(tmp != nullptr){
        cout << tmp->item << ", ";
        tmp = tmp->next;
    }
    cout << "|" << endl;
}

template <class T>
bool Hash_chain<T>::isEmpty()const{
    return size == 0;
}

template <class T>
bool Hash_chain<T>::isFull(Node<T> list[], int otherSize)const{
    for(int i = 0; i < otherSize; i++){
        if(list[i].item == nullptr)
            return false;

    }
    return true;
}

template <class T>
bool Hash_chain<T>::exceedSize(int idx)const{
    return ((idx >= size) ? true : false);
}

template <class T>
bool Hash_chain<T>::isIn(T search, int place)const{
    Node<T>* tmp;
    if(array[place].item == buffer)
        return false;
    else if(array[place].item == search){
        tmp = nullptr;
        return true;
    }
    else{
        tmp = array[place].next;
        while(tmp != nullptr){
            if(tmp->item == search){
                tmp = nullptr;
                return true;
            }
            tmp = tmp->next;
        }
    }
    tmp = nullptr;
    return false;
}

// this function is specific for char* datatypes
template <class T>
bool Hash_chain<T>::isInChar(char* search, int place)const{
    Node<T>* tmp;
    if(array[place].item == nullptr)
        return false;
    else if(strcmp(array[place].item,search)==0){
        tmp = nullptr;
        return true;
    }
    else{
        tmp = array[place].next;
        while(tmp != nullptr){
            if(strcmp(tmp->item,search)==0){
                tmp = nullptr;
                return true;
            }
            tmp = tmp->next;
        }
    }
    tmp = nullptr;
    return false;
}

template <class T>
void Hash_chain<T>::optimize(){
    if(!isFull(array, size))
        reSize(size);
}

template <class T>
int Hash_chain<T>::nullSum(Node<T> list[], int otherSize){
    int nullCounter = 0;
    for(int i = 0; i < otherSize; i++){
        if(list[i].item == nullptr)
            nullCounter++;    
    }  
    cout << nullCounter << endl;
    return nullCounter;
}

template <class T>
Hash_chain<T>::~Hash_chain(){
    Node<T>* head, *tmp;
    for(int i = 0; i < size; i++){
        head = array[i].next;
        while(head!=nullptr){
            tmp = head;
            head = head->next;
            delete tmp;
        }
        array[i].next = nullptr;
    }
    head = nullptr;
    tmp = nullptr;
    delete [] array;
}

#endif