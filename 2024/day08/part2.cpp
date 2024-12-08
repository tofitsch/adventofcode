#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Coord {

  int y, x;

  bool const operator < (Coord const& other) const {
    return y < other.y ? true : y == other.y ? x < other.x : false;
  }

  bool const inbounds (size_t const n_y, size_t const n_x) const {
    return x >= 0 && x < n_x && y >= 0 && y < n_y;
  }

};

void add_antinodes(Coord const& a, Coord const& b, size_t const n_y, size_t const n_x, set<Coord> & antinodes) {

  int n = 0;
  
  while(antinodes
        .insert({b.y + n * (b.y - a.y), b.x + n * (b.x - a.x)})
        .first
        ->inbounds(n_y, n_x)
       )
    n++;

}

int main() {

  ifstream in_file("input.txt");
  
  vector<string> lines {{""}};

  while (getline(in_file, lines.back()))
    lines.push_back("");
  
  lines.pop_back();

  size_t const n_x {lines.at(0).size()};
  size_t const n_y {lines.size()};

  map<char, vector<Coord>> frequency_map;

  for (int y = 0; y < n_y; ++y) {
    for (int x = 0; x < n_x; ++x) {

      char const c {lines[y][x]};

      if (c != '.') {

	if (frequency_map.find(c) == frequency_map.end())
	  frequency_map.insert({c, {{y, x}}});
	else
	  frequency_map[c].push_back({y, x});

      }

    }
  }

  set<Coord> antinodes;

  for (auto const& [frequency, coords] : frequency_map)
    for (int i = 0; i < coords.size(); ++i)
      for (int j = i + 1; j < coords.size(); ++j) {
	add_antinodes(coords.at(i), coords.at(j), n_y, n_x, antinodes);
	add_antinodes(coords.at(j), coords.at(i), n_y, n_x, antinodes);
      }

  int count = 0;

  for (Coord const& a : antinodes)
    if (a.x >= 0 && a.x < n_x && a.y >= 0 && a.y < n_y) {
      if (lines[a.y][a.x] == '.')
	lines[a.y][a.x] = '#';
      count++;
    }

  for (string const& line : lines)
    cout << line << endl;

  cout << count << endl;

}
