#ifndef COORDINATE_TRANSLATOR_H
#define COORDINATE_TRANSLATOR_H
#include <iostream>
#include "../../includes/graph_info/graph_info.h"
#include "../../includes/vector/vector_class.h"

using namespace std;

class Coordinate_translator{
  public:
  Coordinate_translator(Graph_info* graph_info);
  sf::Vector2f translator(sf::Vector2f point);
  sf::Vector2f operator()(sf::Vector2f point);
  private: 
  Graph_info* _info;
};

#endif