#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>

using namespace std;

pair<size_t, size_t> const NAN{0, 0};

bool overlap(pair<size_t, size_t> const& a, pair<size_t, size_t> const& b) {

  if (a == NAN || b == NAN)
    return false;

  if (& a == & b)
    return false;
  
  return (a.first  >= b.first && a.first  <= b.second)
      || (a.second >= b.first && a.second <= b.second)
      || (b.first  >= a.first && b.first  <= a.second)
      || (b.second >= a.first && b.second <= a.second);

}

bool merge(pair<size_t, size_t> & a, pair<size_t, size_t> & b) {

  if (! overlap(a, b))
    return false;

  b = {min(a.first, b.first), max(a.second, b.second)};

  a = NAN;

  return true;

}

int main(){
  
  string line, field;

  ifstream in_file("input.txt");

  vector<pair<size_t, size_t>> ranges;

  while (getline(in_file, line)) {

    if (line.length() == 0)
      break;

    stringstream line_stream(line);

    getline(line_stream, field, '-');

    size_t const beg = stol(field);

    getline(line_stream, field, '-');

    size_t const end = stol(field);

    ranges.emplace_back(beg, end);

  }

  bool done{false};

  while (! done) {

    done = true;

    for (pair<size_t, size_t> & a : ranges)
      for (pair<size_t, size_t> & b : ranges)
        done &= ! merge(a, b);

  }

  size_t sum{0};

  for (pair<size_t, size_t> const& r : ranges)
    if (r != NAN)
      sum += r.second - r.first + 1;

  cout << sum << endl;

}
