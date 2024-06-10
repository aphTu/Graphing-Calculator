#include "function.h"

Function::Function(string data): Token(data){
  _type = "function";
  _data = data;
  _arg = 1;
  _priority = 9;
}

// Function::Function(string a, string b): Token(a+ " " +b){
//   _data = a;
//   _data2 =b;
//   _arg = 2;
// }
string Function::get_type(){
  return _type;
}

int Function::get_priority(){
  return _priority;
}


double Function::eval(Integer a){
  if(_data == "x" || _data == "X"){
    return a.get_value();
  } else if (_data == "sin"){
    return sin(a.get_value());
  } else if (_data == "cos"){
    return cos(a.get_value());
  } else if (_data == "tan"){
    return tan(a.get_value());
  } else if (_data == "ln"){
  
    if(a.get_value() == 0) throw Exception_handler("ln of 0");
  
    return log10(a.get_value());
  } else if (_data == "arccos"){
    return acos(a.get_value());
  } else if (_data == "arcsin"){
    return asin(a.get_value());
  } else if (_data == "arctan"){
    return atan(a.get_value());
  } else if (_data == "sinh"){
    return sinh(a.get_value());
  } else if (_data=="cosh"){
    return cosh(a.get_value());
  } else if (_data == "tanh"){
    return tanh(a.get_value());
  } else if (_data == "e"){
    return exp(1);
  }
}
