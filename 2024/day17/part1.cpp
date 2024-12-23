#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct Computer {

	int reg_a, reg_b, reg_c;

	vector<int> program;

	Computer(string const& in_file_name);

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

	int out = 1;

	while (exp-- > 0)
		out *= base;

	return out;

}

string Computer::run() {

	string output = "";

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
			case 5: output += to_string(combo % 8) + ","; break;
			case 6: reg_b = reg_a / ipow(2, combo); break;
			case 7: reg_c = reg_a / ipow(2, combo); break;

		};

	}

	output.pop_back();

	return output;

}

int main() {

	Computer computer("input.txt");

	cout << computer.run() << endl;

}
