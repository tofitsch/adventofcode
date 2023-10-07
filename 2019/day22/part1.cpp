#include<iostream>
#include<fstream>
#include<sstream>
#include<queue>

using namespace std;

#define END_POS 2019
#define N_CARDS 10007
//#define N_CARDS 10

void swap(int * stack, int a, int b){ //TODO: by reference?

  int tmp = stack[a];
  stack[a] = stack[b];
  stack[b] = tmp;

}

void deal_into_new_stack(int * stack){
  
  for(int i=0; i<N_CARDS / 2; i++)
    swap(stack, i, N_CARDS - i - 1);

}

void cut(int * stack, int n_cut){

  queue<int> q;
  
  if(n_cut > 0){
    
    n_cut %= N_CARDS;
    
    for(int i=0; i<n_cut; i++)
      q.push(stack[i]);

    for(int i=0; i<N_CARDS - n_cut; i++)
      stack[i] = stack[i + n_cut];

    for(int i=N_CARDS - n_cut; i<N_CARDS; i++){
      
      stack[i] = q.front();
      q.pop();

    }

  }
  else{
    
    deal_into_new_stack(stack);
    cut(stack, abs(n_cut));
    deal_into_new_stack(stack);
   
  }

}

void deal_with_increment(int * stack, int inc){
  
  int tmp[N_CARDS];

  for(int i=0; i<N_CARDS; i++)
    tmp[i] = stack[i];

  for(int i=0; i<N_CARDS; i++)
    stack[(i * inc) % N_CARDS] = tmp[i];

}

int main(){
   
  int stack[N_CARDS];

  for(int i=0; i<N_CARDS; i++)
    stack[i] = i;

  string line, field;

  vector<pair<string, int>> instructions;

  ifstream in_file("example.txt");

  while(getline(in_file, line)){
    
    stringstream line_stream(line);
      
    instructions.push_back({"", 0});

    while(getline(line_stream, field, ' ')){
      
      if(isdigit(field.back())) instructions.back().second = stoi(field);
      else instructions.back().first += field;

    }

  }

  int ctr = 0;

  for(auto & instruction : instructions){
    
    ctr++; 

    cout<<ctr<<"/"<<instructions.size()<<" "<<instruction.first<<" "<<instruction.second<<endl;
    
    if(instruction.first == "dealintonewstack") deal_into_new_stack(stack);
    else if(instruction.first == "dealwithincrement") deal_with_increment(stack, instruction.second);
    else if(instruction.first == "cut") cut(stack, instruction.second);

  }

  for(int i=0; i<N_CARDS; i++)
    cout<<stack[i]<<" ";
  cout<<endl;

  cout<<stack[END_POS]<<endl;

}
