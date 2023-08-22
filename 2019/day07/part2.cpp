#include<iostream>
#include<fstream>
#include<vector>
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
#define STOP 99
#define N_AMPS 5
#define OFFSET 5

using namespace std;

class Intcode_computer{

  private:

    vector<int> tape;
    int phase;
    bool phase_set = false;
    int op[4];
    unsigned int pos = 0;
    string buffer;

    int eval_parameter(int par){

      return op[par] == 1 ? tape[pos + par] : tape[tape[pos + par]];

    }
  
  public:

    int output = 0;
    int input = 0;
    bool halted = false;

    void init(int IN, int PH){
      
      tape.clear();
      pos = 0;
      halted = false;

      input = IN;
      phase = PH;
      
      ifstream in_file("input.txt");
    
      while(getline(in_file, buffer, ',')) tape.push_back(stoi(buffer));

      in_file.close();

    }
    
    int run(){

      while(true){
    
        op[0] = tape.at(pos) % 100;
         
        if(op[0] == STOP){
          
          halted = true;
          
          break;

        }
    
        for(int i=1; i<4; i++) op[i] = (tape.at(pos) % (int)pow(10, i+2) - op[i-1])  / (int)pow(10, i+1);
    
        switch(op[0]){
          
          case ADD:
            tape[tape[pos + 3]] = eval_parameter(1) + eval_parameter(2);
            pos += 4;
            break;
    
          case MUL:
            tape[tape[pos + 3]] = eval_parameter(1) * eval_parameter(2);
            pos += 4;
            break;
    
          case SAVE:
            tape[tape[pos + 1]] = phase_set ? input : phase;
            pos += 2;
            phase_set = true;
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
            tape[tape[pos + 3]] = (eval_parameter(1) < eval_parameter(2)) ? 1 : 0;
            pos += 4;
            break;
    
          case EQLS:
            tape[tape[pos + 3]] = (eval_parameter(1) == eval_parameter(2)) ? 1 : 0;
            pos += 4;
            break;
    
        }
        
      }

      return output;
    
    }

};

int main(){
  
  int phases[N_AMPS];

  for(int i=0; i<N_AMPS; i++) phases[i] = i + OFFSET;

  int max = (int)-1e10;

  do{

    Intcode_computer computers[N_AMPS];

    for(int i=0; i<N_AMPS; i++) computers[i].init(0, phases[i]);

    int it = 0;

    bool halted = false;

    while(!halted){

      computers[it == N_AMPS - 1 ? 0 : it + 1].input = computers[it].run();

      halted = computers[it].halted;

      it++;

      if(it >= N_AMPS) it = 0;

    }

    if(computers[N_AMPS - 1].output > max) max = computers[N_AMPS - 1].output;

  }while(next_permutation(phases, phases + N_AMPS));

  cout<<max<<endl;

}
