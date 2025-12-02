#include<iostream>
#include<fstream>
#include<sstream>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  getline(in_file, line);

  stringstream line_stream(line);

  size_t sum{0};

  while(getline(line_stream, field, ',')) {

    size_t const 
      pos = field.find('-'),
      beg = stol(field.substr(0, pos)),
      end = stol(field.substr(pos + 1));

    for (size_t i = beg; i <= end; ++i) {

      string const s = to_string(i);

      for (size_t j = 1; j <= s.size() / 2; ++j) {

        if (s.length() % j > 0)
          continue;

        string const s_beg = s.substr(0, j);

        bool is_valid{false};

        for (size_t k = j; k < s.size(); k += j) {

          string const s_sub = s.substr(k, j);

          if (s_sub != s_beg) {

            is_valid = true;

            break;

          }

        }

        if (! is_valid) {

          sum += i;

          break;

        }

      }

    }

  }

  cout << sum << endl;

}
