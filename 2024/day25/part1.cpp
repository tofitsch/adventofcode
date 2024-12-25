#include <iostream>
#include <fstream>
#include <vector>

using namespace std;
using Code = vector<int>;

const int n_x = 5;
const int n_y = 7;

bool read_file(ifstream & in_file, vector<Code> & keys, vector<Code> & locks) {

	string line;

	bool is_lock = false;

	vector<string> grid;

	for (int i = 0; i < n_y; i++) {

		getline(in_file, line);

		if (i == 0 && line == "#####")
			is_lock = true;

		grid.push_back(line);

	}

	Code code(n_x, 0);

	for (int x = 0; x < n_x; x++)
		for (int y = 0; y < n_y; y++)
			if (grid[y][x] == '#')
				code[x]++;

	if (is_lock)
		locks.push_back(code);
	else
		keys.push_back(code);

	return static_cast<bool>(getline(in_file, line));

}

bool is_match(Code const& key, Code const& lock) {

	for (int i = 0; i < n_x; i++)
		if (key[i] + lock[i] > n_y)
			return false;

	return true;

}

int count_matches(vector<Code> const& keys, vector<Code> & locks) {

	int count = 0;

	for (Code const& key : keys)
		for (Code const& lock : locks)
			if (is_match(key, lock))
				count++;

	return count;

}

int main() {

	ifstream in_file("input.txt");

	vector<Code> keys, locks;

	while (read_file(in_file, keys, locks));

	cout << count_matches(keys, locks) << endl;

}
