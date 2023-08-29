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

class Intcode_bot{

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
    pair<int, int> coord;

    long output = 0;
    long input = 0;
    bool halted = false;

    void init(long IN, pair<int, int> COORD){
      
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

  map<pair<int, int>, bool> occupied = {{{0, 0}, false}};
  

  Intcode_bot initial_bot;
  initial_bot.init(0, {0, 0});

  vector<Intcode_bot> bots = {initial_bot};

  int ctr = 0;

  while(true){
    
    ctr++;
    
    vector<Intcode_bot> new_bots;

    for(Intcode_bot &bot : bots){
      
      for(int i=1; i<=4; i++){

        pair<int, int> new_coord = bot.coord;

        if(i == 1)      new_coord.second++;
        else if(i == 2) new_coord.second--;
        else if(i == 3) new_coord.first++;
        else if(i == 4) new_coord.first--;

        if(occupied[new_coord]) continue;

        occupied[new_coord] = true;

        Intcode_bot new_bot = bot;

        new_bot.coord = new_coord;

        new_bot.input = i;

        int output = new_bot.run();

        if(output == 2){
          
          cout<<ctr<<endl;
          return 0;

        }

        if(output == 1) new_bots.push_back(new_bot);

      }

    }

    bots = new_bots;

  }

}
