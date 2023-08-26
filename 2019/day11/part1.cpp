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

using namespace std;

class Intcode_computer{

  private:

    short op[4];
    unsigned int pos = 0;
    string buffer;
    long relative_base = 0;

    long eval_parameter(long par){
      
      long raw = tape[pos + par];
      
      switch(op[par]){
        
        case MODE_POS: return tape[raw];
        case MODE_DIR: return raw;
        case MODE_REL: return tape[raw + relative_base];

        default: return 0;
          
      }

    }
  
  public:

    map<int, long> tape;

    long output = 0;
    long input = 0;
    bool halted = false;

    void init(long IN){
      
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
    
    long run(){

      while(true){
    
        op[0] = tape.at(pos) % 100;
         
        if(op[0] == STOP){
          
          halted = true;
          
          return STOP;

        }
    
        for(short i=1; i<4; i++) op[i] = (tape.at(pos) % (long)pow(10, i+2) - op[i-1])  / (long)pow(10, i+1);

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

int main(){
  
  Intcode_computer computer;

  pair<int, int> bot_pos = {0, 0};

  map<pair<int, int>, int> trace;

  trace[bot_pos] = 0;

  computer.init(0);

  int facing = 0;

  while(!computer.halted){
    
    computer.input = trace[bot_pos];

    int colour    = computer.run();
    int direction = computer.run();

    cout<<colour<<" "<<direction<<endl;

    trace[bot_pos] = colour;

    if(direction == 1) facing++;
    if(direction == 0) facing--;

    if(facing > 3) facing = 0;

    if(facing == 0) bot_pos.second++;
    if(facing == 1) bot_pos.first++;
    if(facing == 2) bot_pos.second--;
    if(facing == 3) bot_pos.first--;

  }

  pair<int, int> max = {1e-9, 1e-9};
  pair<int, int> min = {1e9, 1e9};

  for(const auto &p : trace){
    
    cout<<p.first.first<<" "<<p.first.second<<endl;
    
    int x = p.first.first;
    int y = p.first.second;
    
    if(x > max.first) max.first = x;
    if(x < min.first) min.first = x;

    if(y > max.second) max.second = y;
    if(y < min.second) min.second = y;

  }


  for(int y=min.second; y<=max.second; y++){
    for(int x=min.first; x<=max.first; x++){
      
      pair<int, int> tmp = {x, y};
      
      cout<<(trace[tmp] == 1 ? '#' : '.');

    }

    cout<<endl;

  }

  cout<<trace.size() - 1<<endl;

}
