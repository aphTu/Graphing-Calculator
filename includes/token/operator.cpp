#include "../../includes/token/operator.h"
#include <cstring>
#include <string>

Operator::Operator(char op): Token(to_string(op)){
  _data = op;
  _type = "operator";
  set_priority_for_var();
}

Operator::Operator(string op): Token(op){
  _data = op[0];
  _type = "operator";
  set_priority_for_var();
}

string Operator::get_type(){
  return _type;
}

double Operator::eval(Integer right, Integer left){
  double result = 0;
  if(_data == '+'){
    result = right.get_value() + left.get_value();
  } else if (_data == '-'){
    result = right.get_value() - left.get_value();
  } else if (_data == '*'){
    result = right.get_value() * left.get_value();
  } else if (_data == '/'){
    result = right.get_value() / left.get_value();
  } else if (_data == '^'){
    result = pow(right.get_value(),left.get_value());
    // cout << "result: " << result << endl;
    // cout << "right: " << right.get_value() << endl;
    if(right.get_value() == 0){
      result = 0;
    }
  }
  return result;
}


void Operator::set_priority_for_var(){
  if(_data == '+' || _data == '-'){
    _priority = 1;
  } else if (_data == '*' || _data == '/'){
    _priority = 2;
  } else if (_data == '^'){
    _priority = 3;
  }
}
