#include<iostream>
#include<fstream>
#include<sstream>
#include<numeric>
#include<vector>
#include<map>

using namespace std;

bool finished(vector<long> & period_length){

  for(long & p : period_length)
    if(p == 0)
      return false;

  return true;

}

int main(){

  string line, instructions;

  ifstream in_file("input.txt");

  getline(in_file, instructions);

  map<string, pair<string, string>> graph;

  while(getline(in_file, line))
    if(line.length() > 0)
      graph[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};

  vector<string> pos;

  for(auto & key : graph)
    if(key.first[2] == 'A')
      pos.push_back(key.first);

  vector<long> period_offset(pos.size(), 0);
  vector<long> period_length(pos.size(), 0);

  int step = 0;

  while(!finished(period_length)){
    
    if(instructions[step % instructions.length()] == 'L')
      for(string & i_pos : pos)
        i_pos = graph[i_pos].first;
    else
      for(string & i_pos : pos)
        i_pos = graph[i_pos].second;

    for(int i=0; i<pos.size(); i++)
      if(pos[i][2] == 'Z')
        if(period_offset[i] == 0)
          period_offset[i] = step;
        else
          period_length[i] = step - period_offset[i];

    step++;

  }

  long result = 1;

  for(long & p : period_length)
    result = lcm(result, p);

  cout << result / 2 << endl;

}
