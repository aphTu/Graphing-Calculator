#ifndef INTEGER_H
#define INTEGER_H
#include <iostream>
#include "token.h"

using namespace std;

class Integer: public Token{
  public:
  Integer(double n);
  Integer (char n);
  Integer (string n);
  Integer (int n);
  string get_type();
  double get_value();

  private:
  double _data;
  string _type;
};


#endif