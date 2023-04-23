#ifndef HASH_H
#define HASH_H

#include <iostream>

using namespace std;

template <class T>
struct Node{
    T item;
    Node<T>* chain;
};

template <class T>
class Hash{
public:
    Hash();
    Hash(T, int);
    void insert(T, int);
    T pop_front(); // not necessary
    T linear_probe(T)const;
    void print()const;
    bool isEmpty()const;
    bool exceedSize(int)const;

    ~Hash();

private:
    Node<T>* array;
    T buffer;
    int size;
};

template <class T>
Hash<T>::Hash(){
    size = 1402895;
    buffer = '\0';
    array = new Node<T>[size];
    for(int i = 0; i < size; i++)
        array[i].item = buffer;
}

template <class T>
Hash<T>::Hash(T initalize, int size){
    this->size = size;
    buffer = initalize;
    array = new Node<T>[this->size];
    for(int i = 0; i < this->size; i++)
        array[i].item = buffer;
}

template <class T>
void Hash<T>::insert(T newitem, int idx){
    try{
        if(exceedSize(idx)){
            
        }

        // if(exceedSize(idx)){
        //     insert(newitem, 0);
        // }else if(array[idx].item == buffer){
        //     array[idx].item = newitem;
        //     arrry[idx].chain = new Node<T>;
        // }else{
        //     insert(newitem, idx + 1);
        // }
    }catch(out_of_range& ex){
        cerr << ex.what() << endl;
        return;
    }

    // if(isEmpty()){
    //     head = new Node<T>;
    //     tail = head;
    //     head->index = 0;
    //     head->item = newitem;
    //     head->chain = new Node<T>;
    //     size++;
    // }else if(exceedSize(idx)){
        
    // }else{
    //     Node<T>* temp = head;
    //     for(int i = 0; i < size; i++){

    //     }
    // }
}

template <class T>
bool Hash<T>::isEmpty()const{
    return size == 0;
}

template <class T>
bool Hash<T>::exceedSize(int idx)const{
    return ((idx >= size) ? true : false);
}

#endif