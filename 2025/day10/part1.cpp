#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

struct Button {

  Button(string const str) {

    string field;

    stringstream str_stream(str);

    while (getline(str_stream, field, ','))
      connections.push_back(stoul(field));

  }

  void press(vector<bool> & state) {

    for (size_t const i : connections)
      state[i] = ! state[i];

  }

  vector<size_t> connections;

};

struct Machine {

  Machine(string const& line) {

    string field;

    stringstream line_stream(line);

    getline(line_stream, field, ' ');

    target = vector<bool>(field.length() - 2, 0);

    for (size_t i = 1; i < field.size() - 1; ++i)
      target[i - 1] = (field[i] == '#');

    while (getline(line_stream, field, ' '))
      buttons.emplace_back(field.substr(1, field.size() - 2));

    buttons.pop_back();

  }

  size_t solve() {

    size_t const
      n_bits = buttons.size(),
      all_ones = (size_t(1) << n_bits) - 1;

    size_t min_presses{n_bits};

    for (size_t ctr = 0; ctr <= all_ones; ++ctr) {

      vector<bool> state(target.size(), 0);

      size_t n_presses{0};

      for (size_t i_bit = 0; i_bit < n_bits; ++i_bit) {

        bool const bit = (ctr >> i_bit) & 1;

        if (! bit)
          continue;

        buttons[i_bit].press(state);

        ++n_presses;

      }

      if (state == target && n_presses < min_presses)
        min_presses = n_presses;

    }

    return min_presses;

  }

  vector<bool> target;

  vector<Button> buttons;

};

int main() {

  string line;

  ifstream in_file("input.txt");

  size_t sum{0};

  while (getline(in_file, line)) {
    
    Machine m(line);

    sum += m.solve();

  }

  cout << sum << endl;

}
