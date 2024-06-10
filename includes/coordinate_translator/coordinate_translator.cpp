#include "coordinate_translator.h"
Coordinate_translator::Coordinate_translator(Graph_info* graph_info){
  _info = graph_info;
}
sf::Vector2f Coordinate_translator::translator(sf::Vector2f point){
  // double transform_x = _info->_window_dimensions.x / (_info->_domain.y-_info->_domain.x);
  // double transform_y = _info->_window_dimensions.y / (_info->_domain.y-_info->_domain.x);
  
  // double new_x = point.x * _info->_scale.x * _info->_spaces_tick.x;
  // double new_y = point.y * _info->_scale.y * -1 * _info->_spaces_tick.x;
  double new_x = point.x* _info->_scale.x;
  double new_y = point.y* _info->_scale.y * -1;
  
  sf::Vector2f coord(_info->_origin.x +new_x, _info->_origin.y + new_y);

  return coord;
}
sf::Vector2f Coordinate_translator::operator()(sf::Vector2f point){
  return translator(point);
}