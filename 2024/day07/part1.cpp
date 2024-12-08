#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

long solve(string const & line) {

	stringstream line_stream{line};

	string field;

	line_stream >> field;

	long target = stol(field);

	vector<long> numbers;

	while (line_stream >> field)
		numbers.push_back(stol(field));

	long const n_ops = numbers.size() - 1;

	for (long num = 0; num < pow(2, n_ops); num++) {

		long result = numbers.at(0);

	  for (char bit = 0; bit < n_ops; bit++) {

			if (num >> bit & 1)
				result += numbers.at(bit + 1);
			else
				result *= numbers.at(bit + 1);

			if (result > target)
				break;

		}

		if (target == result)
			return target;

	}

	return 0;

}

int main() {
  
  string line;

	ifstream in_file("input.txt");

	long count = 0;

  while(getline(in_file, line))
    count += solve(line);

	cout << count << endl;

}
