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

      if (s.length() % 2 > 0)
        continue;

      string const
        s_beg = s.substr(0, s.length() / 2),
        s_end = s.substr(s.length() / 2);

      if (s_beg == s_end)
        sum += i;

    }

  }

  cout << sum << endl;

}
