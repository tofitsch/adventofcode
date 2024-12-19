#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

void read_file(string in_file_name, vector<string> &towels, vector<string> &patterns) {

	string line, field;

	ifstream in_file(in_file_name);

	getline(in_file, line);

	stringstream line_stream(line);

	while (getline(line_stream, field, ' ')) {

		towels.push_back(field);

		if (towels.back().back() == ',')
			towels.back().pop_back();

	}

	getline(in_file, line);

	while (getline(in_file, line))
		patterns.push_back(line);

}

bool solve(string const& pattern, vector<string> const& towels) {

	return false;

}

int main() {

	vector<string> towels, patterns;

	read_file("example.txt", towels, patterns);

	int ctr = 0;

	for (string const& pattern : patterns)
		if (solve(pattern, towels))
			ctr++;

	cout << ctr << endl;

}
