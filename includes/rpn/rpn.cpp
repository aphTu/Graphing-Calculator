#include "../../includes/rpn/rpn.h"

RPN::RPN(Queue<Token*> queue){
  Queue<Token*>::Iterator  q_it= queue.begin();
  for(; q_it != queue.end(); q_it++){
    the_queue.push(*q_it);
  }
}


double RPN::operator()(double n){
  double result;
  int size = the_queue.size();
  Stack<Token*> stack_calculation;
  
  for(Queue<Token*>::Iterator it = the_queue.begin(); it!= the_queue.end(); it++){
    string type = (*it)->get_type();
    // cout << "type: " << type << endl;
    // (*it)->print();
    if(type == "function"){
      Function* func = static_cast<Function*>(*it);
      if(func->get_value_1() != "X" && func->get_value_1() != "x" && func->get_value_1()!="e" ){
        Integer* value = static_cast<Integer*> (stack_calculation.pop());
        try{
          double answer = func->eval(*value);
          stack_calculation.push(new Integer(answer));
        }
        catch(Exception_handler e){
          cout << e.Report();
        }
      } else {
        try{
          double answer = func->eval(Integer(n));
          stack_calculation.push(new Integer(answer));
        } 
        catch(Exception_handler e){
          cout << e.Report();
        }
      }
    } 
    else if(type == "operator"){
      Operator* op = static_cast<Operator*>(*it);
      Integer* b = static_cast<Integer*> (stack_calculation.pop());
      Integer*a = static_cast<Integer*> (stack_calculation.pop());
      // cout << "bruh moment\n";
        result = op->eval(*a,*b);
      stack_calculation.push(new Integer(result));
    } 
    else {
      stack_calculation.push(*it);
    }
    // cout << stack_calculation << endl;
  }

  if(stack_calculation.size() != 1) throw Exception_handler("stack was not clear");
  return (static_cast<Integer*>(stack_calculation.top())->get_value());
}
 
void RPN::set_input(Queue<Token*> queue){
  the_queue.~Queue();
  Queue<Token*>::Iterator  q_it= queue.begin();
  for(; q_it != queue.end(); q_it++){
    the_queue.push(*q_it);
  }
}


double rpn_functions(Stack<Token*>& stack){
  
  double result;
  if(stack.top()->get_type() == "operator"){
    Operator* op = static_cast<Operator*>(stack.pop());
    Integer* a = static_cast<Integer*>(stack.pop());
    Integer* b = static_cast<Integer*>(stack.pop());
    result = op->eval(*a,*b);
  }
  return result;
}
