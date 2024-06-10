#include "graph_info.h"
Graph_info::Graph_info(){
  _window_dimensions = sf::Vector2f(SCREEN_WIDTH-SIDE_BAR,SCREEN_HEIGHT);
  _origin = sf::Vector2f((SCREEN_WIDTH-SIDE_BAR)/2.f,SCREEN_HEIGHT/2.f);
  _points = 4000;
  _equation ="";
  kms = 1;
  // _domain = sf::Vector2f(-5,5);
  // double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
  // double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
  // _scale=sf::Vector2f(transform_x,transform_y);



  // _spaces_tick = sf::Vector2f(transform_x,transform_y);
  // _scale= sf::Vector2f(1,1);
  // cout << "being constructed";
}

void Graph_info::reset_graph(){
  _window_dimensions = sf::Vector2f(SCREEN_WIDTH-SIDE_BAR,SCREEN_HEIGHT);
  _origin = sf::Vector2f((SCREEN_WIDTH-SIDE_BAR)/2.f,SCREEN_HEIGHT/2.f);
  _points = 4000;
  _equation ="";

  if(isPolar == true){
    _domain = sf::Vector2f(0,2*3.14159);
    kms = 1;
    double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
    double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
    _scale=sf::Vector2f(transform_x,transform_y);
  } else {
    _domain = sf::Vector2f(-5,5);
    double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
    double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
    _scale=sf::Vector2f(transform_x,transform_y);
  }
  // _domain = sf::Vector2f(-5,5);
  // double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
  // double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
  // _scale=sf::Vector2f(transform_x,transform_y);
}

Queue<Token*> Graph_info::tokenizer(){
  if(_equation[0] == 'P'){
    isPolar = true;
    _domain = sf::Vector2f(0,2*3.14159);
    kms = 1;
    double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
    double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
    _scale=sf::Vector2f(transform_x,transform_y);

  } else if(_equation[0]=='R'){
    isPolar =false;
    _domain = sf::Vector2f(-5,5);
    double transform_x = _window_dimensions.x / (_domain.y - _domain.x);
    double transform_y = _window_dimensions.y / (_domain.y - _domain.x);
    _scale=sf::Vector2f(transform_x,transform_y);

  } else {
    throw Exception_handler("Syntax Error: Did not indicate Polar or Rect Graph or add a space between the indication and equation");
  }

  if(!(_equation.length()>2)) throw Exception_handler("Syntax Error: Input valid equation");

  if(_equation[2]=='+'||_equation[2]=='*'|| _equation[2]=='/'||_equation[2]=='/'){
    throw Exception_handler("Operator at beginning of equation");
  }

  Queue<Token*> queue;
  //token list vector
  string token_list_a[] = {"+","-","*","/","^","e","sin","cos","tan","sinh","cosh","tanh","ln","arccos","arcsin","arctan","x","X","(",")"};
  string* token_list_p = token_list_a;
  Vector<string> token_list(token_list_p,20);

  vector<string> token_data_type = {"operator","operator","operator","operator","operator","function","function","function","function","function","function","function","function","function","function","function","function","function","leftparen","rightparen"};
  
  string char_holder;
  string int_holder;

  //exception handler check
  string last_input;
  int count_leftparen = 0;
  int count_rightparen= 0;
  for(int i = 1; i <_equation.length();i++){
    if(isspace(_equation[i])){
      last_input = "space";
      continue;
    }
    if(isdigit(_equation[i]) || _equation[i] == '.'){
      int_holder+= _equation[i];
      if(isdigit(_equation[i+1]) || _equation[i+1] == '.'){
        continue;
      } else if(_equation[i+1] == '+' || _equation[i+1]=='-'|| _equation[i+1]=='/'||_equation[i+1]=='*' || _equation[i+1]=='^' ||_equation[i+1] == ')' || _equation.length() == i+1 || isspace(_equation[i+1])) {
        queue.push(new Integer(int_holder));
        int_holder = "";
        last_input = "integer";
        continue;
      } else{
        queue.push(new Integer(int_holder));
        int_holder ="";
        queue.push(new Operator('*'));
        last_input= "operator";
        continue;
      }
    }
    
    if(_equation[i] == '-'){
      if(i == 2 || i == 1){
        queue.push(new Integer(-1));
        queue.push(new Operator('*'));
        continue;
      } else if (_equation[i+1] =='(' || _equation[i-1] == '+' || _equation[i-1]=='-'|| _equation[i-1]=='/'||_equation[i-1]=='*' || _equation[i-1]=='^'||_equation[i-1] == '('){
        queue.push(new Integer(-1));
        queue.push(new Operator('*'));
        continue;
      }

    }
    // cout << "char_holder: " << char_holder << endl;
    char_holder += _equation[i];
    int index = token_list.index_of(char_holder);
    if(index == -1){
      continue;
    } 
    if(char_holder == "sin"||char_holder=="cos"||char_holder=="tan"){
      if(_equation[i+1]=='h'){
        continue;
      }
    }
    string data_type = token_data_type.at(index);


    if(last_input == "operator" && data_type == "operator"){ 
      throw Exception_handler("Syntax error: operator back to back");
    }
    
    if(data_type == "function"){
      queue.push(new Function(char_holder));
      if(_equation[i] != 'x' || _equation[i]=='X'){
        if(_equation[i+1] != '('){
          throw Exception_handler("Syntax error: Missing parenthese");
        }
      }

      char_holder = "";
    } else if (data_type == "operator"){
      queue.push(new Operator(char_holder));
      char_holder = "";
    } else if (data_type == "leftparen"){
      queue.push(new LeftParen());
      count_leftparen++;
      char_holder = "";
    } else if (data_type == "rightparen"){
      queue.push(new RightParen());
      count_rightparen++;
      char_holder = "";
    } 

    last_input = data_type;
  }

  if(char_holder != "" || int_holder!= "") {
    throw Exception_handler("Syntax Error: Invalid Equation");
  }
  if(last_input == "operator"){
    throw Exception_handler("Syntax Error: Operator at end of equation");
  }
  if(count_leftparen != count_rightparen){
    // cout << "leftparen: " << count_leftparen << endl;
    // cout << "rightparen: " << count_rightparen << endl;
    throw Exception_handler("Syntax Error: Mismatch Parenthese");
  }
  if(queue.empty() == true){
    throw Exception_handler("Syntax Error: Equation is empty");
  }
  cout << queue << endl;  
  return queue;
}
