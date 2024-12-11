#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

long n_digits(long in) {

	return static_cast<long>(log10(in)) + 1;

}

long split_digits(long & in) {

	long orig = in;

	long n = n_digits(in) / 2;

	long divisor = static_cast<long>(pow(10, n)); 

	in /= divisor;

	return orig % divisor;

}

void add(map<long, long> & stones, long key, long count) {

	if (stones.find(key) == stones.end())
		stones[key] = count;
	else
		stones[key] += count;

}

void transform(long key, long count, map<long, long> & stones) {

	if (key == 0) {
		add(stones, 1, count);
		return;
	}

	if (n_digits(key) % 2 == 0) {
		add(stones, split_digits(key), count);
		add(stones, key, count);
		return;
	}

	add(stones, key * 2024, count);

}

map<long, long> get_stones(string const& in_file_name) {

	string line, field;

	fstream in_file(in_file_name);

	getline(in_file, line);

	stringstream line_stream(line);

	map<long, long> stones;

	while (getline(line_stream, field, ' '))
	  add(stones, stol(field), 1);

	return move(stones);

}

int main () {

	int const n_steps = 75;

	map<long, long> stones = get_stones("input.txt");

	for (int s = 0; s < n_steps; s++) {

		map<long, long> new_stones;

		for (auto const& [key, count] : stones)
			transform(key, count, new_stones);

		stones = move(new_stones);

	}

	long sum = 0;

	for (auto const& [key, count] : stones)
		sum += count;

	cout << sum << endl;

}
