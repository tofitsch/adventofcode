#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Gate;

struct Wire {

	string name;

	bool active, val;

	vector<Gate *> targets;

	void propagate();

};

struct Gate {

	enum class Type {AND, OR, XOR} type;

	Wire *in_a, *in_b, *out;

	vector<Gate *> out_gates;

	void propagate();

};

void Gate::propagate() {

	if (! in_a->active || ! in_b->active)
		return;

	switch (type) {

		case Type::AND : out->val = (in_a->val && in_b->val); break;
		case Type::OR  : out->val = (in_a->val || in_b->val); break;
		case Type::XOR : out->val = (in_a->val != in_b->val); break;

	};

	out->active = true;

	out->propagate();

}

void Wire::propagate() {

	if (! active)
		return;

	for (Gate * target : targets)
		target->propagate();

}

struct Network {

	map<string, Wire> wires;
	vector<Gate> gates;

	vector<Wire *> inputs;

	Network(string const& in_file_name);

	void read_wires(string const& in_file_name);
	void read_gates(string const& in_file_name);

	void connect_inputs();
	void connect_targets();

	long output();

};

Network::Network(string const& in_file_name) {

	read_wires(in_file_name);
	read_gates(in_file_name);

	connect_inputs();
	connect_targets();

	for (Wire * wire : inputs)
		wire->propagate();

}

void Network::connect_inputs() {

	for (auto const& [name, wire] : wires)
		if (wire.active)
			inputs.push_back(& wires[name]);

}

void Network::connect_targets() {

	for (Gate & gate : gates) {

		gate.in_a->targets.push_back(& gate);
		gate.in_b->targets.push_back(& gate);

	}

}

void Network::read_wires(string const& in_file_name) {

	ifstream in_file(in_file_name);

	string line;

	while (getline(in_file, line)) {

		if (line.size() == 0)
			continue;

		if (line[3] == ':') {

			string name = line.substr(0, 3);
			
			wires[name] = {name, true, (line[5] == '1')};

		} else {

			stringstream line_stream(line);

			string field;

			int ctr = 0;

			while (getline(line_stream, field, ' ')) {

				if (ctr++ % 2 == 1)
					continue;

				if (wires.find(field) != wires.end())
					continue;

				wires[field] = {field, false, false};

			}

		}

	}

}

void Network::read_gates(string const& in_file_name) {

	ifstream in_file(in_file_name);

	string line;

	while (getline(in_file, line)) {

		if (line.size() == 0 || line[3] == ':')
			continue;

		stringstream line_stream(line);

		string field;

		Gate gate;

		getline(line_stream, field, ' ');
		gate.in_a = & wires[field];

		getline(line_stream, field, ' ');
		switch (field[0]) {
			case 'A': gate.type = Gate::Type::AND; break;
			case 'O': gate.type = Gate::Type::OR; break;
			case 'X': gate.type = Gate::Type::XOR; break;
		};

		getline(line_stream, field, ' ');
		gate.in_b = & wires[field];

		getline(line_stream, field, ' ');
		getline(line_stream, field, ' ');
		gate.out = & wires[field];

		gates.push_back(gate);

	}

}

long Network::output() {

	string binary;

	for (auto const& [name, wire] : wires)
		if (name[0] == 'z')
			binary += wire.val ? '1' : '0';

  reverse(binary.begin(), binary.end());

	return stol(binary, nullptr, 2);

}

int main() {

	Network network{"input.txt"};

	cout << network.output() << endl;

}
