#include<iostream>
#include<fstream>
#include<vector>

#define ADD 1
#define MUL 2
#define STOP 99
#define BUFFER_SIZE 10
#define NOUN_POS 1
#define VERB_POS 2
#define OUTPUT 19690720

using namespace std;

int main(){
  
  ifstream in_file("input.txt");

  char buffer[BUFFER_SIZE];

  vector<unsigned int> original_tape;

  while(in_file.good()){

    in_file.getline(buffer, BUFFER_SIZE, ',');

    original_tape.push_back(atoi(buffer));

  }

  for(unsigned int noun=0; noun<=STOP; noun++){
    for(unsigned int verb=0; verb<=STOP; verb++){

      vector<unsigned int> tape(original_tape);

      tape[NOUN_POS] = noun;
      tape[VERB_POS] = verb;

      unsigned int pos = 0;
    
      while(tape.at(pos) != STOP){
        
        if     (tape[pos] == ADD) tape[tape[pos + 3]] = tape[tape[pos + 1]] + tape[tape[pos + 2]];
        else if(tape[pos] == MUL) tape[tape[pos + 3]] = tape[tape[pos + 1]] * tape[tape[pos + 2]];
    
        pos += 4;
    
      }
    
      if(tape.at(0) == OUTPUT){

        cout<<100 * noun + verb<<endl;

        exit(0);

      }

    }
  }

}
