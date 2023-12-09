#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

struct Row{
  
  vector<int> state;
  vector<int> history;

  Row(string & line){
    
    stringstream line_stream(line);

    string field;

    while(getline(line_stream, field, ' '))
      state.push_back(stoi(field));

  }

  void iterate(){

    history.push_back(state[0]);
   
    for(int i = 0; i < state.size() - 1; ++i)
      state[i] = state[i + 1] - state[i];

    state.pop_back();

  }

  bool finished(){
    
    for(int & s : state)
      if(s != 0)
        return false;

    return true;

  }

  int result(){
    
    int x = 0;

    for(int i = history.size() - 1; i >= 0; --i)
      x = history[i] - x;

    return x;

  }

};

int main(){
  
  string line;

  ifstream in_file("input.txt");

  vector<Row> rows;

  while(getline(in_file, line))
    rows.push_back(Row(line));

  int sum = 0;

  for(Row & row : rows){
    
    while(!row.finished())
      row.iterate();

    sum += row.result();
    
  }

  cout << sum << endl;

}
