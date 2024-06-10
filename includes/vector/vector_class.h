#ifndef VECTOR_CLASS_H
#define VECTOR_CLASS_H
#include <iostream>
#include <vector>
#include "../../includes/add_entry/add_entry.h"
#include <assert.h>
using namespace std;


template <class T>
class Vector{
public:

    Vector(int capacity = 100);
    Vector(T *arr, int size);
    // big three:
    
    //copy constr
    Vector(const Vector& other);
    
    //assignment operator
    Vector& operator= (const Vector& RHS);

    //destructor
    ~Vector();

    //member access functions:
    T& operator [](int index);
    const T& operator [](int index) const;

    T& at(int index);              //return reference to item at position index
    const T& at(int index) const;  //return a const item at position index

    T& front();                         //return item at position 0.
    T& back();                          //return item at the last position


    //Push and Pop functions:
    Vector& operator +=(const T& item); //push_back
    void push_back(const T& item);      //append to the end
    T pop_back();                       //remove last item and return it


    //Insert and Erase:
    void insert(int insert_here, const T& insert_this); //insert at pos
    void erase(int erase_this_index);        //erase item at position
    int index_of(const T& item);             //search for item. retur index.

    //size and capacity:
    void set_size(int size);              //enlarge the vector to this size
    void set_capacity(int capacity);      //allocate this space
    int size() const;  //return _size
    int capacity() const; //return _capacity

    bool empty() const;                    //return true if vector is empty

    //array string
    string class_string();

    //OUTPUT:
    template <class U>
    friend ostream& operator <<(ostream& outs, const Vector<U>& _a);
private:
    int _capacity;
    int _size;
    int _how_many;
    T* _p;
};

//--------------------------------------------------------------------------//
//--------------------------------------------------------------------------//

template <class T>
Vector<T>::Vector(int capacity):_size(0), _capacity(capacity){
    _p = allocate <T>(_capacity);
}

template <class T>
Vector<T>::Vector(T *arr, int size):_size(size),_capacity(3){
    while(_capacity<=size){
        _capacity*=2;
    }
    _p = allocate <T>(_capacity);
    copy_array(_p,arr,size);
}

// big three:
    
//copy constr
template <class T>
Vector<T>::Vector(const Vector& other): _size(other.size()), _capacity(other.capacity()){
    _p = allocate<T>(_capacity);
    copy_array(_p,other._p,other.size());
}

//assignment operator
template <class T>
Vector<T> & Vector<T>::operator=(const Vector& RHS){
    if(this == &RHS){
        return *this;
    }
    _size = RHS.size();
    _capacity = RHS.capacity();

    if(_p != nullptr){
    delete [] _p;
    }
    _p = allocate<T>(_capacity);
    copy_array(_p,RHS._p,RHS.size());
    return *this;
}

//destructor
template <class T>
Vector<T>::~Vector(){
    delete [] _p;
    _p = nullptr;
}

//member access functions:
template <class T>
T& Vector<T>::operator [](int index){
    assert(!(index>=_size));
    assert(!(index<0));
    T* _p_walker = _p + index;
    return *_p_walker;
}

template <class T>
const T& Vector<T>::operator [](int index) const{
    return operator[](index);
}

template <class T>
T& Vector<T>::at(int index){
    assert(!(index>=_size));
    assert(!(index<0));
    T* _p_walker = _p + index;
    return *_p_walker;
}    
          //return reference to item at position index
template <class T>
const T& Vector<T>::at(int index) const{
    assert(!(index>=_size));
    assert(!(index<0));
    T found = at(index);
    return found;
}  //return a const item at position index

template <class T>
T& Vector<T>::front(){
    T front = at(0);
    return front;
}       
                  //return item at position 0.
template <class T>
T& Vector<T>::back(){
    T back = at(_size - 1);
    return back;
}                          //return item at the last position

//Push and Pop functions:
template <class T>
Vector<T>& Vector<T>::operator +=(const T& item){
   push_back(item);
   return *this; 
} //push_back
template <class T>
void Vector<T>::push_back(const T& item){
    _p = add_entry<T>(_p,item,_size,_capacity);
}      //append to the end
template <class T>
T Vector<T>::pop_back(){
    T last_item;
    _p = remove_last_entry <T> (_p,last_item,_size,_capacity);
    return last_item;
}                       //remove last item and return it

//Insert and Erase:
template <class T>
void Vector<T>::insert(int insert_here, const T& insert_this){
    _p = insert_entry <T> (_p,insert_this,insert_here,_size,_capacity);
} //insert at pos

template <class T>
void Vector<T>::erase(int erase_this_index){
    _p = erase_entry(_p,erase_this_index,_size,_capacity);
}        //erase item at position

template <class T>
int  Vector<T>::index_of(const T& item){
    int index_of = search(_p,_size,item);
    return index_of;
}             //search for item. return index.


//size and capacity:

template <class T>
void Vector<T>::set_size(int size){
    _size = size;
}              //enlarge the vector to this size

template <class T>
void Vector<T>::set_capacity(int capacity){
    delete []_p;
    _capacity = capacity;
    _p = allocate <T> (capacity);
}      //allocate this space

template <class T>
int Vector<T>::size() const {
    int _how_many = _size;
    return _how_many;
}  //return _size

template <class T>
int Vector<T>::capacity() const {
    return _capacity;
} //return _capacity

template <class T>
bool Vector<T>::empty() const{
    if (_size == 0){
        return true;
    }
    return false;
}                   //return true if vector is empty


//class string
template <class T>
string Vector<T>::class_string(){
    string class_string = array_string(_p,_size);
    return class_string;
}

//OUTPUT:
template <class U>
ostream& operator <<(ostream& outs, const Vector<U>& _a){
    print_array(_a._p,_a.size(),_a.capacity());
    return outs;   
}

#endif

