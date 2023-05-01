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

using namespace std;

template <class T>
struct Node{
    int rank = 0;
    T item;
    Node<T>* next;
    Node<T>* tail;
};

template <class T>
class Hash_chain{
public:
    Hash_chain();
    Hash_chain(T, int);
    int getSize()const;
    void insert(T, int);
    void print()const;
    bool isEmpty()const;
    bool exceedSize(int)const;
    bool isIn(T, int)const;

    ~Hash_chain();

private:
    Node<T>* array;
    T buffer;
    int size;
};

template <class T>
Hash_chain<T>::Hash_chain(){
    size = 1402895;
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
                curr->rank++;
                curr->next = nullptr;
                curr->tail = &array[idx];
                array[idx].next = curr;
                array[idx].tail = curr;
                curr = nullptr;
                return;
            }

            curr = new Node<T>;
            assert(curr!=nullptr);
            curr->item = newitem;
            curr->rank++;
            curr->next = nullptr;
            array[idx].tail->next = curr;
            curr->tail = array[idx].tail;
            array[idx].tail = curr;
            curr = nullptr;
            return;   
        }
        else if(array[idx].item == buffer){
            array[idx].item = newitem;
            array[idx].rank++;
        }
    }catch(out_of_range& ex){
        cerr << ex.what() << endl;
        return;
    }
}

template <class T>
void Hash_chain<T>::print()const{
    Node<T>* tmp;
    for(int i = 0; i < size; i++){
        if(array[i].item == nullptr && array[i].next == nullptr) continue;
        else{
            cout << array[i].item << " -> ";
            tmp = &array[i];
            tmp = tmp->next;
            while(tmp != nullptr){
                cout << tmp->item << ", ";
                tmp = tmp->next;
            }
            cout << endl;            
        }
    }
    tmp = nullptr;
}

template <class T>
bool Hash_chain<T>::isEmpty()const{
    return size == 0;
}

template <class T>
bool Hash_chain<T>::exceedSize(int idx)const{
    return ((idx >= size) ? true : false);
}

template <class T>
bool Hash_chain<T>::isIn(T search, int place)const{
    Node<T>* tmp;
    if(array[place].item == nullptr && array[place].next == nullptr){
        tmp = nullptr;
        return false;
    }
    else if(strcmp(array[place].item, search)==0){
        array[place].rank++;
        tmp = nullptr;
        return true;
    } 
    else{
        tmp = &array[place];
        // cout << "word to compare: " << search << endl;
        while(tmp->next != nullptr){
            if(strcmp(tmp->item, search) == 0){
                tmp->rank++;
                tmp = nullptr;
                return true;
            }
            // cout << "test: " << tmp->item << endl;
            // cout << "result: " << (tmp->item == search) << endl;
            tmp = tmp->next;
        }
    } 
    tmp = nullptr;
    return false;
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