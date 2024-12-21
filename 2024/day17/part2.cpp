#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct Computer {

	int reg_a, reg_b, reg_c, idx = 0;

	vector<int> program;

	Computer(string const& in_file_name);

	int step();
	string run();

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

int Computer::step() {

	while (idx < program.size()) {

		int opcode = program[idx];
		int literal = program[idx + 1];
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
			case 3: if(reg_a != 0) idx = literal - 2; break;
			case 4: reg_b ^= reg_c; break;
			case 5: idx += 2; return combo % 8;
			case 6: reg_b = reg_a / ipow(2, combo); break;
			case 7: reg_c = reg_a / ipow(2, combo); break;

		};

		idx += 2;

	}

	return -1;

}

string Computer::run() {

	string output = "";

	idx = 0;

	int out;

	while ((out = step()) >= 0)
		output += to_string(out) + ",";

	output.pop_back();

	return output;

}

int main() {

	Computer computer("input.txt");

	cout << computer.run() << endl;

}
