#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Node {char value; vector<Node*> edges; vector<bool> visited, is_horizontal; int id;};

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
			nodes.push_back({c, {}, {}, {}, 0});

	}

	return move(nodes);

}

void check_and_connect(Node * const a, Node * const b, bool is_horizontal) {

	if (b->value == a->value) {

		a->edges.push_back(b);
		b->edges.push_back(a);

		a->is_horizontal.push_back(is_horizontal);
		b->is_horizontal.push_back(is_horizontal);

		a->visited.push_back(false);
		b->visited.push_back(false);

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

int count_sides(Node *n, Node *prev, bool is_first=true, bool prev_is_horizontal=false, int s = 0) {

	int i = 0;

	while (i < n->edges.size() && (n->visited[i] || n->edges[i]->edges.size() == 4 || n->edges[i] == prev))
		i++;

	
	if (i == n->edges.size()) { // try again but allowing == prev
		
	  i = 0;

	  while (i < n->edges.size() && (n->visited[i] || n->edges[i]->edges.size() == 4))
			i++;

	}

	if (i == n->edges.size())
		return s;

	n->visited[i] = true;

	if (!is_first && n->is_horizontal[i] != prev_is_horizontal)
	  s++;

	return s + count_sides(n->edges[i], n, false, n->is_horizontal[i], s);

}

void measure(Node *n, map<int, int> & area, map<int, int> & n_sides) {

	if (area.find(n->id) == area.end())
		area[n->id] = 1;
	else
		area[n->id]++;

	if (n->edges.size() < 4 && n_sides.find(n->id) == n_sides.end())
		n_sides[n->id] = count_sides(n, nullptr);

}

int main() {

	int len;

	vector<Node> nodes = read_nodes("example.txt", len);

	connect_nodes(nodes, len);
	
	int id = 0;

	for (Node & n : nodes)
		traverse(&n, ++id);

	map<int, int> area, n_sides;

	for (Node & n : nodes)
		measure(&n, area, n_sides);

	int sum = 0;

	for (auto const& [id, a] : area)
		sum += a * n_sides[id];

	cout << sum << endl;

}
