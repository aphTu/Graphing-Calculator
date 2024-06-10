#ifndef LEFTPAREN_H
#define LEFTPAREN_H
#include <iostream>
#include "token.h"

using namespace std;
class LeftParen: public Token{
  public: 
  LeftParen(); 
  string get_type(){return _type;}
  
  private:
  string _type;

};

#endif