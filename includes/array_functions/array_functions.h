#ifndef ARRAY_FUNCTIONS_H
#define ARRAY_FUNCTIONS_H
#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <cassert>
#include <typeinfo>

using namespace std;
const int MINIMUM_CAPACITY = 3;

template<class T>
T* allocate(int capacity= MINIMUM_CAPACITY);            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template<class T>
T* reallocate(T* a, int size, int capacity);            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<class T>
void print_array(T* a, int size, 
            int capacity = 0, ostream& outs = cout);    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <class T>
void print(T* a, unsigned int how_many, 
                                ostream& outs = cout);  //print array

template<class T>
T* search_entry(T* a, int size, const T& find_me);      //search for 'find me'

template <class T>
int search(T* a, int size, const T& find_me);           //search for 'find_me' 

template <class T>
void shift_left(T* a, int& size, int shift_here);       //shift left @ pos:
                                                        //    erases @ pos
template <class T>
void shift_left(T* a, int& size, T* shift_here);        //shift left @ pos: 
                                                        //    erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here);      //shift right: 
                                                        //      make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here);       //shift right: 
                                                        //   make a hole

template<class T>
void copy_array(T *dest, const T* src, 
                                int many_to_copy);      //copy from src to dest

template <class T>
T* copy_array(const T *src, int size);                  //return a 
                                                        //  copy of src

template <class T>
string array_string(const T *a, int size);              //return array 
                                                        //  as a string

template <class T>
bool compare_array(const T*a, const T*b, int size);

template <class T>
void append(T* a, int& size, T append_me);
//=======================================================================

template <class T>
void append(T* a, int& size, T append_me){
  
  T* a_p = a + size;
  *a_p = append_me;
  size++;
  
}


template<class T>
T* allocate(int capacity){
  assert(!(capacity<=0));
  T *new_array = new T[capacity];
  return new_array;
}            //allocate 'capacity' 
                                                        //      elements. 
                                                        //  return array

template<class T>
T* reallocate(T* a, int size, int capacity){
  assert(!(size >= capacity));
  T* new_array = allocate <T>(capacity);
  copy_array(new_array, a,size);
  delete [] a;
  return new_array;
}            //take array, resize it 
                                                        //  return new array. 
                                                        //  delete old array

template<class T>
void print_array(T* a, int size, int capacity, ostream& outs){
  T* a_p = a;
  cout << "(" << size << "/" << capacity <<") ["; 
  print(a_p, size);
  cout << setw(6) <<"]" << endl;
}    //prints 
                                                        //  (size/capacity)
                                                        //  for debugging

template <class T>
void print(T* a, unsigned int how_many, ostream& outs ){
  T* a_p = a;
  for (int i = 0; i< how_many; i++){
    cout << setw(6)  << *a_p << setw(6);
    a_p++;
    if(!(i + 1 == how_many)){
      cout << "|";
    }
  }
}  //print array

template<class T>
T* search_entry(T* a, int size, const T& find_me){
  T *a_p = a;
  assert(!(size <= 0));
  for (int i = 0; i<size; i++){
    if(*a_p == find_me){
      return a_p;
    }
    a_p++;
  }
  return NULL;
}      //search for 'find me'

template <class T>
int search(T* a, int size, const T& find_me){
  T* a_p = a;
  T* address_index = search_entry(a_p,size, find_me);
  if(!address_index) {
    return -1; 
  }
  else {
    return address_index - a_p;
  }
}           //search for 'find_me' 

template <class T>
void shift_left(T* a, int& size, int shift_here){
  T* a_p = a+shift_here;
  shift_left(a, size, a_p);
}                                                       //shift left @ pos:
                                                        //    erases @ pos
template <class T>
void shift_left(T* a, int& size, T* shift_here){
  int index = shift_here - a;
  
  //checking if the argument are invalid values
  assert(!(index >= size));
  assert(!(index < 0));
  assert(!(size <= 0));

  //a_p get the index at where the user want to shift
  //a_next_p get the index next to to where the user want to shift
  //count is the amt of time it will shift left
  T* a_p = a + index;
  T* a_next_p = a_p + 1;
  int count = size - index-1;
  const bool debug = false;
  
  for (int i = 0; i < count; i++)
  {
    if(debug) {
      cout << "shifting " << *a_next_p << " to " << *a_p << endl;
    }
    *a_p = *a_next_p;
    a_p++;
    a_next_p++;     
  }
  size--;
}                                                       //shift left @ pos: 
                                                        //    erases @ pos

template <class T>
void shift_right(T *a, int &size, int shift_here){
  T* a_p = a+shift_here;
  shift_right(a,size,a_p);
}      //shift right: 
                                                        //      make a hole

template <class T>
void shift_right(T *a, int &size, T* shift_here){
  int index = shift_here - a;
  //check for invalid input from the user
  assert(!(size <= 0));
  assert(!(index >= size));
  assert(!(index < 0));

  //count how many time we have to move it to the right
  int count = size - index;
  //a_p hold the address of the highest maximum value of the array
  //size increment bc we are shifting right and we need the space to put our maximum value into
  T* a_p = a+size;
  size++;
  bool debug = false;
  for (int i = 0; i<count;i++){
    T* iptr = a_p - 1;
    if(debug) {
      cout << "shifting " << *iptr << " to " << *shift_here << endl;
    }
    //iptr hold the address of the value behind a_p
    //change the maximum value of the array with the one below it
    //make the hole of 0
    *a_p = *iptr;
    //decrease a_p to continue shifting right
    a_p--;
  }
}       //shift right: 
                                                        //   make a hole

template<class T>
void copy_array(T *dest, const T* src, int many_to_copy){
  if(many_to_copy <= 0) {
    return;
  }
  //create a pointer that the thing it pointing at can be change aka not lose where the position is
  const T* src_p = src;
  T* dest_p = dest;
  for (int i =0; i <many_to_copy; i++, src_p++){
    //so this the equivalent to dest[i] = src[i]
    //dereference the point to the value and then set the dest to the src
    
    *dest_p = *src_p;

    dest_p++;
  }
}      //copy from src to dest

template <class T>
T* copy_array(const T *src, int size){
  const T *src_p = src;
  T * new_array = allocate <T> (size);
  copy_array(new_array,src_p,size);
  return new_array;
}                 //return a 
//  copy of src

template <class T>
string array_string(const T *a, int size){
  string array_string="";
  const T* a_p = a;
  if(typeid(*a_p) == typeid(char)){
    for(int i = 0; i<size;i++){
      array_string += *a_p;
      if(!(i + 1 == size)){ 
      array_string += " , ";
      }
      a_p++;
    }
  } else {
    for (int i =0; i<size; i++, a_p++){
      array_string+= to_string(*a_p);
      if(!(i + 1 == size)){ 
      array_string += " , ";
      }
    }
  }
  array_string += "\n";
  return array_string;
}             //return array 
                                                        //  as a string

template <class T>
bool compare_array(const T*a, const T*b, int size){
  const T *a_p = a;
  const T*b_p = b;
  for(int i = 0; i<size; i++){
    if(*a_p - *b_p != 0 ){
      cout << "array a :" <<*a_p << " and array b: " << *b_p << endl;
      return false;
    } 
  }
  return true;
}

#endif