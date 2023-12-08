#include<iostream>
#include<fstream>
#include<sstream>
#include<numeric>
#include<vector>
#include<map>

using namespace std;

bool finished(vector<int> & z_offset){

  for(int & z : z_offset)
    if(z == 0)
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

  vector<long> period_length(pos.size(), 0);
  vector<int> period_offset(pos.size(), 0);
  vector<int> z_offset(pos.size(), 0);

  map<string, int> empty_map;
  vector<map<string, int>> steps_for_node(pos.size(), empty_map);

  int step = 0;

  while(!finished(z_offset)){
    
    int i_instruction = step % instructions.length();

    if(instructions[i_instruction] == 'L')
      for(string & i_pos : pos)
        i_pos = graph[i_pos].first;
    else
      for(string & i_pos : pos)
        i_pos = graph[i_pos].second;

    cout<<"> "<<step<<endl;
    for(int i=0; i<pos.size(); i++)
      cout<<pos[i]<<" "<<i_instruction<<" "<<period_offset[i]<<" "<<period_length[i]<<" "<<z_offset[i]<<endl;
    cout<<endl;

    for(int i=0; i<pos.size(); i++){

      if(period_offset[i] == 0 && steps_for_node[i][pos[i] + to_string(i_instruction)] > 0){
        period_offset[i] = steps_for_node[i][pos[i] + to_string(i_instruction)];
        period_length[i] = step - period_offset[i];
      }
      else
        steps_for_node[i][pos[i] + to_string(i_instruction)] = step;

      if(period_offset[i] > 0 && z_offset[i] == 0 && pos[i][2] == 'Z')
        z_offset[i] = step / 2;

    }

    step++;

  }

  long result = 1;

  for(int i=0; i<pos.size(); i++)
    cout<<period_offset[i]<<" "<<period_length[i]<<" "<<z_offset[i]<<endl;

  for(long & p : period_length)
    result = lcm(result, p);

  cout << result << endl;

}
