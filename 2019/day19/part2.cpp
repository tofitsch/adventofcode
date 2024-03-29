#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
#include<math.h>
#include<algorithm>

#define SIZE 100

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
    queue<long> input = {};
    bool halted = false;

    void init(queue<long> IN){
      
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
            tape[tape[pos + 1] + (op[1] == MODE_REL ? relative_base : 0)] = input.front();
            input.pop();
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
  
  int sum = 0;

  Intcode_computer computer;

  vector<int> beg = {0};
  vector<int> end = {0};

  int y = 0;
  int x = -1;

  int prev = -1;

  while(true){
    
    if(beg.size() > SIZE && end.size() > SIZE){
      if(end.back() - beg.back() >= SIZE){
        if(end.at(end.size() - SIZE) >= beg.back() + SIZE - 1){

          cout<<beg.back() * 10'000 + y - SIZE<<endl;
          exit(0);

        }
      }
    }
    
    x++;

    if(x < beg.back()){

      prev = 0;

      continue;

    }

    if(end.back() > 0 && x < end.back() - 1 && prev == 1){

      prev = 1;

      continue;

    }

    queue<long> input;

    input.push(x);
    input.push(y);

    computer.init(input);

    computer.run();

    if(computer.output == 1) sum++;

    if((prev == 1 || x > end.back() + 10) && computer.output == 0){
      
      end.push_back(x - 1);

      y++;
      x = -1;

      prev = -1;

      continue;

    }

    if(prev !=1 && computer.output == 1) beg.push_back(x);


    prev = computer.output;

  }

}
