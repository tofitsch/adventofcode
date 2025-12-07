#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

int main(){
  
  string line;

  ifstream in_file("input.txt");

  getline(in_file, line);

  size_t const n_x = line.length();

  vector<size_t> counters(n_x, 0);

  counters[line.find('S')] = 1;

  while (getline(in_file, line)) {

    vector<size_t> new_counters(n_x, 0);

    for (size_t x = 0; x < n_x; ++x) {

      if (line[x] == '^') {

        new_counters[x - 1] += counters[x];
        new_counters[x + 1] += counters[x];

      } else
        new_counters[x] += counters[x];

    }

    counters = new_counters;

  }

  size_t sum{0};

  for (size_t const ctr : counters)
    sum += ctr;

  cout << sum << endl;

}
