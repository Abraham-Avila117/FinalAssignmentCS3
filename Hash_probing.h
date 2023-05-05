#ifndef HASH_PROBING_H
#define HASH_PROBING_H
/*
This header file was made by Arin Hartung
*/

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;

template <class T>
struct Probe_Node{
    int num = 0;
    T item;
};

template <class T>
class Hash_probe{
public:
    Hash_probe();
    Hash_probe(T, int);
    int getSize()const;
    void insert(T, int);
    int search(T, int);
    void print()const;
    bool isEmpty()const;
    bool exceedSize(int)const;
    void sort();

    ~Hash_probe();

private:
    Probe_Node<T>* array;
    T buffer;
    int size;
};

template <class T>
Hash_probe<T>::Hash_probe(){
    size = 1402895;
    buffer = nullptr;
    array = new Probe_Node<T>[size];
    assert(array!=nullptr);
    for(int i = 0; i < size; i++){
        array[i].item = buffer;
    }
        
}

template <class T>
Hash_probe<T>::Hash_probe(T initalize, int size){
    this->size = size;
    buffer = initalize;
    array = new Probe_Node<T>[this->size];
    assert(array!=nullptr);
    for(int i = 0; i < this->size; i++){
        array[i].item = buffer;
    }
}

template <class T>
int Hash_probe<T>::getSize()const{
    return size;
}

template <class T>
void Hash_probe<T>::insert(T newitem, int idx){
    try{
        if(exceedSize(idx))
            throw idx;
            bool T_F = true;
            bool loop = false;
            
            while(T_F)
            {
             if(array[idx].item == buffer){
                 Probe_Node<T> prob = *new Probe_Node<T>;
                        //assert(prob!=null);
                 prob.item = newitem;
                 prob.num = 1;
                        array[idx] = prob;
                        T_F = false;
                    }
         else if(array[idx].item == newitem){
                    array[idx].item = newitem;
                    array[idx].num++;
                    T_F= false;
        }
        idx++;
        if (exceedSize(idx))
        {
            idx=0;
            if(loop)
                throw idx;
            loop=true;
        }
        }
        return;
    }
    catch(out_of_range& ex){
        cerr << ex.what() << endl;
        return;
    }
}

template <class T>
void Hash_probe<T>::print()const{
    for(int i = 0; i < size; i++){
        if(array[i].item == nullptr) continue;
        else{
            cout << array[i].item << " -> "<< array[i].num;
            cout << "|" << endl;
        }
    }
}

template <class T>
bool Hash_probe<T>::isEmpty()const{
    return size == 0;
}

template <class T>
bool Hash_probe<T>::exceedSize(int idx)const{
    return ((idx >= size) ? true : false);
}
template <class T>
int Hash_probe<T>::search(T search, int start){
    int end = start;
    bool T_F = true;
    bool loop = false;
    if (search == array[start].item)
        return end;
    else
        while (T_F) {
    end++;
    if (exceedSize(end))
    {
        end=0;
        if(loop)
            return -1;
        loop=true;
        
    }
    if (search == array[end].item)
            return end;
    }
    return -1;
}
template <class T>
Hash_probe<T>::~Hash_probe(){
    Probe_Node<T> temp;
    for(int i = 0; i < size; i++){
        temp = array [i];
        // delete temp;
    }
    delete [] array;
}

#endif
