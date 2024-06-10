#ifndef MYQUEUE_H
#define MYQUEUE_H
#include <iostream>
#include "../../includes/linked_list_functions/linked_list_functions.h"

using namespace std;
template <typename T>
class Queue
{
public:
    class Iterator{
    public:
        friend class Queue;                          //give access to list to
                                                    //          access _ptr
        Iterator(){_ptr = NULL;}                    //default ctor
        Iterator(node<T>* p){_ptr = p;}
                                                    //Point Iterator to where p
                                                    //  is pointing to
        T &operator*(){return _ptr->_item;}                             //dereference operator

        T *operator->(){return &_ptr->_item;}                           //member access operator
        bool is_null(){return _ptr == NULL;}                            //true if _ptr is NULL
        friend bool operator!=(const Iterator &left, const Iterator &right){ 
          if(left._ptr!= right._ptr){
            return true;
          }
          return false;
        } //true if left != right

        friend bool operator==(const Iterator &left, const Iterator &right){
          if(left._ptr == right._ptr){
            return true;
          }
          return false;
        } //true if left == right

        Iterator &operator++(){
          _ptr=_ptr->_next;
          return *this;
        }                         //member operator:
                                                        //  ++it; or
                                                        //  ++it = new_value

        friend Iterator operator++(Iterator &it,
                                   int unused){
          Iterator hold = it;
          it._ptr= it._ptr->_next;
          return hold;

        }          //friend operator: it++

    private:
        node<T>* _ptr;                          //pointer being encapsulated
    };

    Queue();

    Queue(const Queue<T>& copyMe);
    ~Queue();
    Queue& operator=(const Queue<T>& RHS);

    bool empty();
    T front();
    T back();

    void push(T item);
    T pop();

    Iterator begin() const;            //Iterator to the head node
    Iterator end() const;              //Iterator to NULL
    void print_pointers();
    int size() const { return _size; }
    template<typename TT>
    friend ostream& operator << (ostream& outs, const Queue<TT>& printMe);
private:
    node<T>* _front;
    node<T>* _rear;
    int _size;
};

//--------------------------------------------------------------------------------------------------------//
template <class T>
Queue<T>::Queue(){
  _front = nullptr;
  _rear = nullptr;
  _size = 0;
}

template <class T>
Queue<T>::Queue(const Queue<T>& copyMe){
  _size  = copyMe._size;
  _rear = _copy_list(_front,copyMe._front);
}


template <class T>
Queue<T>::~Queue(){
  _size = 0;
  _rear = nullptr;
  _clear_list(_front);
}

template <class T>
Queue<T>& Queue<T>::operator=(const Queue<T>& RHS){
   if(this == &RHS){
    return *this;
  }
  
  _size = RHS._size;
  if(_front!= nullptr){
    _clear_list(_front);
  }

  _rear = _copy_list(_front,RHS._front);
  return*this;
}

template <class T>
bool Queue<T>::empty(){
  return _front == nullptr;
}

template <class T>
T Queue<T>::front(){
  return _front->_item;
}

template <class T>
T Queue<T>::back(){
  // _print_list(_rear);
  T value = _rear->_item;
  // cout << value << endl;
  return value;
}

template <class T>
void Queue<T>::push(T item){
  node<T>* temp = nullptr;
//   if(_front == nullptr){
//     _rear = _insert_head(_front,item);
//   } else {
//  _rear = _insert_before(_front,temp,item);
//   }
  _rear = _insert_after(_front,_rear,item);
  // _rear = _front;
  // node<T>* w = _front;
  _size++;
}

template <class T>
T Queue<T>::pop(){
  T pop_value = _delete_node(_front,_front);
  _size--;
  return pop_value;
}

template <class T>
typename Queue<T>::Iterator Queue<T>::begin() const{
  Iterator p = _front;
  return p;
}            //Iterator to the head node

template <class T>
typename Queue<T>::Iterator Queue<T>::end() const{
  Iterator p = NULL;
  return p;
}             //Iterator to NULL

template <class T>
void Queue<T>::print_pointers(){
  _print_list(_front);
}

template<typename TT>
ostream& operator << (ostream& outs, const Queue<TT>& printMe){
  node<TT>* w = printMe._front;
  while(w!= nullptr){
    cout << *w << "->";
    w=w->_next;
  }
  cout <<"{null}"  << endl;
  return outs;
}
#endif