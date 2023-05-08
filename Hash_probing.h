#ifndef HASH_PROBING_H
#define HASH_PROBING_H
/*
This header file was made by Arin Hartung
*/

#include <iostream>
#include <cassert>
#include <cstring>

using namespace std;
/*
template <class T>
struct Probe_Node{
    int num = 0;
    T item;
};
*/
template <class T>
class Hash_probe{
public:
    Hash_probe();
    Hash_probe(Hash_probe, int);
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
    T* array;
    T buffer;
    int size;
    int size_count;
};

template <class T>
Hash_probe<T>::Hash_probe(){
    size = 1402895;
    size_count = 0;
    buffer = nullptr;
    array = new T[size];
    assert(array!=nullptr);
    for(int i = 0; i < size; i++){
        array[i] = buffer;
    }
    
        
}

template <class T>
Hash_probe<T>::Hash_probe(T initalize, int size){
    this->size = size;
    buffer = initalize;
    size_count = 0;
    array = new T[this->size];
    assert(array!=nullptr);
    for(int i = 0; i < this->size; i++){
        array[i] = buffer;
    }
}
template <class T>
Hash_probe<T>::Hash_probe(Hash_probe old_probe, int new_size)
{
    this->size = new_size;
    this->buffer = old_probe.buffer;
    size_count = 0;
    array = new T[this->size];
    assert(array!=nullptr);
    if (new_size>size)
    {
    for(int i = 0; i < old_probe.size; i++){
        array[i] = old_probe.array[i];
    }
    for(int i=old_probe.size; i<new_size; i++)
    {
        array[i]= buffer;
    }
    }
    else
    {
        for(int i = 0; i < size; i++)
        {
        array[i] = buffer;
    }
        for(int i=0; i < old_probe.size; i++)
        {
            if(old_probe.array[i]!=buffer)
                this-> Hash_probe.insert(old_probe.array[i], i%new_size);
                }
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
        double test = size_count/size;
        if (test > 0.75)
        {
            this->Hash_probe<T> = Hash_probe(this->Hash_probe, size+1);
        }
            while(T_F)
            {
             if(array[idx] == buffer){
                 array[idx] = newitem;
                        T_F = false;
                 size_count++;
                    }
         else if(array[idx] == newitem){
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
        if(array[i] == buffer) continue;
        else{
            cout << array[i] << " ";
        }
        cout << endl;
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
    if (search == array[start])
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
    if (search == array[end])
            return end;
    }
    return -1;
}
template <class T>
Hash_probe<T>::~Hash_probe(){
    delete [] array;
}

#endif
