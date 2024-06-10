#ifndef LINKED_LIST_FUNCTIONS_H
#define LINKED_LIST_FUNCTIONS_H
#include "assert.h"
#include "../../includes/node/node.h"


 //Linked List General Functions:
    template <typename ITEM_TYPE>
    void _print_list(node<ITEM_TYPE>* head);

    //recursive fun! :)
    template <typename ITEM_TYPE>
    void _print_list_backwards(node<ITEM_TYPE> *head);

    //return ptr to key or NULL
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,
                                ITEM_TYPE key);


    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,
                                ITEM_TYPE insert_this);

    //insert after ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,
                                 node<ITEM_TYPE> *after_this,
                                 ITEM_TYPE insert_this);

    //insert before ptr
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head,
                                  node<ITEM_TYPE>* before_this,
                                  ITEM_TYPE insert_this);

    //ptr to previous node
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head,
                                  node<ITEM_TYPE>* prev_to_this);

    //delete, return item
    template <typename ITEM_TYPE>
    ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head,
                         node<ITEM_TYPE>* delete_this);

    //duplicate the list...
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head);

    //duplicate list and return the last node of the copy
    template <typename T>
    node<T> *_copy_list(node<T>* &dest, node<T> *src);


    //delete all the nodes
    template <typename ITEM_TYPE>
    void _clear_list(node<ITEM_TYPE>*& head);

    //_item at this position
    template <typename ITEM_TYPE>
    ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos);

    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
    //      Sorted List Routines. order: 0: ascending, order: other: descending
    //                              Assume a Sorted List
    //. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head,       //insert
                                  ITEM_TYPE item,
                                  bool ascending=true);

    //insert or add if a dup
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,
                                          ITEM_TYPE item,
                                          bool ascending=true);
    //node after which this item goes order: 0 ascending
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,
                                   ITEM_TYPE item,
                                   bool ascending=true);
    //Last Node in the list
    template <typename ITEM_TYPE>
    node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head);            //never use this function.


//-------------------------------------------------------------------------------------------//

template <typename ITEM_TYPE>
void _print_list(node<ITEM_TYPE>* head){
  node<ITEM_TYPE>* w = head;
  const bool debug = false;
  int count = 0;
  while(w != nullptr){
    cout << *w << " -> ";
    w= w->_next;
    count++;  
    if(debug){
      cout << "count: " << count << endl;
      cout << "w->_next: " << w->_next << endl;
      cout << "w: " << w << endl;
    }
  }

  cout << "{null}" << endl;
  if(debug){
    cout << "ran this many time: "<< count << endl;
  }  
}

//recursive fun! :)
template <typename ITEM_TYPE>
void _print_list_backwards(node<ITEM_TYPE> *head){

}

//return ptr to key or NULL
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _search_list(node<ITEM_TYPE>* head,ITEM_TYPE key){
  // assert(!(head== nullptr));
  node <ITEM_TYPE>* w = head;
  const bool debug = false;
  int count = 0;

  while(w != nullptr){
    if(debug){
      cout << "checking if " << w->_item << " is equal to " << key << endl; 
    }
    if(w->_item == key){
      if(debug){
        cout << "key is at this index: " << count<< endl;
      }
      
      return w;
    } 
    w = w->_next;
  }

  if(debug){
    cout << "loop ran this many time: " << count << endl;
  }
  return nullptr;
}


template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_head(node<ITEM_TYPE> *&head,ITEM_TYPE insert_this){
  const bool debug = false;
  node<ITEM_TYPE>* temp = new node<ITEM_TYPE>;
  temp->_item = insert_this;
  if(debug){
    cout << "item in temp: " << *temp << endl;
  }
  
  temp->_next = head;

  if(debug){
    cout << "making sure temp hold the address head previously held\n";
    cout << "temp holding: " << temp->_next << endl;
    cout << "head: " << head << endl;
  }

  head=temp;

  if(debug){
    cout << "making sure temp address (" << temp << ") is inside of head: " << head << endl;
  }
  return head;
  
}

//insert after ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_after(node<ITEM_TYPE>*& head,node<ITEM_TYPE> *after_this, ITEM_TYPE insert_this){
  int count = 0;

  if(head==nullptr || after_this == nullptr){
    head = _insert_head(head,insert_this);
    return head;
  }
  node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);
  temp->_next = after_this->_next;
  after_this->_next = temp;
  return temp;
}

//insert before ptr
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_before(node<ITEM_TYPE>*& head, node<ITEM_TYPE>* before_this,ITEM_TYPE insert_this){
  assert(!(head==nullptr));
  assert(!(before_this == nullptr));
  if(before_this == head){
    head = _insert_head(head,insert_this);
    return head;
  }
  

  node<ITEM_TYPE>* before = _previous_node(head,before_this);
  node<ITEM_TYPE>* temp = new node<ITEM_TYPE>(insert_this);

  temp->_next = before_this;
  before->_next = temp;
  
  return temp;
}

//ptr to previous node
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _previous_node(node<ITEM_TYPE>* head, node<ITEM_TYPE>* prev_to_this){
  assert(!(head==nullptr));
  int count = 0;
  node<ITEM_TYPE>* w = head;
  while(w!= nullptr){
    if(w->_next == prev_to_this){
      return w;
    }

    w=w->_next;
    count++;
  }

  return nullptr;
}

//delete, return item
template <typename ITEM_TYPE>
ITEM_TYPE _delete_node(node<ITEM_TYPE>*&head, node<ITEM_TYPE>* delete_this){
  // assert(!(delete_this == nullptr));
  // cout << "deleting value: " << endl;
  node<ITEM_TYPE>* before = _previous_node(head,delete_this);
  ITEM_TYPE value = delete_this->_item;
  // cout << value << endl;
  if(delete_this == head){
    head = delete_this->_next;
  } else { 
    before->_next = delete_this->_next;
  }

  // _print_list(head);
  delete delete_this;
  return value;
}

//duplicate the list...
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _copy_list(node<ITEM_TYPE>* head){
   if(head==nullptr){
    return nullptr;
  }

  node<ITEM_TYPE>* w = head->_next;
  node<ITEM_TYPE>* return_head = new node<ITEM_TYPE>(head->_item);
  int count = 0;
  node<ITEM_TYPE>* after_this = return_head;
  
  const bool debug = false;
  while(w!=nullptr){

    if(debug){
      cout << "count: " << count << endl;
    }
    // if(count != 0){
    //   ITEM_TYPE value = _at(return_head,count-1);
    //   after_this = _search_list(return_head,value);
    //     if(debug){
    //     cout << "value: " << value << endl;
    //   }
    //   node<ITEM_TYPE>* temp = _insert_after(return_head,after_this,w->_item);
      
    // } else {
    //   return_head = _insert_after(return_head,after_this,w->_item);
    // }

    // ITEM_TYPE value = _at(return_head,count);
    // after_this = _search_list(return_head,value);
    // if(debug){
    //   cout << "value at the last node: " << value << endl;
    //   cout << "value inserting: " << w->_item << endl;
    // }
    after_this = _insert_after(return_head,after_this,w->_item);
    w=w->_next;
    count++;
  }

  return return_head;
}

//duplicate list and return the last node of the copy
template <typename T>
node<T> *_copy_list(node<T>* &dest, node<T> *src){
  dest = _copy_list(src);
  const bool debug = false;
  node<T>* w = dest;
  int count = 0;
  while(w->_next != nullptr){
    if(debug){
      cout << "count: " << count << endl;
    }
    w=w->_next;
    count++;
  }

  return w;
}


//delete all the nodes
template <typename ITEM_TYPE>
void _clear_list(node<ITEM_TYPE>*& head){
  // assert(!(head == nullptr));
  node<ITEM_TYPE>* w = head;
  const bool debug = false;
  int count =1;
  while(w != nullptr){
    node<ITEM_TYPE>* next_w = w->_next;
    node<ITEM_TYPE> temp =  _delete_node(head,w);
    w = next_w;
    if(debug){
      cout << "count: " << count << endl;
    }
    count++;
  }

}

//_item at this position
template <typename ITEM_TYPE>
ITEM_TYPE& _at(node<ITEM_TYPE>* head, int pos){
  assert(!(head== nullptr));
  assert(!(pos < 0));
  int count =0;
  const bool debug = false;
  node<ITEM_TYPE>* w = head;
  while(w!= nullptr){
    
    if(count == pos){
      break;
    }
    if(debug){
      cout << "count: " << count << endl;
      // cout << "w: " << w << endl;
      // cout << "w->_next: " << w->_next << endl;
      cout << "w->_item: " << w->_item << endl;
      cout << "pos: " << pos << endl;
    }

    count++;
    w= w->_next;
  }

  assert(!(w==nullptr));
  return w->_item;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
//      Sorted List Routines. order: 0: ascending, order: other: descending
//                              Assume a Sorted List
//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted(node<ITEM_TYPE>* &head, ITEM_TYPE item, bool ascending){
  
  if(ascending == true){
    node<ITEM_TYPE>* after_this = _where_this_goes(head,item,ascending);
    node<ITEM_TYPE>* temp = _insert_after(head,after_this,item);
    return temp;
  } else {
    node<ITEM_TYPE>* after_this = _where_this_goes(head,item,ascending);
    node<ITEM_TYPE>* temp = _insert_after(head,after_this,item);
    // _print_list(head);
    return temp;
  }
} //insert

//insert or add if a dup
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _insert_sorted_and_add(node<ITEM_TYPE>* &head,ITEM_TYPE item, bool ascending){
  node<ITEM_TYPE>* value = _search_list(head,item);
  if(value == nullptr){
    value = _insert_sorted(head,item,ascending);
  } else {
    value->_item = value->_item + item;
    // cout << value->_item << endl;
  }
  return value;
}
//node after which this item goes order: 0 ascending
template <typename ITEM_TYPE>
node<ITEM_TYPE>* _where_this_goes(node<ITEM_TYPE>* head,ITEM_TYPE item,bool ascending){
  if(head==nullptr){
    return head;
  }

  bool debug = true;
  int count = 0;
  node<ITEM_TYPE>* leader_w = head;
  node<ITEM_TYPE>* follower_w = nullptr;

  while(leader_w!= nullptr){
    if(ascending == true){
      if(leader_w->_item > item){
        // if(debug){
        //   cout << "follower_w item: " << follower_w->_item << endl;
        // }
        return follower_w;
      }
    } else {
      if(leader_w->_item < item){
        // if(debug){
        //   cout << "follower_w item: " << follower_w->_item << endl;
        // }
        return follower_w;
      }
    }

    follower_w = leader_w;
    leader_w = leader_w ->_next;
    count++;
  }
  return follower_w;
}
//Last Node in the list

template <typename ITEM_TYPE>
node<ITEM_TYPE>* _last_node(node<ITEM_TYPE>* head){
  assert(!(head==nullptr));
  node<ITEM_TYPE>* w = head->_next;
  while(w!=nullptr){
    w = w->_next;
  }

  return w;
}           //never use this function.
#endif