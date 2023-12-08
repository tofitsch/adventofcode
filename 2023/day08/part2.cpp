#include<iostream>
#include<fstream>
#include<sstream>
#include<numeric>
#include<vector>
#include<map>

using namespace std;

bool finished(vector<int> & periodicity){

  for(int & p : periodicity)
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

  vector<int> periodicity(pos.size(), 0);

  map<string, int> empty_map;
  vector<map<string, int>> steps_for_node(pos.size(), empty_map);

  int step = 0;

  while(!finished(periodicity)){

    if(instructions[step % instructions.length()] == 'L')
      for(string & i_pos : pos)
        i_pos = graph[i_pos].first;
    else
      for(string & i_pos : pos)
        i_pos = graph[i_pos].second;

    step++;

    for(int i=0; i<pos.size(); i++)
      if(periodicity[i] == 0 && steps_for_node[i][pos[i]] > 0)
        periodicity[i] = step;
      else
        steps_for_node[i][pos[i]] = step;

  }

  int result = 1;

  for(int & p : periodicity)
    result = lcm(result, p);

  cout << result << endl;

}
