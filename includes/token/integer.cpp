#include "../../includes/token/integer.h"
#include <cstring>
#include <string>

Integer::Integer(double n): _data(n), Token(to_string(n)){
  _type = "int";
}

Integer::Integer (char n): Token(to_string(n)){
  _data = ((n-'0') * 1.0);
  _type = "int";
}

Integer::Integer (int n): Token(to_string(n)){
  _data = n * 1.00;
  // cout << _data << endl;
  _type = "int";
}

Integer::Integer(string n): Token(n){
  _data = stoi(n) * 1.0;
  _type = "int";  
}

double Integer::get_value(){
  return _data;
}


string Integer::get_type(){
  return _type;
}