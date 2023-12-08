#include<iostream>
#include<fstream>
#include<sstream>
#include<map>

using namespace std;

int main(){

  string line, instructions;

  ifstream in_file("input.txt");

  getline(in_file, instructions);

  map<string, pair<string, string>> graph;

  while(getline(in_file, line))
    if(line.length() > 0)
      graph[line.substr(0, 3)] = {line.substr(7, 3), line.substr(12, 3)};

  string pos = "AAA";

  int step = 0;

  while(pos != "ZZZ"){

    if(instructions[step % instructions.length()] == 'L')
      pos = graph[pos].first;
    else
      pos = graph[pos].second;

    step++;

  }

  cout << step << endl;

}
