#ifndef RPN_H
#define RPN_H
#include <iostream>
#include "../../includes/token/integer.h"
#include "../../includes/token/operator.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/token/function.h"
#include "../../includes/exception_handling/exception_handler.h"

using namespace std;

class RPN{
  public:
  RPN(Queue<Token*> queue);
  double operator()(double n=0);
  void set_input(Queue<Token*> queue);

  private:
  Queue<Token*> the_queue;
};

double rpn_functions(Stack<Token*>& stack);

#endif