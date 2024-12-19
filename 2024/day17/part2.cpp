#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <math.h>

using namespace std;

struct Computer {

	int reg_a, reg_b, reg_c;

	int reg_a_init;

	pair<int, int> max{0, 0};

	vector<int> program;

	string program_str;

	Computer(string const& in_file_name);

	bool run();

	void init(int a);

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

	for (int i = 0; i < 5; i++)
		getline(in_file, line);

	program_str = line;

	program = get_int_vec(line);

	cout << program.size() << endl;

}

void Computer::init(int a) {

	reg_a_init = a;

	reg_a = a;
	reg_b = 0;
	reg_c = 0;

}

int ipow(int base, int exp) {

	return static_cast<int>(pow(base, exp));

}

bool Computer::run() {

	vector<int> output;

	int out_idx = 0;

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
			case 6: reg_b = reg_a / ipow(2, combo); break;
			case 7: reg_c = reg_a / ipow(2, combo); break;

			case 5:

				output.push_back(combo % 8);

				if (output.back() != program[output.size() - 1]) {
					if (output.size() - 1 > max.second) {
						max = {reg_a_init, output.size() - 1};
						cout << max.first << " " << max.second << endl;
					}
					return false;
				}

				if (output.size() == program.size())
					return true;

				break;

		};

	}

	return false;

}

int main() {

	Computer computer("input.txt");

	int a = 0;

  computer.init(a);

	while(! computer.run())
		computer.init(++a);

	cout << a << endl;

}
