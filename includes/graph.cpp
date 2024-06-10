#include "graph.h"

Graph::Graph(Graph_info* graph_info): _plotter(graph_info){
  _info = graph_info;
}

Graph::Graph(){
  _info = nullptr;
}


void Graph::update(){
  // sf::Vector2f position(0.f,795.f);
  // _points.push_back(position);
  // sf::Vector2f position2(230.f,594.f);
  // _points.push_back(position2);
  // sf::Vector2f position3(560.f,400.f);
  // _points.push_back(position3);
  // sf::Vector2f position4(702.f,270.f);
  // _points.push_back(position4);
  // sf::Vector2f position5(1105.f,0.f);
  // _points.push_back(position5);
  try{
  _points = _plotter();
  }
   catch(Exception_handler e){
    throw Exception_handler(e.Report());
   }
}

void Graph::draw(sf::RenderWindow& window){
  for(double i = 0; i < _points.size(); i+=1){
    sf::CircleShape circle(3.f);
    circle.setFillColor(sf::Color(177,162,202));
    // circle.center
    // circle.setOrigin(sf::Vector2f(564.f,406.f));
    // circle.setPosition(_info->_origin + _points[i] - sf::Vector2f(3.f,3.f));
    circle.setPosition(_points[i] -sf::Vector2f(3.f,3.f) );
    window.draw(circle);
  }
}

void Graph::set_info(Graph_info* info){
  _info = info;
  try{
  _plotter.set_info(info);
  } 
  catch(Exception_handler e){
    throw Exception_handler(e.Report());
  }
  // cout << "equation from graph set_info: " << _info->_equation << endl;
}