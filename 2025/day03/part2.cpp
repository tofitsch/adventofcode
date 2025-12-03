#include<iostream>
#include<fstream>
#include<vector>

using namespace std;

size_t best_joltage(string const& line) {

  string str = "999999999999";

  vector<size_t> positions(str.length(), 0);

  size_t i_str{0};

  while (i_str < str.length()) {

    bool found{false};

    size_t const
      i_line_min = positions[i_str],
      i_line_max = line.length() - str.length() + i_str + 1;

    for (size_t i_line = i_line_min; i_line < i_line_max; ++i_line) {
      if (line[i_line] == str[i_str]) {

        positions[i_str] = i_line;

        if (i_str < str.length() - 1) 
          positions[i_str + 1] = i_line + 1;

        found = true;

        i_str++;

        break;

      }
    }

    if (! found) {

      bool const underflow = (str[i_str] == '0');

      if (underflow)
        i_str--;

      str[i_str]--;

      for (size_t j_str = i_str + 1; j_str < str.length(); ++j_str) {

        str[j_str] = '9';

        positions[j_str] = positions[i_str] + 1;

      }


    }

  }

  return stol(str);

}

int main(){
  
  string line;

  ifstream in_file("input.txt");

  size_t sum{0};

  while (getline(in_file, line))
    sum += best_joltage(line);

  cout << sum << endl;

}
