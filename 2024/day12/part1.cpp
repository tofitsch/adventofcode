#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Node {char value; vector<Node*> edges; int id;};

vector<Node> read_nodes(string const& file_name, int & len) {

	fstream in_file(file_name);

	string line;

	vector<Node> nodes;

	bool first_line = true;

	while(getline(in_file, line)) {

		if (first_line) {

			len = line.size();

			first_line = false;

		}

		for (char c : line)
			nodes.push_back({c, {}, 0});

	}

	return move(nodes);

}

void check_and_connect(Node * const a, Node * const b) {

	if (b->value == a->value) {
		a->edges.push_back(b);
		b->edges.push_back(a);
	};

}

void connect_nodes(vector<Node> & nodes, int len) { 

	for (int i=0; i < nodes.size(); i++) {

		if (i % len > 0)
			check_and_connect(& nodes[i], & nodes[i - 1]);

		if (i >= len)
			check_and_connect(& nodes[i], & nodes[i - len]);

	}

}

void traverse(Node *n, int id) {

	if (n->id > 0)
		return;

	n->id = id;

	for (Node *e : n->edges)
		traverse(e, id);

}

void measure(Node const * const n, map<int, int> & area, map<int, int> & perimeter) {

	if (area.find(n->id) == area.end()) {

		area[n->id] = 1;
		perimeter[n->id] = 4 - n->edges.size();

	} else {

		area[n->id]++;
		perimeter[n->id] += 4 - n->edges.size();

	}

}

int main() {

	int len;

	vector<Node> nodes = read_nodes("input.txt", len);

	connect_nodes(nodes, len);
	
	int id = 0;

	for (Node & n : nodes)
		traverse(&n, ++id);

	map<int, int> area, perimeter;

	for (Node const& n : nodes)
		measure(&n, area, perimeter);

	int sum = 0;

	for (auto const& [id, a] : area)
		sum += a * perimeter[id];

	cout << sum << endl;

}
