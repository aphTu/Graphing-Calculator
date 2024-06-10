#ifndef FUNCTION_H
#define FUNCTION_H
#include <iostream>
#include "token.h"
#include "integer.h"
#include "../../includes/exception_handling/exception_handler.h"
#include <cstring>
#include <string>
#include <cmath>

using namespace std;
class Function: public Token{
  public:
  Function(string data);
  double eval(Integer a);
  Integer eval(Integer a, Integer b);
  string get_value_1(){return _data;}
  string get_type();
  int get_priority();
  private:
  string _data;
  string _data2;
  string _type;
  int _arg;
  int _priority;
};

#endif