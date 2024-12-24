#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <bitset>
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

	vector<bool *> in_x, in_y, out_z;

	Network(string const& in_file_name);

	void read_wires(string const& in_file_name);
	void read_gates(string const& in_file_name);

	void connect_inputs();
	void connect_targets();
	void connect_bits();

	void print();

};

Network::Network(string const& in_file_name) {

	read_wires(in_file_name);
	read_gates(in_file_name);

	connect_inputs();
	connect_targets();
	connect_bits();

	for (Wire * wire : inputs)
		wire->propagate();

}

void Network::connect_bits() {

	for (auto & [name, wire] : wires) {

		switch (name[0]) {

			case 'x': in_x.push_back(& wire.val); break;
			case 'y': in_y.push_back(& wire.val); break;
			case 'z': out_z.push_back(& wire.val); break;

		};

	}

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

void print_bits(bitset<64> & bits, int n) {

	string str = bits.to_string();

	str = str.substr(str.length() - n);

	cout << str << " " << stol(str, nullptr, 2) << endl;

}

void Network::print() {

	bitset<64> bits_x, bits_y, bits_z;

	for (int i = 0; i < in_x.size(); i++)
  	bits_x[i] = * in_x[i];

	for (int i = 0; i < in_y.size(); i++)
  	bits_y[i] = * in_y[i];

	for (int i = 0; i < out_z.size(); i++)
  	bits_z[i] = * out_z[i];

	long target_z = bits_x.to_ulong() + bits_y.to_ulong();

	bitset<64> bits_target_z(target_z);

	cout << "in_x: ";
	print_bits(bits_x, in_x.size());

	cout << "in_y: ";
	print_bits(bits_y, in_y.size());

	cout << "out_z:    ";
	print_bits(bits_z, out_z.size());

	cout << "target_z: ";
	print_bits(bits_target_z, out_z.size());

}

int main() {

	Network network{"example.txt"};
	
	network.print();

}
