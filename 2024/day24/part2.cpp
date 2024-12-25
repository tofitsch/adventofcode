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

};

struct Gate {

	enum class Type {AND, OR, XOR} type;

	Wire *in_a, *in_b, *out;

	bool is_faulty(map<string, Gate *> & gates_map);
	bool other_xor_has_this_input(map<string, Gate *> & gates_map);

};

bool Gate::other_xor_has_this_input(map<string, Gate *> & gates_map) {
	
	for (auto const& [name, gate] : gates_map)
		if (gate->type == Type::XOR && (gate->in_a == out || gate->in_b == out))
			return true;

	return false;

}

bool Gate::is_faulty(map<string, Gate *> & gates_map) {

	Gate * last_out = gates_map.rbegin()->second;

	if (
			out->name[0] == 'z' &&
			this != last_out &&
			type != Type::XOR
	 	 )
		return true;

	if (
			out->name[0] != 'z' &&
		 	in_a->name[0] != 'x' &&
			in_a->name[0] != 'y' &&
		 	in_b->name[0] != 'x' &&
			in_b->name[0] != 'y' &&
			type == Type::XOR
		 )
		return true;

	if (
			type == Type::XOR &&
		 	( (in_a->name[0] == 'x' && in_b->name[0] == 'y') ||
				(in_a->name[0] == 'y' && in_b->name[0] == 'x')
			) &&
			! other_xor_has_this_input(gates_map)
		 )
		return true;

	return false;

}

struct Network {

	map<string, Wire> wires;
	vector<Gate> gates;

	vector<Wire *> inputs;

	map<string, Gate *> gates_map; //XXX

	vector<bool *> in_x, in_y, out_z;

	Network(string const& in_file_name);

	void read_wires(string const& in_file_name);
	void read_gates(string const& in_file_name);

	void connect_inputs(); //XXX
	void connect_targets();

	string find_faults();

};

Network::Network(string const& in_file_name) {

	read_wires(in_file_name);
	read_gates(in_file_name);

	connect_inputs();
	connect_targets();

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

	for (Gate & gate : gates)
		gates_map[gate.out->name] = & gate;

}

string Network::find_faults() {

	set<string> faults;

	for (Gate & gate : gates)
		if (gate.is_faulty(gates_map))
			faults.insert(gate.out->name);

	string output{""};

	for (string const& fault : faults)
		output += fault + ",";

	if (output.size() > 0)
		output.pop_back();

	return output;

}

int main() {

	Network network{"input.txt"};

	cout << network.find_faults() << endl;

}
