#ifndef occur_h
#define occur_h
#include <cstring>
#include <iostream>

using namespace std;

template <class T>
struct Occurence{
    T word;
    int rank = 0;
};

template <class T>
class Occur{
public:
    Occur<T>();
    Occur<T>(int);
    T getTop();
    T getBottom();
    int getTopRank();
    int  getBottomRank();
    void printTop(int) const;
    void printbottem(int)const;
    void push(T); // insert into the vector list
    void remove(T); // delete or pop certain element
    int search(T);  // search for element in list
    void pop();     // remove last element
    void clear();   // clear the list
    bool isEmpty()const; // check if list is empty
    bool isFull()const;  // check if list is full to increase size
    void print() const;
    void sort();// start the sort
    void sort(Occurence<T> *, int, int); //recersive call for the sort
    void merge(Occurence<T> *, int const, int const,int const); // merge sort fuction
    Occurence<T> * getList();       //get list so far
    T * getWordList(); //words
    int *getRankList(); //ranks
    int getsize()const; //get the size of list so far

    ~Occur();

private:
    Occurence<T>* vec;
    int size;
    int maxSize;
};

template <class T>
Occur<T>::Occur(){
 vec = new Occurence<T>[100];
 size = 0;
 maxSize = 100;
}

template <class T>
Occur<T>::Occur(int zize){
 vec = new Occurence<T>[zize];
 size = 0;
 maxSize = zize;
}

template <class T>
T Occur<T>::getTop(){
    return vec[size-1].word;
}

template <class T>
T Occur<T>::getBottom(){
    return vec[0].word;
}
template <class T>
int Occur<T>::getTopRank(){
    return vec[size-1].rank;
}

template <class T>
int Occur<T>::getBottomRank(){
    return vec[0].rank;
}

template <class T>
void Occur<T>::push(T elem){
    int a = search(elem);
    bool temp_TF = isFull();
    if(temp_TF)
    {
        maxSize = maxSize+10;
        Occurence<T> *temp = new Occurence<T>[maxSize];
        for(int i=0; i< size; i++)
        {
            //cout<<vec[i].word<<endl;
            temp[i].word = vec[i].word;
            //cout<<temp[i].word<<endl;
            temp[i].rank = vec[i].rank;
        }
        delete [] vec;
        vec = temp;
        temp =nullptr;
    }
    if(a!=-1)
    {
        int b = vec[a].rank;
        b++;
        vec[a].rank = b;

    }
    if(a == -1)
    {
        vec[size].word = elem;
        vec[size].rank = 1;
        size++;
    }

}

template <class T>
int Occur<T>::search(T elem){
    for(int i = 0; i < size; i++){
        if(strcmp(vec[i].word,elem)==0){
            return i;
        }
    }
    return -1;
}

template <class T>
void Occur<T>::clear(){
    delete [] vec;
    size = 0;
    vec = new Occurence<T>[maxSize];
}

template <class T>
bool Occur<T>::isFull()const{
    return (size == maxSize);
}

template <class T>
bool Occur<T>::isEmpty()const{
    return (size <= 0);
}
  template <class T>
void Occur<T>::remove(T item)
{
    int index = search(item);
    bool temp = isFull();
    if (index != -1)
    {
        if(temp)
            for(int i = index; i<size; i++)
            {
                vec[i] = vec[i+1];
            }
             
        size--;
    }
    else
        return;
    
}

template <class T>
void Occur<T>::pop()
{
    if(isEmpty())
        return;
    else
        size--;
}

template <class T>
void Occur<T>::sort(Occurence<T> *array, int begin, int end){
    if (begin >= end)
        return;
    int mid = begin + (end - begin) / 2;
    sort(array, begin, mid);
    sort(array, mid + 1, end);
    merge(array, begin, mid, end);
}

template <class T>
void Occur<T>::sort(){
    if (0 >= size)
        return;
    int mid = 0 + (size - 1) / 2;
    sort(vec, 0, mid);
    sort(vec, mid + 1, size-1);
    merge(vec, 0, mid, size-1);
}

template <class T>
void Occur<T>::merge(Occurence<T> *array, int const left, int const mid, int const right)
{
    int  subArrayOne = mid - left + 1;
    int  subArrayTwo = right - mid;
 
    // Create temp arrays
    Occurence<T> *leftArray = new Occurence<T>[subArrayOne], *rightArray = new Occurence<T> [subArrayTwo];
 
    // Copy data to temp arrays
    for (int i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (int j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];
 
    int indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge the temp arrays back into array
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo) {
        if (leftArray[indexOfSubArrayOne].rank <= rightArray[indexOfSubArrayTwo].rank)
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray]= rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne) {
        array[indexOfMergedArray]= leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
    }
    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo) {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
    }
    delete[] leftArray;
    delete[] rightArray;
}

template <class T>
int Occur<T>::getsize()const
{
    return size;
}

template <class T>
Occurence<T> * Occur<T>::getList()
{
    Occurence<T> * list = new Occurence<T> [size];
    for(int i=0; i< size; i++)
    {
        list[i]=vec[i];
    }
    return list;
}

template <class T>
T * Occur<T>::getWordList()
{
    T * list = new T[size];
    for(int i=0; i< size; i++)
    {
        list[i]=vec[i].word;
    }
    return list;
}
template <class T>
int* Occur<T>::getRankList()
{
    int * list = new int[size];
    for(int i=0; i< size; i++)
    {
        list[i]=vec[i].rank;
    }
    return list;
}
template <class T>
void Occur<T>::print()const
{
    cout<<"max size = "<<maxSize<<"  size ="<<size<<endl;
    for(int i=0; i< size; i++)
    {
        cout<<vec[i].word<<" | "<<vec[i].rank<<endl;
    }
}
template <class T>
void Occur<T>::printTop(int amount)const
{ 
    int count = 1;
    int a = (size-1);
    int b = (size-amount);
    for(int i=a; i>=b; i = i-1)
    {
        cout<<count<<vec[i].word<<" | "<<vec[i].rank<<endl;
        count++;
    }
}
template <class T>
void Occur<T>::printbottem(int amount)const
{
    int count = 1; 
    for(int i=0; i< amount; i++)
    {
        cout<<count <<". "<< vec[i].word<<" | "<<vec[i].rank<<endl;
        count++;
    }
}
template <class T>
Occur<T>::~Occur(){
delete [] vec;
}
#endif
