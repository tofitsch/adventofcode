#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Node {

	char value;

	vector<Node*> edges;

	vector<Node*> neighbors;

	int id;

};

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

		for (char c : line) {

			nodes.push_back({c, {}, {}, 0});

			for (int i=0; i < 4; i++)
				nodes.back().neighbors.push_back(nullptr);

		}

	}

	return move(nodes);

}

void check_and_connect(Node * const a, Node * const b, bool horizontally) {

	if (horizontally) {
		a->neighbors[3] = b;
		b->neighbors[1] = a;
	}
	else {
		a->neighbors[0] = b;
		b->neighbors[2] = a;
	}

	if (b->value == a->value) {
		a->edges.push_back(b);
		b->edges.push_back(a);
	};

}

void connect_nodes(vector<Node> & nodes, int len) { 

	for (int i=0; i < nodes.size(); i++) {

		if (i % len > 0)
			check_and_connect(& nodes[i], & nodes[i - 1], true);

		if (i >= len)
			check_and_connect(& nodes[i], & nodes[i - len], false);

	}

}

void traverse(Node *n, int id) {

	if (n->id > 0)
		return;

	n->id = id;

	for (Node *e : n->edges)
		traverse(e, id);

}

struct Plot {

	int id;

	int area;

	vector<vector<Node *>> fence_segments;

	void merge_fence_segments();

	void print() { //XXX

		for (int i=0; i < 4; i++) {

			cout << "Border " << i << " of plot " << id << ": ";

			for (Node *n : fence_segments[i])
				cout << n->id << " ";

			cout << endl;

		}

	}

};

void Plot::merge_fence_segments() {

	// TODO

}

map<int, Plot> form_plots(vector<Node> const& nodes) {

	map<int, Plot> plots;

	for (Node const& n : nodes) {

		if (plots.find(n.id) == plots.end())
			plots[n.id] = {n.id, 0, {{}, {}, {}, {}}};

		plots[n.id].area++;

		for (int i=0; i < 4; i++)
			if (n.neighbors[i] != nullptr && n.neighbors[i]->id != n.id)
				plots[n.id].fence_segments[i].push_back(n.neighbors[i]);
	
	}

	return plots;

}

int main() {

	int len;

	vector<Node> nodes = read_nodes("input.txt", len);

	connect_nodes(nodes, len);
	
	int id = 0;

	for (Node & n : nodes)
		traverse(&n, ++id);

	map<int, Plot> plots = form_plots(nodes);

	int sum = 0;

	for (auto & [id, plot] : plots)
		plot.print();

	for (auto const& [id, plot] : plots) {

		int n_segments = 0;

		for (int i=0; i < 4; i++)
			n_segments += plot.fence_segments[i].size();

		sum += plot.area * n_segments;

	}

	cout << sum << endl;

}
