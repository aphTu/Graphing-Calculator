#include "sidebar.h"
#include "constants.h"
Sidebar::Sidebar(){

}

Sidebar::Sidebar(float left, float width):_left(left), _width(width){
    cout<<"Sidebar CTOR: TOP"<<endl;
    items.reserve(50);
    //set up the sidebar rectangle:
    rect.setFillColor(sf::Color(0,98,105)); //(192,192,192)); //silver
    rect.setOutlineColor(sf::Color(104,71,141));
    rect.setOutlineThickness(3.f);
    rect.setPosition(sf::Vector2f(left, 0));
    rect.setSize(sf::Vector2f(width, SCREEN_HEIGHT));
    cout<<"Sidebar CTOR: about to load font."<<endl;

    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    //the font file must be in the "working directory"
    // check projects->run->working directory
    //      [Make sure it's not pointing to the app file]

    if (!font.loadFromFile("Roboto-Thin.ttf")){
        cout<<"Sidebar() CTOR: Font failed to load"<<endl;
        cin.get();
        exit(-1);
    }
    ////- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -

    cout<<"Sidebar CTOR: loaded font."<<endl;

    //. . . . . text / font problems: . . . . . . . .
    //initializing text object in this way caused problems
    // (hangs!)
    //only when sb_text was a private member and worked fine
    //when it was a public member. Probably not releavant,
    //but still strange!
    //
    //sb_text = sf::Text("Initial String for myTextLabel", font);
    //
    //. . . . . . . . . . . . . . . . . . . . . . . . .
    cout<<"Sidebar CTOR: Text object initialized."<<endl;
    sb_text.setFont(font);
    sb_text.setCharacterSize(20);
    sb_text.setStyle(sf::Text::Bold);
    sb_text.setColor(sf::Color::Yellow);

    ////this is how you would position text on screen:
    //sb_text.setPosition(sf::Vector2f(10, SCREEN_HEIGHT-sb_text.getLocalBounds().height-5));

    items.push_back("sidebar sample text");
    //Fill the items vector with empty strings so that we can use [] to read them:
    
    // for (int i=0 ; i<30; i++){
    //     items.push_back("");
    // }
    get_history();
    cout<<"Sidebar: CTOR: Exit."<<endl;
}

void Sidebar::get_history(){
    ifstream MyTextFile("includes/history.txt");

    if(!MyTextFile.is_open()){
        cout << "ERROR FILE NOT OPEN\n";
        exit(1);
    }
    
    string holder;
    while(getline(MyTextFile,holder)){
        items.push_back(holder);
        // num_of_item++;
    }
    // cout << info->_points << endl;
    // info->_equation = items.at(1);
    // cout << info->_equation << endl;
    MyTextFile.close();
}

void Sidebar::add_history(string equation){
    if(items.size() == 6){
        items.pop_back();
    }
    int i = 0;
    for(vector<string>::iterator it = items.begin(); i <=1; i++, it++){
        if(i == 1){
            items.insert(it,equation);
            break;
        }
    }
}

void Sidebar::write_history(){
    ofstream MyTextFile("includes/history.txt");

    if(!MyTextFile.is_open()){
        cout << "ERROR FILE NOT OPEN\n";
        exit(1);
    }
     int i = 0;
    for(vector<string>::iterator it = items.begin(); it!= items.end(); i++, it++){
        if(i >= 1){
           MyTextFile << items.at(i) << "\n";
        }
    }
    

    MyTextFile.close();

}


void Sidebar::draw(sf::RenderWindow& window){
    const double VERTICAL_LINE_SPACING = 10.0;
    const double LEFT_MARGIN = 10.0;

    window.draw(rect);
    float height = 10;

    for (vector<string>::iterator it = items.begin();
                                it!= items.end(); it++){
        bool blank = false;
        if (strlen(it->c_str()) == 0){
            //empty rows must be taken into account (getLocalBounds())
            //    but not drawn
            blank = true;
            sb_text.setString("BLANK");
        }
        else{
            sb_text.setString(it->c_str());
        }
        sidebar_pos_vect.push_back(sf::Vector2f(_left+LEFT_MARGIN, height));
        sb_text.setPosition(sf::Vector2f(_left+LEFT_MARGIN, height));
        // height += sb_text.getLocalBounds().height+VERTICAL_LINE_SPACING;
        height += 30+VERTICAL_LINE_SPACING;
        if (!blank)
            window.draw(sb_text);
    }
}

string& Sidebar::operator [](int index){
    return items[index];
}
