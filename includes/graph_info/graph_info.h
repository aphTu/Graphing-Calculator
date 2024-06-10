#ifndef GRAPH_INFO_H
#define GRAPH_INFO_H
#include <iostream>
#include <SFML/Graphics.hpp>
#include "../../includes/constants.h"
#include "../../includes/shunting_yard/shunting_yard.h"
#include "../../includes/vector/vector_class.h"
#include <cmath>

using namespace std;

struct Graph_info{
  public:
  Graph_info();
  void reset_graph();
  string _equation;
  sf::Vector2f _window_dimensions, _origin, _scale, _domain, _spaces_tick;
  int _points;
  double kms;
  bool isPolar;
  
  Queue<Token*> tokenizer();
};

#endif