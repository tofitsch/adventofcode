#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <set>
#include <regex>

using namespace std;

using GridBase = vector<vector<bool>>;

struct Grid : GridBase {

  using GridBase::GridBase;

  size_t n_x() const
    {return this[0].size();}

  size_t n_y() const
    {return this->size();}

  Grid rotate(size_t const n) const {

    if (n == 0)
      return * this;

    Grid g(n_y(), vector<bool>(n_x()));

    for (size_t x = 0; x < n_x(); ++x)
      for (size_t y = 0; y < n_y(); ++y)
        g[x][y] = (*this)[n_y() - 1 - y][x];

    return g.rotate(n - 1);

  }

};


struct Present {

  Present(vector<string> const& lines) {
    
    n_y = lines.size();
    n_x = lines[0].size();

    Grid g(n_y, vector<bool>(n_x));

    for (size_t y = 0; y < n_y; ++y)
      for (size_t x = 0; x < n_x; ++x)
        g[y][x] = (lines[y][x] == '#');

    orientations.insert(g.rotate(0));
    orientations.insert(g.rotate(1));
    orientations.insert(g.rotate(2));
    orientations.insert(g.rotate(3));
    //TODO
    
  }

  void print() const { //TODO

    cout << endl;
    cout << endl;

    for (Grid const& g : orientations) {

      for (vector<bool> const& r : g) {

        for (bool const c : r)
          cout << (c ? '#' : '.');

        cout << endl;

      }

      cout << endl;

    }

  }

  bool place(Grid & grid, size_t const x, size_t const y, size_t const z) const {
    //TODO
    return true;
  }

  set<Grid> orientations;

  size_t n_x, n_y, n_z; //z: orientation

};

struct Tree {

  Tree(string const& line, vector<Present> const& p) {

    size_t const
      pos_x = line.find('x'),
      pos_c = line.find(':');

    n_x = stoul(line.substr(0, pos_x));
    n_y = stoul(line.substr(pos_x + 1, pos_c - pos_x));

    stringstream line_stream(line.substr(pos_c + 1));

    string field;

    size_t ctr{0};

    while (getline(line_stream, field)) {

      for (size_t i = 0; i < stoul(field); ++i)
        presents.push_back(& p[ctr]);

      ++ctr;

    }

  }

  vector<Present const *> presents;

  size_t n_x, n_y;

  bool solve() {
    //TODO;
    return true;
  }

};

vector<Present> const read_presents(string const& in_file_name) {

  vector<Present> presents;

  ifstream in_file(in_file_name);

  string line;

  vector<string> g;

  while (getline(in_file, line)) {

    if (regex_search(line, regex("^\\d+x")))
      break;

    if (regex_search(line, regex("^\\d+:")))
      continue;

    if (line.length() == 0) {

      presents.emplace_back(g);

      g = {};

      continue;

    }

    g.push_back(line);

  }

  return presents;

}

vector<Tree> const read_trees(string const& in_file_name, vector<Present> const& presents) {

  vector<Tree> trees;

  ifstream in_file(in_file_name);

  string line;

  while (getline(in_file, line))
    if (regex_search(line, regex("^\\d+x")))
      trees.emplace_back(line, presents);

  return trees;

}

int main() {

  string line;

  string const in_file_name{"example.txt"};

  vector<Present> const presents = read_presents(in_file_name);

  vector<Tree> const trees = read_trees(in_file_name, presents);

  for (Present const& p : presents)
    p.print();

}
