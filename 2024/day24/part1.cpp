#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Wire {

	string name{""};

	bool val{false}, active{false};

};

struct Gate {

	enum class Type {AND, OR, XOR, ID} type;

	Wire in_a, in_b, out;

	void eval();

};

void Gate::eval() {

	switch (type) {

		case Type::ID:  out.val = in_a.val; break;
		case Type::AND: out.val = (in_a.val && in_b.val); break;
		case Type::OR:  out.val = (in_a.val || in_b.val); break;
		case Type::XOR: out.val = (in_a.val != in_b.val); break;

	};

}

struct Network {

	vector<Gate> gates;

	set<string> wire_names;

	map<string, vector<Gate*>> in_a_map, in_b_map, out_map;

	Network(string const& in_file_name);

};

Network::Network(string const& in_file_name) {

	ifstream in_file(in_file_name);

	string line;

	wire_names.insert("");

	while (getline(in_file, line)) {

		if (line.size() == 0)
			continue;

		Gate gate;

		if (line[3] == ':') {

			gate.out.name = line.substr(0, 3);

			wire_names.insert(gate.out.name);

			gate.out.val = (line[5] == '1');

			gate.in_a.active = true;
			gate.in_b.active = true;
			gate.out.active = true;

			gate.type = Gate::Type::ID;

		} else {

			stringstream line_stream(line);

			string field;

			getline(line_stream, field, ' ');
			gate.in_a.name = field;
			wire_names.insert(field);

			getline(line_stream, field, ' ');

			switch (field[0]) {

				case 'A': gate.type = Gate::Type::AND; break;
				case 'O': gate.type = Gate::Type::OR; break;
				case 'X': gate.type = Gate::Type::XOR; break;

			};

			getline(line_stream, field, ' ');
			gate.in_b.name = field;
			wire_names.insert(field);

			getline(line_stream, field, ' ');
			getline(line_stream, field, ' ');
			gate.out.name = field;
			wire_names.insert(field);

		}

		gates.push_back(gate);

	}

	for (string const& wire_name : wire_names) {

			in_a_map[wire_name] = {};
			in_b_map[wire_name] = {};
			out_map[wire_name] = {};

	}

	for (Gate & gate : gates) {

		in_a_map[gate.in_a.name].push_back(& gate);
		in_b_map[gate.in_b.name].push_back(& gate);
		out_map[gate.out.name].push_back(& gate);

	}

}

int main() {

	Network network{"example.txt"};

}
