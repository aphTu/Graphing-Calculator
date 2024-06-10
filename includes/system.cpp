#include "system.h"
#include "random.h"

#include <iostream>

#include "constants.h"
System::System(): _graph()
{
    Random r;
    int xpos = 100;
    int ypos = 100;
    //the shape of the object, along with its velocity, acceleration,
    //position, etc. should be part of the individual object.
    shape = sf::CircleShape(10);
    shape.setPosition(sf::Vector2f(xpos, ypos));
    vel = sf::Vector2f(r.Next(-5,5), r.Next(-5,5)); //random velocity
    int r_ = r.Next(0,255);
    int g_ = r.Next(0,255);
    int b_ = r.Next(0,255);
    shape.setFillColor(sf::Color(r_, g_, b_));
}


//------------------------------------------------------------------
//------------------------------------------------------------------

void System::Step(int command, sf::RenderWindow& window){

        //all this is the responsibility of the
        // individual object:
        shape.move(vel);
        sf::Vector2f pos = shape.getPosition();
        if ((pos.x)>=WORK_PANEL-20)
            vel = sf::Vector2f(-1*vel.x,1*vel.y);
        if (pos.x<=0)
            vel = sf::Vector2f(-1*vel.x,1*vel.y);
        if ((pos.y)>=SCREEN_HEIGHT-20)
            vel = sf::Vector2f(1*vel.x,-1*vel.y);
        if (pos.y<=0)
            vel = sf::Vector2f(1*vel.x,-1*vel.y);
        

        //1 is zoom in
        //2 is zoom out
        //3 is up arrow
        //4 is left arrow
        //5 is down arrow
        //6 is right arrow
        
        if(command ==1){
            //ZOOM IN
            
            // double scale_amt = _info->_scale.y/2;
            // _info->_scale.x+= scale_amt;
            // _info->_scale.y+= scale_amt;
            // _info->_spaces_tick.y+= scale_amt;
            if(_info->isPolar==true){
                double scale_amt = 3.14159/16;
                // _info->_domain.x= scale_amt;
                _info->_domain.y-=scale_amt;
                _info->kms +=scale_amt;
                _info->_scale.x = _info->_window_dimensions.x/(_info->_domain.y-_info->_domain.x);
                _info->_scale.y = _info->_window_dimensions.y/(_info->_domain.y-_info->_domain.x);
            }else {
                double scale_amt = 0.90;
                _info->_domain.x*= scale_amt;
                _info->_domain.y*=scale_amt;
                _info->kms /=scale_amt;
                _info->_scale.x = _info->_window_dimensions.x/(_info->_domain.y-_info->_domain.x);
                _info->_scale.y = _info->_window_dimensions.y/(_info->_domain.y-_info->_domain.x);
            }
            
        }

        if(command == 2){
            //ZOOM OUT
            
            // double amt= _info->_domain.y/2;
            // _info->_domain.x-=amt;
            // _info->_domain.y+=amt;
            // _info->_scale.x-= amt;
            // _info->_scale.y-=amt;
            if (_info->isPolar == true){
                double scale_amt = 3.14159/16;
                // _info->_domain.x/=scale_amt;
                _info->_domain.y+=scale_amt;
                _info->kms -= scale_amt;
                _info->_scale.x = _info->_window_dimensions.x/(_info->_domain.y-_info->_domain.x);
                _info->_scale.y = _info->_window_dimensions.y/(_info->_domain.y-_info->_domain.x);

            }else {
                double scale_amt = 0.90;
                _info->_domain.x/=scale_amt;
                _info->_domain.y/=scale_amt;
                _info->kms *= scale_amt;
                _info->_scale.x = _info->_window_dimensions.x/(_info->_domain.y-_info->_domain.x);
                _info->_scale.y = _info->_window_dimensions.y/(_info->_domain.y-_info->_domain.x);

            }
            
            
            // _info->_spaces_tick.y-= amt;
        
        }

        if(command == 4){
            //LEFT ARROW
            
            if(_info->isPolar == true){
                // _info->_domain.x-=3.14159/(_info->kms*2);
                // _info->_domain.y-=3.14159/(_info->kms*2);
                _info->_origin.x+= (_info->_scale.x/ _info->kms);  
            }else {
                _info->_domain.x-=1/_info->kms;
                _info->_domain.y-=1/_info->kms;
                _info->_origin.x+= (_info->_scale.x/ _info->kms);  
            }

            // _info->_domain.x-=1/_info->kms;
            // _info->_domain.y-=1/_info->kms;
            // _info->_origin.x+= (_info->_scale.x/ _info->kms);
        }
        
        if(command == 3){
            _info->_origin.y+=(_info->_scale.y/_info->kms);
        }

        if(command == 5){
            _info->_origin.y-=(_info->_scale.y/_info->kms);
        }
        if(command ==6){
            //RIGHT ARROW


            if(_info->isPolar == true){
                // _info->_domain.x+=3.14159/(_info->kms*2);
                // _info->_domain.y+=3.14159/(_info->kms*2);
                _info->_origin.x-=(_info->_scale.x / _info->kms);
            }else {
                _info->_domain.x+=1/_info->kms;
                _info->_domain.y+=1/_info->kms;
                _info->_origin.x-=(_info->_scale.x / _info->kms);
            }
        
            // _info->_domain.x+=1/_info->kms;
            // _info->_domain.y+=1/_info->kms;
            // _info->_origin.x-=(_info->_scale.x / _info->kms);
        }

        //7 is text input
        if(command == 7){
            _display_text_box = true;
        }
        if(command == 8){
            _display_text_box = false;
        }
        if(command == 9){
            _info->reset_graph();
        }
        if(command!=0){
            try{
             _graph.update();
             cout << _info->_domain.x << ", " << _info->_domain.y << endl;
            }
            catch(Exception_handler e){
                // cout << "catching it\n";
                // _info->_equation = "1000000";
                // _graph.update();
                // cout << e.Report();
                throw Exception_handler(e.Report());
            }
        }
        
}

void System::set_info(Graph_info* info){
    try{
    _graph.set_info(info);
    _info = info;

    }
    catch(Exception_handler e){
        cout << e.Report();
        _info = info;
        _info->_equation= "x";
        throw Exception_handler(e.Report());
        
    }

    cout << _info->_equation << endl;
    // _graph.update();
}

void System::Draw(sf::RenderWindow& window){
    // window.draw(shape);
    window.clear(sf::Color(46,26,71));
    sf::RectangleShape x(sf::Vector2f(1.f,_info->_window_dimensions.x));
    sf::RectangleShape y(sf::Vector2f(1.f,_info->_window_dimensions.y));
    x.setFillColor(sf::Color(187,41,187));
    y.setFillColor(sf::Color(187,41,187));
    x.setPosition(sf::Vector2f(0,_info->_origin.y));
    x.setOrigin(x.getSize());
    x.rotate(90);

    y.setPosition(sf::Vector2f(_info->_origin.x,0));
    window.draw(x);
    window.draw(y);
    _graph.draw(window);
    // cout << "this is firing\n";
}

void System::update(Graph_info* info){
    _info = info;
    try{
        _graph.set_info(info);
    } 
    catch(Exception_handler e){
        throw Exception_handler(e.Report());
    }
    // cout << _info->get
}