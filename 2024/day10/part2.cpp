#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct Node {char value; vector<Node*> edges; int n_visits;};

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

	switch (b->value - a->value) {
		case  1: a->edges.push_back(b); break;
		case -1: b->edges.push_back(a); break;
	};

}

void connect_nodes(vector<Node> & nodes, vector<Node*> & start_nodes, vector<Node*> & end_nodes, int len) { 

	for (int i=0; i < nodes.size(); i++) {

		if (nodes[i].value == '0')
			start_nodes.push_back(& nodes[i]);
		else if (nodes[i].value == '9')
			end_nodes.push_back(& nodes[i]);

		if (i % len > 0)
			check_and_connect(& nodes[i], & nodes[i - 1]);

		if (i >= len)
			check_and_connect(& nodes[i], & nodes[i - len]);

	}

}

void traverse(Node *n) {

	n->n_visits++;

	for (Node *e : n->edges)
		traverse(e);

}

int main() {

	int len;

	vector<Node> nodes = read_nodes("input.txt", len);

	vector<Node*> start_nodes, end_nodes;

	connect_nodes(nodes, start_nodes, end_nodes, len);

	int sum = 0;

	for (Node * n : start_nodes)
		traverse(n);

	for (Node * n : end_nodes)
		sum += n->n_visits;

	cout << sum << endl;

}
