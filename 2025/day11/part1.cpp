#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t recurse(string const& key, map<string, vector<string>> & graph) {

  if (key == "out")
    return 1;

  size_t sum{0};

  for (string & k : graph[key])
    sum += recurse(k, graph);

  return sum;

}

int main() {

  string line, field;

  ifstream in_file("input.txt");

  map<string, vector<string>> graph;

  while (getline(in_file, line)) {

    stringstream line_stream(line);

    getline(line_stream, field, ':');

    string const key = field;

    graph[key] = {};

    while (getline(line_stream, field, ' '))
      graph[key].push_back(field);
    
  }

  cout << recurse("you", graph) << endl;

}
