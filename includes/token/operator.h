#ifndef OPERATOR_H
#define OPERATOR_H
#include <iostream>
#include "../../includes/token/token.h"
#include "../../includes/token/integer.h"
#include "../../includes/exception_handling/exception_handler.h"
#include <cmath>

using namespace std;

class Operator: public Token{
  public:
  Operator(char op);
  Operator(string op);
  string get_type();
  char get_value(){return _data;}  
  double eval(Integer right, Integer left);
  int get_priority(){return _priority;}
  void set_priority_for_var();


  private:
  char _data;
  string _type;
  int _priority;
};

#endif