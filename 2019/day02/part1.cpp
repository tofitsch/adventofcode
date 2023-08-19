#include<iostream>
#include<fstream>
#include<vector>

#define ADD 1
#define MUL 2
#define STOP 99
#define BUFFER_SIZE 10
#define NOUN_POS 1
#define VERB_POS 2
#define NOUN 12
#define VERB 2

using namespace std;

int main(){
  
  ifstream in_file("input.txt");

  char buffer[BUFFER_SIZE];

  vector<unsigned int> tape;

  while(in_file.good()){

    in_file.getline(buffer, BUFFER_SIZE, ',');

    tape.push_back(atoi(buffer));

  }

  tape[NOUN_POS] = NOUN;
  tape[VERB_POS] = VERB;

  unsigned int pos = 0;

  while(tape.at(pos) != STOP){
    
    if     (tape[pos] == ADD) tape[tape[pos + 3]] = tape[tape[pos + 1]] + tape[tape[pos + 2]];
    else if(tape[pos] == MUL) tape[tape[pos + 3]] = tape[tape[pos + 1]] * tape[tape[pos + 2]];

    pos += 4;

  }

  cout<<tape.at(0)<<endl;

}
