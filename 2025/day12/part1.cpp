#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <cassert>
#include <set>
#include <regex>

using namespace std;

vector<size_t> read_presents(string const& in_file_name) {

  vector<size_t> presents;

  ifstream in_file(in_file_name);

  string line;

  vector<string> g;

  size_t p{0};

  while (getline(in_file, line)) {

    if (regex_search(line, regex("^\\d+x")))
      break;

    if (regex_search(line, regex("^\\d+:"))) {

      p = 0;

      continue;

    }

    if (line.length() == 0) {

      presents.push_back(p);

      g = {};

      continue;

    }

    for (char const c : line)
      if (c == '#')
        ++p;

  }

  return presents;

}

struct Tree {

  Tree(string const& line, vector<size_t> const& presents) {

    size_t const
      pos_x = line.find('x'),
      pos_c = line.find(':');

    n_x = stoul(line.substr(0, pos_x));
    n_y = stoul(line.substr(pos_x + 1, pos_c - pos_x));

    n_max = n_x * n_y;

    stringstream line_stream(line.substr(pos_c + 2));

    string field;

    size_t ctr{0};

    n_min = 0;
    n_presents = 0;

    while (getline(line_stream, field, ' ')) {

      for (size_t i = 0; i < stoul(field); ++i) {

        n_min += presents[ctr];

        ++n_presents;

      }

      ++ctr;

    }

  }

  enum class Validity{yes, no, undetermined};

  Validity validity() const {

    if (n_min > n_max)
      return Validity::no;

    if (n_presents * 9 <= n_max)
      return Validity::yes;

    return Validity::undetermined;

  }

  size_t
    n_x,
    n_y,
    n_max,
    n_min,
    n_presents;

};

vector<Tree> read_trees(string const& in_file_name, vector<size_t> const& presents) {

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

  string const in_file_name{"input.txt"};

  vector<size_t> const presents = read_presents(in_file_name);

  vector<Tree> const trees = read_trees(in_file_name, presents);

  size_t ctr_yes{0}, ctr_no{0}, ctr_undetermined{0};

  for (Tree const& t : trees) {

    Tree::Validity const v = t.validity();

    if (v == Tree::Validity::yes)
      ++ctr_yes;

  }

  assert(ctr_undetermined == 0);

  cout << ctr_yes << endl; 

}
