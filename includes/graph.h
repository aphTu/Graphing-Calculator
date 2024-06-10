#ifndef GRAPH_H
#define GRAPH_H
#include "iostream"
#include "graph_info/graph_info.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "plot.h"
#include "rpn/rpn.h"
#include "vector/vector_class.h"



using namespace std;

class Graph{
  public:
  Graph();
  Graph(Graph_info* graph_info);
  void set_info(Graph_info*);
  void update();
  void draw(sf::RenderWindow& widnow);

  private:
  Graph_info* _info;
  Vector<sf::Vector2f> _points;
  Plot _plotter;
};

#endif