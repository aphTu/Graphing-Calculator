#ifndef MYSTACK_H
#define MYSTACK_H
#include <iostream>
#include "../../includes/linked_list_functions/linked_list_functions.h"

using namespace std;
template <typename T>
class Stack{
public:
    class Iterator{
    public:
        friend class Stack;                          //give access to list to
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

    Stack();
    Stack(const Stack<T>& copyMe);
    ~Stack();
    Stack<T>& operator=(const Stack<T>& RHS);
    T top();
    bool empty();
    void push(T item);
    T pop();
    template<typename TT>
    friend ostream& operator<<(ostream& outs, 
                                        const Stack<TT>& printMe);

    Iterator begin() const;              //Iterator to the head node
    Iterator end() const;                //Iterator to NULL
    int size() const { return _size; }

private:
    node<T>* _top;
    int _size;
};

//----------------------------------------------------------------------------------//
template <class T>
Stack<T>::Stack(){
  _size = 0;
  _top = nullptr;
}

template <class T>
Stack<T>::Stack(const Stack<T>& copyMe){
  _size  = copyMe._size;
  _top = _copy_list(copyMe._top);
}

template <class T>
Stack<T>::~Stack(){
  _clear_list(_top);
  _size = 0;
}

template <class T>
Stack<T>& Stack<T>::operator=(const Stack<T>& RHS){
  if(this == &RHS){
    return *this;
  }
  
  _size = RHS._size;
  if(_top!= nullptr){
    _clear_list(_top);
  }

  _top = _copy_list(RHS._top);
  return*this;
}

template <class T>
T Stack<T>::top(){
  return _top->_item;
}

template <class T>
bool Stack<T>::empty(){
  return _top == nullptr;
}

template <class T>
void Stack<T>::push(T item){
  _insert_head(_top,item);
  _size++;
}

template <class T>
T Stack<T>::pop(){
  T value = _delete_node(_top,_top);
  --_size;
  return value;
}

template<typename TT>
ostream& operator<<(ostream& outs, const Stack<TT>& printMe){
   node<TT>* w = printMe._top;
  while(w!= nullptr){
    cout << *w << "->";
    w=w->_next;
  }
  cout <<"{null}"  << endl;
  return outs;
}

template<class T>
typename Stack<T>::Iterator Stack<T>::begin() const{
  Iterator p = _top;
  return p;
}             //Iterator to the head node

template <class T>
typename Stack<T>::Iterator Stack<T>::end() const{
  Iterator p = NULL;
  return p;
}               //Iterator to NULL
#endif