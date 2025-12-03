#include<iostream>
#include<fstream>

using namespace std;

size_t best_joltage(string const& line) {

  string str = "999999999999";

  size_t i_cursor{0};

  for (size_t i_str = 0; i_str < str.length(); ++i_str) {

    bool found{false};

    for (size_t i_line = i_cursor; i_line < line.length(); ++i_line) {
      if (line[i_line] == str[i_str]) {

        i_cursor = i_line + 1;

        found = true;

        break;

      }
    }

    if (! found) {

      bool underflow = (str[i_str] == '0');

      if (underflow)
        i_str--;

      for (size_t j_str = i_str + 1; j_str < str.length(); ++j_str)
        str[j_str] = '9';

      str[i_str]--;

      i_str -= 2;

      if (underflow)
        i_str--;

      i_cursor--;

      cout << str << endl;

    }

  }

  cout << line << endl;
  cout << "> " << str << endl;

  return stol(str);

}

int main(){
  
  string line;

  ifstream in_file("example.txt");

  size_t sum{0};

  while (getline(in_file, line))
    sum += best_joltage(line);

  cout << sum << endl;

}
