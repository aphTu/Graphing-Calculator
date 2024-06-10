#include "animate.h"
#include "constants.h"
#include <iostream>
using namespace std;
#include "system.h"

bool check_first_box(sf::RenderWindow& window, Sidebar sidebar){
    sf::RectangleShape _sidebar = sidebar.return_rect();
    Vector<sf::Vector2f> pos_vect = sidebar.return_pos();
    if(sf::Mouse::getPosition(window).x >= _sidebar.getGlobalBounds().left&& sf::Mouse::getPosition(window).x <= _sidebar.getLocalBounds().width + _sidebar.getGlobalBounds().left && sf::Mouse::getPosition(window).y >= pos_vect[1].y && sf::Mouse::getPosition(window).y <= pos_vect[1].y+40 ){
        return true;
    }
    return false;
}

bool check_second_box(sf::RenderWindow& window, Sidebar sidebar){
     sf::RectangleShape _sidebar = sidebar.return_rect();
    Vector<sf::Vector2f> pos_vect = sidebar.return_pos();
     if(sf::Mouse::getPosition(window).x >= _sidebar.getGlobalBounds().left&& sf::Mouse::getPosition(window).x <= _sidebar.getLocalBounds().width+_sidebar.getGlobalBounds().left && sf::Mouse::getPosition(window).y >= pos_vect[2].y && sf::Mouse::getPosition(window).y <= pos_vect[2].y+40 ){
        return true;
    }
    return false;
}

bool check_third_box(sf::RenderWindow& window, Sidebar sidebar){
    sf::RectangleShape _sidebar = sidebar.return_rect();
    Vector<sf::Vector2f> pos_vect = sidebar.return_pos();
    if(sf::Mouse::getPosition(window).x >= _sidebar.getGlobalBounds().left&& sf::Mouse::getPosition(window).x <= _sidebar.getLocalBounds().width+_sidebar.getGlobalBounds().left && sf::Mouse::getPosition(window).y >= pos_vect[3].y && sf::Mouse::getPosition(window).y <= pos_vect[3].y+40){
        return true;
    }
    return false;
}

bool check_fourth_box(sf::RenderWindow& window, Sidebar sidebar){
    sf::RectangleShape _sidebar = sidebar.return_rect();
    Vector<sf::Vector2f> pos_vect = sidebar.return_pos();
    if(sf::Mouse::getPosition(window).x >= _sidebar.getGlobalBounds().left&& sf::Mouse::getPosition(window).x <= _sidebar.getLocalBounds().width+_sidebar.getGlobalBounds().left && sf::Mouse::getPosition(window).y >=  pos_vect[4].y && sf::Mouse::getPosition(window).y <= pos_vect[4].y+40 ){
        return true;
    }
    return false;
}

bool check_fifth_box(sf::RenderWindow& window, Sidebar sidebar){
    sf::RectangleShape _sidebar = sidebar.return_rect();
    Vector<sf::Vector2f> pos_vect = sidebar.return_pos();
    if(sf::Mouse::getPosition(window).x >= _sidebar.getGlobalBounds().left&& sf::Mouse::getPosition(window).x <= _sidebar.getLocalBounds().width+_sidebar.getGlobalBounds().left && sf::Mouse::getPosition(window).y >=  pos_vect[5].y && sf::Mouse::getPosition(window).y <= pos_vect[5].y+40 ){
        return true;
    }
    return false;
}

animate::animate(): sidebar(WORK_PANEL, SIDE_BAR), _info(new Graph_info())
{   
    textInputMode = false;
    cout<<"animate CTOR: TOP"<<endl;
    window.create(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "SFML window!");
    //VideoMode class has functions to detect screen size etc.
    //RenderWindow constructor has a third argumnet to set style
    //of the window: resize, fullscreen etc.

    //System will be implemented to manage a vector of objects to be animated.
    //  at that point, the constructor of the System class will take a vector
    //  of objects created by the animate object.
    //  animate will
    system = System();
   
    window.setFramerateLimit(60);

    mouseIn = true;

    


    mousePoint = sf::CircleShape();
    mousePoint.setRadius(5.0);
    mousePoint.setFillColor(sf::Color::Red);

    cout<<"Geme CTOR. preparing to load the font."<<endl;
    //--- FONT ----------
    //font file must be in the "working directory:
    //      debug folder
    //Make sure working directory is where it should be and not
    //  inside the app file:
    //  Project->RUN->Working Folder
    //
    //font must be a member of the class.
    //  Will not work with a local declaration
    if (!font.loadFromFile("arial.ttf")){
        cout<<"animate() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    
    string text;
    try{
    _info->_equation = sidebar[1];
    system.set_info(_info);
    text = _info->_equation;
    }
    catch(Exception_handler e){
        _info->_equation="R x";
        system.set_info(_info);
        text = e.Report();
        
    }
    myTextLabel = sf::Text(text, font);
    myTextLabel.setCharacterSize(20);
    myTextLabel.setStyle(sf::Text::Bold);
    myTextLabel.setColor(sf::Color::Green);
    myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-5));





    

    cout<<"animate instantiated successfully."<<endl;
}

void animate::Draw(){
    //Look at the data and based on the data, draw shapes on window object.
    system.Draw(window);
    if (mouseIn){
        window.draw(mousePoint);
    }

    sidebar.draw(window);

    //- - - - - - - - - - - - - - - - - - -
    //getPosition() gives you screen coords, getPosition(window) gives you window coords
    //cout<<"mosue pos: "<<sf::Mouse::getPosition(window).x<<", "<<sf::Mouse::getPosition(window).y<<endl;
    //- - - - - - - - - - - - - - - - - - -

    //drawing Test: . . . . . . . . . . . .
    //This is how you draw text:)
    window.draw(myTextLabel);
     if(system.get_display_text_box() == true){
            sf::RectangleShape x(sf::Vector2f(30.f,_info->_window_dimensions.x));
            x.setPosition(sf::Vector2f(0,30));
            x.setOrigin(x.getSize());
            x.rotate(90);
            window.draw(x);
            
            sf::Text TextInput(textInput,font);
            TextInput.setCharacterSize(20);
            TextInput.setColor(sf::Color::Black);
            TextInput.setPosition(sf::Vector2f(30,0) + sf::Vector2f(2.f,2.f));
            window.draw(TextInput);
        }
    //. . . . . . . . . . . . . . . . . . .
}

void animate::update(){
    //cause changes to the data for the next frame
    system.Step(command, window);
    //   if(command != 0 ){
    //     system.update(_info);
    //   }
    command = 0;
    if (mouseIn){
        //mousePoint red dot:
        mousePoint.setPosition(sf::Mouse::getPosition(window).x-5,
                               sf::Mouse::getPosition(window).y-5);

        //mouse location text for sidebar:
        sidebar[SB_MOUSE_POSITION] = mouse_pos_string(window);




    }
  
}
void animate::render(){
       window.clear();
       Draw();
       window.display();
}



void animate::processEvents()
{
   sf::Event event;
   float mouseX, mouseY;
   while (window.pollEvent(event))//or waitEvent
       {
       // check the type of the event...
           switch (event.type)
           {
           // window closed
           case sf::Event::Closed:
               window.close();
               break;
           // key pressed
           case sf::Event::KeyPressed:
               if(textInputMode == false){
               switch(event.key.code){
                case sf::Keyboard::P:
                    // sidebar[SB_KEY_PRESSED] = "P - ZOOM IN";
                    command = 1;
                    break;
                case sf::Keyboard::O:
                    // sidebar[SB_KEY_PRESSED] = "O - ZOOM OUT";
                    command=  2;
                    break;
                case sf::Keyboard::Up:
                    // sidebar[SB_KEY_PRESSED] = "UP ARROW";
                    // if(_info->isPolar == false){
                        command = 3;
                    // }
                    break;
                case sf::Keyboard::Left:
                    // sidebar[SB_KEY_PRESSED] = "LEFT ARROW";
                    // if(_info->isPolar==false){
                        command = 4;
                    // }
                    break;
                case sf::Keyboard::Down:
                    // sidebar[SB_KEY_PRESSED] = "DOWN ARROW";
                    // if(_info->isPolar==false){
                        command= 5;
                    // }
                    break;
                case sf::Keyboard::Right:
                    // sidebar[SB_KEY_PRESSED] = "RIGHT ARROW";
                    // if(_info->isPolar==false){
                        command = 6;
                    // }
                    break;
                case sf::Keyboard::Escape:
                    // sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                    sidebar.write_history();
                    window.close();
                        break;
                case sf::Keyboard::T:
                    // sidebar[SB_KEY_PRESSED] = "TEXT INPUT";
                    command = 7;
                    textInput="";
                    textInputMode = true;
                    break;
                case sf::Keyboard::Enter:
                    command = 9;
                    _info->_equation=sidebar[1];
                    myTextLabel = sf::Text(_info->_equation, font);
                } 
            } else {
                
                switch(event.key.code){
                    case sf::Keyboard::Escape:
                        // sidebar[SB_KEY_PRESSED] = "ESC: EXIT";
                        sidebar.write_history();
                        window.close();
                        break;
                    case sf::Keyboard::Enter:
                        // sidebar[SB_KEY_PRESSED] = "ENTER";
                       
                        try{
                        textInputMode = false;
                        _info->_equation = textInput;
                        system.update(_info);
                        sidebar.add_history(textInput);
                        textInput = "";
                        myTextLabel = sf::Text(_info->_equation,font);
                        }
                        catch(Exception_handler e){
                        myTextLabel = sf::Text(e.Report(),font);
                        }
                        command = 8;
                        break;
                }


                
            }
               break;
           case sf::Event::MouseEntered:
               mouseIn = true;
               break;
            
            break;
           case sf::Event::MouseLeft:
               mouseIn = false;
               break;

           case sf::Event::MouseMoved:
                mouseX = event.mouseMove.x;
                mouseY = event.mouseMove.y;
                //Do something with it if you need to...
               break;
            
            case sf::Event::TextEntered:
                if(system.get_display_text_box() == true){
                    if(event.text.unicode != '\b'){
                        textInput+= event.text.unicode;
                    } else if (textInput.size()!=0) {
                        textInput.pop_back();
                    }
                    cout << textInput << endl;
                }
                break;
                
           case sf::Event::MouseButtonReleased:

                   if (event.mouseButton.button == sf::Mouse::Right)
                   {
                    //    sidebar[SB_MOUSE_CLICKED]   = "RIGHT CLICK " +
                    //            mouse_pos_string(window);
                    if(check_first_box(window, sidebar) == true){
                        _info->_equation = sidebar[1];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;

                    } else if (check_second_box(window, sidebar)==true){
                        _info->_equation = sidebar[2];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;

                    }else if (check_third_box(window, sidebar)==true){
                        _info->_equation = sidebar[3];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }else if (check_fourth_box(window, sidebar)==true){
                        _info->_equation = sidebar[4];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }else if (check_fifth_box(window, sidebar)==true){
                        _info->_equation = sidebar[5];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }
                    
                   }
                   else{
                    //    sidebar[SB_MOUSE_CLICKED] = "LEFT CLICK " +
                    //            mouse_pos_string(window);
                    if(check_first_box(window,sidebar) == true){
                        _info->_equation = sidebar[1];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;


                    }else if (check_second_box(window, sidebar)==true){
                        _info->_equation = sidebar[2];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
    
                    } else if (check_third_box(window, sidebar)==true){
                        _info->_equation = sidebar[3];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }else if (check_fourth_box(window, sidebar)==true){
                        _info->_equation = sidebar[4];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }else if (check_fifth_box(window, sidebar)==true){
                        _info->_equation = sidebar[5];
                        system.update(_info);
                        myTextLabel = sf::Text(_info->_equation,font);
                        command = 99;
                    }
                    
                   }
                   break;

               default:
                   break;
           }
            myTextLabel.setCharacterSize(20);
            myTextLabel.setStyle(sf::Text::Bold);
            myTextLabel.setColor(sf::Color::Green);
            myTextLabel.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-myTextLabel.getLocalBounds().height-20));
       }
}
void animate::run()
{
   while (window.isOpen())
   {
       processEvents();
       update();
       render(); //clear/draw/display
   }
   cout<<endl<<"-------ANIMATE MAIN LOOP EXITING ------------"<<endl;
}

string mouse_pos_string(sf::RenderWindow& window){
    return "(" +
            to_string(sf::Mouse::getPosition(window).x) +
            ", " +
            to_string(sf::Mouse::getPosition(window).y) +
            ")";
}
