#ifndef EXCEPTION_HANDLER_H
#define EXCEPTION_HANDLER_H
#include <iostream>

using namespace std;

class Exception_handler{
  public: 
  Exception_handler(string error){_error = error;}
  string Report(){return _error;}
  
  private:
  string _error;
};

#endif