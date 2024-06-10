#include "plot.h"

bool double_equals(double left, double right){
  double checker = abs(left-right);
  if(0.001 >checker){
    return true;
  }
  return false;
}

Vector<sf::Vector2f> Plot::operator()(){
  // sf::Vector2f origin (564.f,406.f);
  // RPN rpn(queue);
  // double transform_x = SCREEN_WIDTH/10;
  // double transform_y = SCREEN_HEIGHT/10;
  // for(int i = -5; i <= 5; i++){
  //   double y = rpn(i);
  //   _points.push_back(sf::Vector2f(i*transform_x,y*transform_y));
  // }
  
  sf::Vector2f empty[1];
  Vector<sf::Vector2f> empty_vector(empty,1);
  _points = empty_vector;
  _points.set_size(0);

  RPN rpn(_postfix);
  // double transform_x = _info->_window_dimensions.x / (_info->_domain.y-_info->_domain.x);
  // double transform_y = _info->_window_dimensions.y / (_info->_domain.y-_info->_domain.x);
  Coordinate_translator coord(_info);
  double loop = (_info->_domain.y - _info->_domain.x)/_info->_points;

  if(_info->isPolar == true){
    for(double a = _info->_domain.x; a<=_info->_domain.y; a+=loop){
      double r = rpn(a);
      double x = r*cos(a);
      double y = r*sin(a);
      sf::Vector2f cartesian(x,y);
      _points.push_back(coord(cartesian));
    }
  } else {

    for(double i = _info->_domain.x; i <= _info->_domain.y; i+= loop){
      double y = rpn(i);
      sf::Vector2f cartesian(i,y);
      _points.push_back(coord(cartesian));
    } 

  }
  return _points;
}

Plot::Plot(){
  Queue<Token*> queue;
  queue.push(new Function("x"));
  // queue.push(new Function("sin"));
  // queue.push(new Integer("2"));
  // queue.push(new Operator("^"));
  // queue.push(new Function("x"));
  // queue.push(new Operator("*"));
  //  queue.push(new Function("x"));
  // queue.push(new Operator("*"));
  _postfix= queue;
}
Plot::Plot(Graph_info* info): _info(info), _points(1){
  // Queue<Token*> queue;
  // queue.push(new Function("x"));
  // queue.push(new Function("cos"));
  // queue.push(new Integer("2"));
  // queue.push(new Operator("^"));
  // queue.push(new Function("x"));
  // queue.push(new Operator("*"));
  //  queue.push(new Function("x"));
  // queue.push(new Operator("*"));
  ShuntingYard shuntingyard(_info->tokenizer());
  _postfix = shuntingyard.postfix();
}

void Plot::set_info(Graph_info* info){
  _info = info;
  try{
  ShuntingYard shuntingyard(_info->tokenizer());
  _postfix = shuntingyard.postfix();
  cout << _postfix << endl;
  }
  catch (Exception_handler e){
    cout << "catching it\n";
    string error = e.Report();
    throw Exception_handler(error);
  }
  
}
