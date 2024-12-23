#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
#include <set>
#include <math.h>

using namespace std;

struct Computer {

	int reg_a, reg_b, reg_c;

	vector<int> program;

	Computer(string const& in_file_name);

	vector<int> run(int a);

	int find_quine();

};

int get_int(string const& line) {

	string field;

  stringstream line_stream(line);

	getline(line_stream, field, ':');
	getline(line_stream, field, ':');

	return stoi(field);

}

vector<int> get_int_vec(string const& line) {

	vector<int> vec;

	string field;

  stringstream line_stream(line);

	getline(line_stream, field, ':');
	getline(line_stream, field, ':');

  stringstream field_stream(field);

	while(getline(field_stream, field, ','))
		vec.push_back(stoi(field));

	return vec;

}

Computer::Computer(string const& in_file_name) {

	ifstream in_file(in_file_name);

	string line;

	getline(in_file, line);
	reg_a = get_int(line);

	getline(in_file, line);
	reg_b = get_int(line);

	getline(in_file, line);
	reg_c = get_int(line);

	getline(in_file, line);

	getline(in_file, line);
	program = get_int_vec(line);

}

int ipow(int base, int exp) {

	return static_cast<int>(pow(base, exp));

}

vector<int> Computer::run(int a) {

	reg_a = a;

	vector<int> output;

	for (int i = 0; i < program.size(); i += 2) {

		int opcode = program[i];
		int literal = program[i + 1];
		int combo = literal;

		switch (combo) {

			case 4: combo = reg_a; break;
			case 5: combo = reg_b; break;
			case 6: combo = reg_c; break;

		};

		switch (opcode) {

			case 0: reg_a /= ipow(2, combo); break;
			case 1: reg_b ^= literal; break;
			case 2: reg_b = combo % 8; break;
			case 3: if(reg_a != 0) i = literal - 2; break;
			case 4: reg_b ^= reg_c; break;
			case 5: output.push_back(combo % 8); break;
			case 6: reg_b = reg_a / ipow(2, combo); break;
			case 7: reg_c = reg_a / ipow(2, combo); break;

		};

	}

	return output;

}

long oct_stol(string const& str) {

	return stol(str, nullptr, 8);

}

bool last_n_match(vector<int> const& a, vector<int> const& b, int n) {

	for (int i = 0; i < n; i++)
		if (a[a.size() - 1 - i] != b[b.size() - 1 - i])
			return false;

	return true;

}

int Computer::find_quine() {

	set<string> valids = {""};

	for (int n = 1; n <= program.size(); n++) {

		set<string> new_valids;

		for (string const& str : valids) {

			for (char c = '0'; c <= '7'; c++)
			 	if (last_n_match(run(oct_stol(str + c)), program, n))
					new_valids.insert(str + c);

		}

		valids = new_valids;

	}

	long min = numeric_limits<long>::max();

	for (string const& str : valids) {

		int x = oct_stol(str);

		if (x < min)
			min = x;

	}

	return min;

}

int main() {

	Computer computer("input.txt");

	cout << computer.find_quine() << endl;

}
