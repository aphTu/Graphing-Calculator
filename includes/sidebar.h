#ifndef SIDEBAR_H
#define SIDEBAR_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstring>
#include <string>
#include <vector>
#include <fstream>
#include "graph_info/graph_info.h"
#include "vector/vector_class.h"
// #include "../../includes/add_entry/add_entry.h"
using namespace std;


class Sidebar
{
public:
    Sidebar();
    Sidebar(float left, float width);
    sf::RectangleShape return_rect(){return rect;}
    Vector<sf::Vector2f> return_pos(){return sidebar_pos_vect;}
    void draw(sf::RenderWindow& window);
    void get_history();
    void add_history(string equation);
    void write_history();
    // void set_info(Graph_info* info){_info = info;}
    string& operator [](int index);
private:
    sf::RectangleShape rect;            //sidebar rectangle
    vector<string> items;               //strings to place on the sidebar
    sf::Font font;                      //used to draw text
    sf::Text sb_text;                   //used to draw strings on the window object
    float _left;
    float _width;
    Vector<sf::Vector2f> sidebar_pos_vect;
    // Graph_info* _info;

};

#endif // SIDEBAR_H
