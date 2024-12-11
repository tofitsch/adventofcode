#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

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

void transform(vector<long> & vec, int i) {

	if (vec[i] == 0) {
		vec[i]++;
		return;
	}

	if (n_digits(vec[i]) % 2 == 0) {
		vec.push_back(split_digits(vec[i]));
		return;
	}

	vec[i] *= 2024;

}

vector<long> get_vec(string const& in_file_name) {

	string line, field;

	fstream in_file(in_file_name);

	getline(in_file, line);

	stringstream line_stream(line);

	vector<long> vec;

	while (getline(line_stream, field, ' '))
		vec.push_back(stol(field));

	return move(vec);

}

int main () {

	int const n_steps = 25;

	vector<long> vec = get_vec("input.txt");

  int n = vec.size();

	for (int s = 0; s < n_steps; s++) {

		for (int i = 0; i < n; i++)
			transform(vec, i);

		n = vec.size();

	}

	cout << n << endl;

}
