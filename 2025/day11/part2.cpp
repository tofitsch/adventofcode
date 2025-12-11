#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

vector<char> recurse(string const& key, map<string, vector<string>> & graph) {

  if (key == "out")
    return {0};

  vector<char> signal;

  for (string & k : graph[key])
    for (char const c : recurse(k, graph))
      signal.push_back((key == "fft" || key == "dac") ? c + 1 : c);

  return signal;

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

  vector<char> signal = recurse("svr", graph);

  size_t ctr{0};

  for (char const c : signal)
    if (c == 2)
      ++ctr;

  cout << ctr << endl;

}
