#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<math.h>
#include<algorithm>

#define ADD 1
#define MUL 2
#define SAVE 3
#define PRNT 4
#define JUMP_IF_TRUE 5
#define JUMP_IF_FALSE 6
#define LESS 7
#define EQLS 8
#define REL_BASE_MODIFY 9
#define STOP 99

#define MODE_POS 0
#define MODE_DIR 1
#define MODE_REL 2

#define MAX_INSTRUCTION_SIZE 20

using namespace std;

class Intcode_bot{

  private:

    short op[4];
    unsigned int pos = 0;
    string buffer;
    int relative_base = 0;

    int eval_parameter(int par){
      
      int raw = tape[pos + par];
      
      switch(op[par]){
        
        case MODE_POS: return tape[raw];
        case MODE_DIR: return raw;
        case MODE_REL: return tape[raw + relative_base];

        default: return 0;
          
      }

    }
  
  public:

    map<int, int> tape;
    pair<int, int> coord;

    int output = 0;
    int input = 0;
    bool halted = false;

    void init(int IN, pair<int, int> COORD){
      
      coord = COORD;
      
      tape.clear();
      pos = 0;
      relative_base = 0;
      halted = false;

      input = IN;
      
      ifstream in_file("input.txt");

      while(getline(in_file, buffer, ',')){

        tape[pos] = stol(buffer);

        pos ++;

      }

      pos = 0;

      in_file.close();

    }
    
    int run(){

      while(true){
    
        op[0] = tape.at(pos) % 100;
         
        if(op[0] == STOP){
          
          halted = true;
          
          return STOP;

        }
    
        for(short i=1; i<4; i++) op[i] = (tape.at(pos) % (int)pow(10, i+2) - op[i-1])  / (int)pow(10, i+1);

        switch(op[0]){
          
          case ADD:
            tape[tape[pos + 3] + (op[3] == MODE_REL ? relative_base : 0)] = eval_parameter(1) + eval_parameter(2);
            pos += 4;
            break;
    
          case MUL:
            tape[tape[pos + 3] + (op[3] == MODE_REL ? relative_base : 0)] = eval_parameter(1) * eval_parameter(2);
            pos += 4;
            break;
    
          case SAVE:
            tape[tape[pos + 1] + (op[1] == MODE_REL ? relative_base : 0)] = input;
            pos += 2;
            break;
    
          case PRNT:
            output = eval_parameter(1);
            pos += 2;
            return output;
    
          case JUMP_IF_TRUE:
            if(eval_parameter(1) != 0) pos = eval_parameter(2);
            else pos += 3;
            break;
    
          case JUMP_IF_FALSE:
            if(eval_parameter(1) == 0) pos = eval_parameter(2);
            else pos += 3;
            break;
    
          case LESS:
            tape[tape[pos + 3] + (op[3] == MODE_REL ? relative_base : 0)] = (eval_parameter(1) < eval_parameter(2)) ? 1 : 0;
            pos += 4;
            break;
    
          case EQLS:
            tape[tape[pos + 3] + (op[3] == MODE_REL ? relative_base : 0)] = (eval_parameter(1) == eval_parameter(2)) ? 1 : 0;
            pos += 4;
            break;

          case REL_BASE_MODIFY:
            relative_base += eval_parameter(1);
            pos += 2;
            break;
    
        }
        
      }

      return output;
    
    }

};

bool is_path(pair<int, int> const & coord, vector<vector<char>> & coord_map){
  
  if(coord.first < 0 || coord.second < 0) return false;
  if(coord_map.size() < coord.second + 1) return false;
  if(coord_map[coord.second].size() < coord.first + 1) return false;
  if(coord_map[coord.second][coord.first] == '.') return false;

  return true;
  
}

pair<int, int> go_forward(pair<int, int> const & coord, short const & facing){

  int x = coord.first;
  int y = coord.second;
  
  switch(facing){
    
    case 0: y--; break;
    case 1: x++; break;
    case 2: y++; break;
    case 3: x--; break;

  }

  return {x, y};

}

template<typename T>
void print_instructions(T instructions){//XXX
  for(auto & e : instructions){
    if(e == -1) cout<<"R";
    else if(e == -3) cout<<"L";
    else cout<<e;
    cout<<",";
  }
  cout<<endl;
}

template<typename T>
vector<T> concat(vector<T> const & vector1, vector<T> const & vector2){

  vector<T> return_vector(vector1);

  for(auto & x : vector2) return_vector.push_back(x);

  return return_vector;

}

template<typename T>
bool is_subvector_of(vector<T> const & vector1, vector<T> const & vector2){
  
//  print_instructions(vector1);
//  print_instructions(vector2);
//  cout<<endl;

  for(int i=0; i<vector1.size(); i++)
    if(vector1.at(i) != vector2.at(i))
      return false;

  return true;

}

template<typename T>
vector<T> subvec(vector<T> const & vec, int start, int end){
  
  vector<T> subvec;

  for(int i=start; i<end; i++) subvec.push_back(vec.at(i));

  return subvec;

}

int recursive_find_main_routine(vector<int> const & instructions, vector<int> const & conc, vector<vector<int>> const & routines, int n_routine){

//  print_instructions(routines.at(0));
//  print_instructions(routines.at(1));
//  print_instructions(routines.at(2));
//  cout<<endl;

  if(n_routine >= routines.size()
    || conc.size() > instructions.size()
    || !is_subvector_of(conc, instructions)
    ) return n_routine;

  print_instructions(conc);
  print_instructions(instructions);

  if(conc.size() == instructions.size()){

    print_instructions(instructions);
    print_instructions(conc);
    exit(0);

  }

  vector<int> new_conc = concat(conc, routines.at(n_routine));
  
  return recursive_find_main_routine(instructions, new_conc, routines, n_routine + 1);

}

int main(){

  Intcode_bot bot;

  vector<vector<char>> coord_map = {{}};
  vector<pair<int, int>> path;

  bot.init(0, {0, 0});

  pair<int, int> start;

  while(!bot.halted){
    
    bot.run();

    char c = bot.output;
    
    if(c == '\n'){

      coord_map.push_back({});

    }
    else{

      if(c!= '\n' && c != '.') path.push_back({coord_map.back().size(), coord_map.size() - 1});

      if(c == '^') start = {coord_map.back().size(), coord_map.size() - 1};

      coord_map.back().push_back(c);

    }

  }


  pair<int, int> current_coord = start;
  short current_facing = 0;

  bool arrived = false;

  vector<int> instructions = {0}; //+X: move X forward, -1: turn right, -3: turn left 

  while(!arrived){
    
    for(short turns_right : {0, 1, 3, 2}){ //2: backwards => arrived at end
      
      if(turns_right == 2){

        arrived = true;

        break;

      }

      short next_facing = current_facing + turns_right;
      if(next_facing > 3) next_facing -= 4;

      pair<int, int> next_coord = go_forward(current_coord, next_facing);

      if(is_path(next_coord, coord_map)){

        current_coord = next_coord;
        current_facing = next_facing;

        if(turns_right != 0){
          
          instructions.push_back(-turns_right);
          instructions.push_back(1);

        }
        else instructions.back()++;

        break;

      }

    }

  }

  if(instructions.at(0) == 0) instructions.erase(instructions.begin());

//  print_instructions(instructions);

  for(int end_a=1; end_a<=instructions.size() && end_a < MAX_INSTRUCTION_SIZE; end_a++){
    for(int end_b=end_a+1; end_b<=instructions.size() && end_b - end_a < MAX_INSTRUCTION_SIZE; end_b++){
      for(int end_c=end_b+1; end_c<=instructions.size() && end_c - end_b < MAX_INSTRUCTION_SIZE; end_c++){
        
        vector<int> a = subvec(instructions, 0, end_a);
        vector<int> b = subvec(instructions, end_a, end_b);
        vector<int> c = subvec(instructions, end_b, end_c);

        cout<<endl;
        print_instructions(a);
        print_instructions(b);
        print_instructions(c);
        cout<<endl;

        vector<vector<int>> routines = {a, b, c};

        vector<int> conc = concat(concat(a, b), c);
         
        recursive_find_main_routine(instructions, conc, routines, 0);

      }
    }
  }

//  print_instructions(instructions);

//  for(auto & x : coord_map){
//    for(auto & y : x)
//      cout<<y;
//    cout<<endl;
//  }

}
