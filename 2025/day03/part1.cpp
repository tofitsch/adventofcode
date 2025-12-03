#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  
  string line;

  ifstream in_file("input.txt");

  size_t sum{0};

  while (getline(in_file, line)) {

    int best_joltage{0};

    for (size_t i = 0; i < line.length(); ++i) {
      for (size_t j = i + 1; j < line.length(); ++j) {

        string const str{line[i], line[j]};

        int joltage = stoi(str);

        if (joltage > best_joltage)
          best_joltage = joltage;

      }
    }

    sum += best_joltage;

  }

  cout << sum << endl;

}
