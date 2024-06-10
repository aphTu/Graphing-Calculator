#ifndef RIGHTPAREN_H
#define RIGHTPAREN_H
#include <iostream>
#include "token.h"

using namespace std;

class RightParen: public Token{
  public: 
  RightParen(); 
  string get_type(){return _type;}
  
  private:
  string _type;
};

#endif