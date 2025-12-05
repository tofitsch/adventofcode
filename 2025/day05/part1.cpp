#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>

using namespace std;

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<size_t> beg, end, mid;

  bool is_range{true};

  while (getline(in_file, line)) {

    if (line.length() == 0) {

      is_range = false;

      continue;

    }

    if (! is_range) {

      mid.push_back(stol(line));

      continue;

    }

    stringstream line_stream(line);

    getline(line_stream, field, '-');

    beg.push_back(stol(field));

    getline(line_stream, field, '-');

    end.push_back(stol(field));

  }

  size_t ctr{0};

  for (size_t const m : mid) {
    for (size_t i = 0; i < beg.size(); ++i) {
      if (m >= beg[i] && m <= end[i]) {

        ++ctr;

        break;

      }
    }
  }

  cout << ctr << endl;

}
