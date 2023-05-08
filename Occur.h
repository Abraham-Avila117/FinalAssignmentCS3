#ifndef occur_h
#define occur_h

template <class T>
struct Occurence{
    T word;
    int rank = 0;
};

template <class T>
class Occur{
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


#endif