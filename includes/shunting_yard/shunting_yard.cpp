#include "shunting_yard.h"

void findingLeftParen(Queue<Token*>& current_queue, Stack<Token*>& current_stack){
  Stack<Token*> looping_stack = current_stack;
  for(Stack<Token*>::Iterator it = looping_stack.begin(); it!= looping_stack.end();it++){
    // cout << "\nwtf\n";
    Token* item = *it;
    if(item->get_type() != "leftparen"){
      // cout << "this is running\n";
      current_queue.push(current_stack.pop());
      // cout << current_queue << endl;
      // cout << current_stack << endl;
    } else {
      // cout << "why you failing\n";
      current_stack.pop();
      break;
    }
  }
}

ShuntingYard::ShuntingYard(Queue<Token*> queue): _infix(queue){
  // _infix = queue;
  // _postfix;
}

ShuntingYard::ShuntingYard(): _infix(){

}

Queue<Token*> ShuntingYard::postfix(Queue<Token*> queue){
  Stack<Token*> stack;
  Queue<Token*> return_queue;
  const bool debug = false;
  for(Queue<Token*>::Iterator it = queue.begin();it!= queue.end();it++){
    Token* item = *it;
    if(debug){
      cout << "item is: ";
      item->print();
      cout << "type of item is " << item->get_type() << endl;
    }

    if(item->get_type() == "leftparen"){
      stack.push(item);
    } else if (item->get_type()=="rightparen"){
      findingLeftParen(return_queue,stack);
      continue;
    } else if (item->get_type() == "function"){
      Function* func = static_cast<Function*> (item);
      if(stack.size()!= 0){
        if(stack.top()->get_type() == "operator"){
          Operator* stack_op = static_cast<Operator*>(stack.top());
          if(func->get_priority() <= stack_op->get_priority()){
          return_queue.push(stack.pop());
          }
        } else if (stack.top()->get_type() == "function"){
         Function* stack_op = static_cast<Function*>(stack.top());
          if(func->get_priority() <= stack_op->get_priority()){
            return_queue.push(stack.pop());
          }
        }
      }
      stack.push(item);
    }
    else if(item->get_type() == "operator"){
      if(stack.size()!= 0){
        Operator* op = static_cast<Operator*>(item);
        

        if(stack.top()->get_type() == "operator"){
          Operator* stack_op = static_cast<Operator*>(stack.top());
          if(op->get_priority() <= stack_op->get_priority()){
          return_queue.push(stack.pop());
          }
        } else if (stack.top()->get_type() == "function"){
         Function* stack_op = static_cast<Function*>(stack.top());
          if(op->get_priority() <= stack_op->get_priority()){
            return_queue.push(stack.pop());
          }
        }
        // Operator* stack_op = static_cast<Operator*>(stack.top());
        // cout << "operator moment: \n";
        // cout << op->get_priority() << endl;
        // cout << stack_op->get_priority() << endl;
        // if(op->get_priority() <= stack_op->get_priority()){
        //   return_queue.push(stack.pop());
        // }
      }
      stack.push(item);
    } else {
      return_queue.push(item);
    }
    //  cout << "\n stack is: \n";
    // cout << stack << endl;
    // cout << "\n queue is \n";
    // cout << return_queue << endl;
  }

  for(Stack<Token*>::Iterator it = stack.begin(); it!= stack.end();it++){
    Token* item = *it;
    return_queue.push(item);
  }


  cout << return_queue << endl;
  return return_queue;
}


Queue<Token*> ShuntingYard::postfix(){
 try{
  Queue<Token*> postfix_queue = postfix(_infix);
  // cout << "bruh\n";
  return postfix_queue;
 }
  catch(Exception_handler e){
    // cout << "brother\n";
    cout << e.Report();
  }
}

Queue<Token*> ShuntingYard::infix(Queue <Token*> queue){
  _infix = queue;
  return _infix;
}


