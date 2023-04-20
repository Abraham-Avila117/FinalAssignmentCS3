#ifndef LINKLIST_H
#define LINKLIST_H

#include <iostream>

using namespace std;

template <class T>
struct Node{
    T item;
    Node<T>* list;
};

template <class T>
class List{
public:
    List();
    List(int);
    void push(T);
    T pop_front();
    void insert(T);
    void print()const;
    bool isEmpty()const;
    bool isFull()const;

    ~List();

private:
    void remove(T);
    Node<T>* array;
    int size, maxSize;
};

template <class T>
List<T>::List(){
    array = new T[10];
    size = 0;
    maxSize = 10;
}

template <class T>
List<T>::List(int N){
    array = new T[N];
    maxSize = N;
    size = 0;
}

template <class T>
void List<T>::push(T newitem){
    if(isFull()){
        cout << "List is full" << endl;
        return;
    }else{
        array[size]->item = newitem;
        array[size]->list = new T[maxSize];
        size++;
    }
}



#endif