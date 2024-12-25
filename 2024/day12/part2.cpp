#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>

using namespace std;

struct Coord{

	int y, x;

	bool const operator < (Coord const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

};

struct Node {

	char value;

	vector<Node*> edges;

	vector<Node*> neighbors;

	int id;

	Coord coord;

};

vector<Node> read_nodes(string const& file_name, int & len) {

	fstream in_file(file_name);

	string line;

	vector<Node> nodes;

	bool first_line = true;

	int y = 0;

	while(getline(in_file, line)) {

		if (first_line) {

			len = line.size();

			first_line = false;

		}

		int x = 0;

		for (char c : line) {

			nodes.push_back({c, {}, {}, 0, {y, x}});

			x++;

			for (int i=0; i < 4; i++)
				nodes.back().neighbors.push_back(nullptr);

		}

		y++;

	}

	return move(nodes);

}

void check_and_connect(Node * const a, Node * const b, bool horizontally) {

	if (horizontally) {
		a->neighbors[3] = b;
		b->neighbors[1] = a;
	} else {
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

	vector<set<Coord>> fence_segments;

	void merge_fence_segments();

};

Coord neighbor_coord(Coord const& c, int i) {

	switch (i) {
		case 0: return {c.y - 1, c.x};
		case 1: return {c.y, c.x + 1};
		case 2: return {c.y + 1, c.x};
		case 3: return {c.y, c.x - 1};
	};

	return {-2, -2};

}

void Plot::merge_fence_segments() {

	for (int i = 0; i < 4; i++) {

		set<Coord> s = fence_segments[i];

		for (Coord c : s)
			do {c = neighbor_coord(c, (i + 1) % 4);}
			while (fence_segments[i].erase(c) > 0);

	}

}


map<int, Plot> form_plots(vector<Node> const& nodes) {

	map<int, Plot> plots;

	for (Node const& n : nodes) {

		if (plots.find(n.id) == plots.end())
			plots[n.id] = {n.id, 0, {{}, {}, {}, {}}};

		plots[n.id].area++;

		for (int i=0; i < 4; i++)
			if (n.neighbors[i] == nullptr || n.neighbors[i]->id != n.id)
				plots[n.id].fence_segments[i].insert(neighbor_coord(n.coord, i));
	
	}

	for (auto & [id, plot] : plots)
		plot.merge_fence_segments();

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

	for (auto const& [id, plot] : plots) {

		int n_segments = 0;

		for (int i = 0; i < 4; i++)
			n_segments += plot.fence_segments[i].size();

		sum += plot.area * n_segments;

	}

	cout << sum << endl;

}
