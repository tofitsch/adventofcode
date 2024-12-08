#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

long concat(long a, long b) {
	return a * pow(10, static_cast<long>(log10(b)) + 1) + b;
}

long solve(string const & line) {

//	cout << line << endl;

	stringstream line_stream{line};

	string field;

	line_stream >> field;

	long target = stol(field);

	vector<long> numbers;

	while (line_stream >> field)
		numbers.push_back(stol(field));

	long const n_ops = numbers.size() - 1;

	for (long num = 0; num < pow(2, 2 * n_ops); num++) {

		long result = numbers.at(0);

	  for (long bit = 0; bit < n_ops; bit++) {

			bool const b0 = num >> (2 * bit) & 1;
			bool const b1 = num >> (2 * bit + 1) & 1;

			if (!b0 && !b1) // 00
				result += numbers.at(bit + 1);
			else if (!b0 && b1) // 01
				result *= numbers.at(bit + 1);
			else if (b0 && !b1) // 10
				result = concat(result, numbers.at(bit + 1));
			else // 11
				goto next;

			if (result > target)
				break;

		}

		if (target == result)
			return target;

    next:;

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
