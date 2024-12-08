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

};

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

  for (auto const& [frequency, coords] : frequency_map) {

    for (int i = 0; i < coords.size(); ++i) {
      for (int j = i + 1; j < coords.size(); ++j) {
	
	Coord const& a = coords.at(i);
	Coord const& b = coords.at(j);

	antinodes.insert({2 * b.y - a.y, 2 * b.x - a.x});
	antinodes.insert({2 * a.y - b.y, 2 * a.x - b.x});
	  
      }
    }

  }

  int count = 0;

  for (Coord const& a : antinodes)
    if (a.x >= 0 && a.x < n_x && a.y >= 0 && a.y < n_y)
      count++;

  cout << count << endl;

}
