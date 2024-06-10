#ifndef SHUNTING_YARD_H
#define SHUNTING_YARD_H
#include <iostream>
#include "../../includes/token/token.h"
#include "../../includes/queue/MyQueue.h"
#include "../../includes/stack/MyStack.h"
#include "../../includes/token/operator.h"
#include "../../includes/token/leftparen.h"
#include "../../includes/token/rightparen.h"
#include "../../includes/token/function.h"
#include "../../includes/exception_handling/exception_handler.h"

using namespace std;
class ShuntingYard{
  public:
  ShuntingYard();
  ShuntingYard(Queue<Token*> queue);
  Queue<Token*> postfix();
  Queue<Token*> postfix(Queue<Token*> queue);
  Queue<Token*> infix(Queue <Token*> queue);

  friend void findingLeftParen(Queue<Token*>& current_queue, Stack<Token*>& current_stack);
  private:
  // Queue<Token*> _postfix;
  Queue<Token*> _infix;
};
#endif