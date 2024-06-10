#ifndef ADD_ENTRY_H
#define ADD_ENTRY_H
#include <iostream>
#include "../../includes/array_functions/array_functions.h"

using namespace std;

template<class T>
T* add_entry(T* list, const T& new_entry,int& size, int& capacity);

template<class T>
T* remove_entry(T* list, const T& delete_me,int& size, int& capacity);

template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity);

template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size,int &capacity);

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity);

//=======================================================================

template<class T>
T* add_entry(T* list, const T& new_entry,int& size, int& capacity){
  // if(size <= 0 || capacity <= 0){
  //   delete [] list;
  //   return nullptr;cmd
  // }
  assert(!(size< 0));
  assert(!(capacity<=0));

  if(size == capacity){
    capacity = capacity*2;

    list = reallocate<T>(list, size, capacity);
  } 
  append(list,size, new_entry);
  
  return list;
}

template<class T>
T* remove_entry(T* list, const T& delete_me,int& size, int& capacity){
  int found = search(list,size,delete_me);
  assert(!(size < 0));
  assert(!(capacity <= 0));
  if(found == -1)
  {
    return list;
  }
  
  // if(size <= (capacity*1/4) && !(capacity<= 3)){
  //   capacity = capacity * 1/2;
  //   list = reallocate(list,size, capacity);
  // }
  
  // shift_left(list,size,found);
  list = erase_entry(list,found,size,capacity);
  return list;
}

template <class T>
T *remove_last_entry(T *list, T &popped, int &size, int &capacity){
  assert(!(capacity <= 0));
  assert(!(size < 0));

  T* last_index = list + size - 1;
  popped = *last_index;
  list = erase_entry(list,size-1,size,capacity);
  return list;
}

template <class T>
T *insert_entry(T *list, const T &insert_this, int insert_here, int &size,int &capacity){
  //  if(size == 0 || capacity == 0 || insert_here <0){
  //   delete[] list;
  //   return nullptr;
  //  }

   assert(!(size < 0));
   assert(!(capacity <= 0));
   assert(!(insert_here < 0));
  assert(!(insert_here>=size));


   if(size == capacity){
    capacity = capacity*2;
    list = reallocate<T>(list, size, capacity);
  }

  shift_right(list,size, insert_here);
  T * list_p = list + insert_here;
  *list_p = insert_this;
  return list;
}

template <class T>
T *erase_entry(T *list, int index, int &size, int &capacity){
  assert(!(index < 0));
  assert(!(size <0));
  assert(!(capacity <=0));


  shift_left(list,size,index);
  
  if(size <= (capacity*1/4) && !(capacity <= 3)  && !(capacity/2 <= 3)){
    capacity = capacity/2;
    list = reallocate<T>(list,size,capacity);
  }
  return list;
} 

#endif