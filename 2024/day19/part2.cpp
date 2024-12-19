#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <set>
#include <map>

using namespace std;

void read_file(string in_file_name, set<string> & towels, vector<string> & patterns, int & max_len) {

	string line, field;

	ifstream in_file(in_file_name);

	getline(in_file, line);

	stringstream line_stream(line);

	max_len = 0;

	while (getline(line_stream, field, ' ')) {

		if (field.back() == ',')
			field.pop_back();

		if (field.size() > max_len)
			max_len = field.size();

		towels.insert(field);

	}

	getline(in_file, line);

	while (getline(in_file, line))
		patterns.push_back(line);

}

long solve(string const& pattern, set<string> const& towels, int const max_len, int const offset, map<int, long> & cache) {

	int sum = 0;

	if (offset == pattern.size())
		return 1;

	for (int i = 1; i <= max_len && offset + i <= pattern.size(); i++) {
		if (towels.find(pattern.substr(offset, i)) != towels.end()) {

			if (cache.find(offset + i) == cache.end())
			  cache[offset + i] = solve(pattern, towels, max_len, offset + i, cache);

			sum += cache[offset + i];

		}
	}

	return sum;

}

int main() {

	set<string> towels;
	vector<string> patterns;

	int max_len;

	read_file("input.txt", towels, patterns, max_len);

	long sum = 0;

	for (string const& pattern : patterns) {

		cout << pattern << endl;

		map<int, long> cache;

		long count = solve(pattern, towels, max_len, 0, cache);

		cout << count << endl;

		sum += count;

	}

	cout << sum << endl;

}
