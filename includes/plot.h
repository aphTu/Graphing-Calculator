#ifndef PLOT_H
#define PLOT_H
#include <iostream>
#include "graph_info/graph_info.h"
#include <SFML/Graphics.hpp>
#include "vector/vector_class.h"
#include "token/token.h"
#include "queue/MyQueue.h"
#include "token/operator.h"
#include "token/function.h"
#include "rpn/rpn.h"
#include "constants.h"
#include "coordinate_translator/coordinate_translator.h"
#include "exception_handling/exception_handler.h"

using namespace std;

class Plot{
  public:
  Plot(Graph_info*);
  Plot();
  void set_info(Graph_info*);
  Vector<sf::Vector2f> operator()();
  private:
  Queue<Token*> _postfix;
  Graph_info* _info;
  Vector<sf::Vector2f> _points;
};
#endif