#ifndef SYSTEM_H
#define SYSTEM_H
#include <vector>
#include <SFML/Graphics.hpp>
#include "graph.h"

using namespace std;
class System
{
public:
    System();
    void Step(int command, sf::RenderWindow& window);
    void set_info(Graph_info* info);
    int Size();
    void Draw(sf::RenderWindow& widnow);
    void update(Graph_info* info);
    bool get_display_text_box(){return _display_text_box;}
private:
//    vector<Particle> system;
    sf::CircleShape shape;
    sf::Vector2f vel;
    Graph _graph;
    Graph_info* _info;
    bool _display_text_box;
};

#endif // SYSTEM_H
