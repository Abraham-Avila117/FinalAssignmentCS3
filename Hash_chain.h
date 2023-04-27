#ifndef HASH_CHAIN_H
#define HASH_CHAIN_H

#include <iostream>
#include <cassert>

using namespace std;

template <class T>
struct Node{
    T item;
    Node<T>* next;
};

template <class T>
class Hash_chain{
public:
    Hash_chain();
    Hash_chain(T, int);
    void insert(T, int);
    void print()const;
    bool isEmpty()const;
    bool exceedSize(int)const;

    ~Hash_chain();

private:
    Node<T>* array;
    T buffer;
    int size;
};

template <class T>
Hash_chain<T>::Hash_chain(){
    size = 1402895;
    buffer = '\0';
    array = new Node<T>[size];
    assert(array!=nullptr);
    for(int i = 0; i < size; i++){
        array[i].item = buffer;
        array[i].next = nullptr;
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
    }
}

template <class T>
void Hash_chain<T>::insert(T newitem, int idx){
    try{
        if(exceedSize(idx))
            throw idx; 
        else if(array[idx].item != buffer){
            Node<T>* curr = array[idx].next;
            if(array[idx].next == nullptr){
                curr = new Node<T>;
                assert(curr!=nullptr);
                curr->item = newitem;
                curr->next = nullptr;
                array[idx].next = curr;
                curr = nullptr;
                return;
            }

            while(curr->next != nullptr)
                curr = curr->next;
            
            Node<T>* tmp = new Node<T>;
            assert(tmp!=nullptr);
            tmp->item = newitem;
            tmp->next = nullptr;
            curr->next = tmp;
            tmp = nullptr;
            return;   
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
        cout << array[i].item << " -> ";
        tmp = array[i].next;
        while(tmp != nullptr){
            cout << tmp->item << ", ";
            tmp = tmp->next;
        }
        cout << endl;
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