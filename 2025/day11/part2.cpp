#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

size_t recurse(string const& key, string const& end, map<string, vector<string>> & graph, map<string, size_t> & memoize) {

  if (memoize.count(key) == 1)
    return memoize[key];

  if (key == end)
    return 1;

  size_t sum{0};

  for (string & k : graph[key])
    sum += recurse(k, end, graph, memoize);

  memoize[key] = sum;

  return sum;

}

size_t n_paths(string const& beg, string const& end, map<string, vector<string>> & graph) {

  map<string, size_t> memoize;

  return recurse(beg, end, graph, memoize);

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

  string hop1{"fft"}, hop2{"dac"};

  if (n_paths(hop1, hop2, graph) == 0)
    swap(hop1, hop2);

  size_t sum{1};

  sum *= n_paths("svr", hop1,  graph); 
  sum *= n_paths(hop1 , hop2,  graph); 
  sum *= n_paths(hop2 , "out", graph); 

  cout << sum << endl;

}
