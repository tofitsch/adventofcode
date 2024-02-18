#include<iostream>
#include<fstream>
#include<vector>
#include<map>
#include<queue>
#include<math.h>
#include<algorithm>

#define N_BOTS 50

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

    long output = -1;
    queue<long> input = {};
    bool halted = false;

    void init(long IN){
      
      input.push(IN);

      init();

    }

    void init(){

      tape.clear();
      pos = 0;
      relative_base = 0;
      halted = false;

      ifstream in_file("input.txt");

      while(getline(in_file, buffer, ',')){

        tape[pos] = stol(buffer);

        pos ++;

      }

      pos = 0;

      in_file.close();

    }

    long step(){

//      while(true){
        
//        cout<<">"<<pos<<endl;
    
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
            tape[tape[pos + 1] + (op[1] == MODE_REL ? relative_base : 0)] = (input.size() == 0 ? -1 : input.front());
            if(input.size() > 0) input.pop();
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
        
//      }

      return output;
    
    }

    long run(){
      
      while(true) step();

    }
    

};

queue<long> parse(string str){
  
  queue<long> q;

  for(char & c : str)
    q.push((long) c);

  q.push((long) '\n');

  return q;

}

int main(){
//
//  Intcode_computer bot;
//  bot.init(0);
//  bot.output = -1;
//  bot.input.push(-1);
//  for(int i=0; i<100; i++)
//    cout<<">"<<bot.step()<<endl;

  Intcode_computer bots[N_BOTS];

  for(int i=0; i<N_BOTS; i++)
    bots[i].init(i);

  vector<pair<int, int>> packets[N_BOTS];

  while(true){

    for(int i=0; i<N_BOTS; i++){
     
      for(pair<int, int> packet : packets[i]){
        
        bots[i].input.push(packet.second);
        bots[i].input.push(packet.first);

      }

      packets[i].clear();

    }

    for(int i=0; i<N_BOTS; i++){
      
      int destination = bots[i].step();

      if(destination >= 0){
        
        bots[i].step();

        int X = bots[i].step();
        int Y = bots[i].step();
        
        cout<<destination<<" "<<X<<" "<<Y<<endl;

        packets[destination].push_back({X, Y});
        
      
      }

    }

  }

}
