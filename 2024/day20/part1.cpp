#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Coord {

	int y, x;

	bool const operator < (Coord const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

};

struct Node {

	char value;

	vector<Node*> edges {};

	int distance = numeric_limits<int>::max();
	bool visited = false;

};

bool distance_decreasing(const Node * a, const Node * b){

	return a->distance > b->distance;

}

map<Coord, Node> read_nodes(string const& file_name) {

	map<Coord, Node> nodes;

	fstream in_file(file_name);

	string line;

	int y = 0;

	while (getline(in_file, line)) {

		int x = 0;

		for (char c : line) {

			if (c != '#')
				nodes[{y, x}] = {c};

			x++;

		}

		y++;

	}

	return nodes;

}

vector<Coord> neighbors(Coord const& coord) {

	return {
		{coord.y - 1, coord.x},
		{coord.y, coord.x + 1},
		{coord.y + 1, coord.x},
		{coord.y, coord.x - 1},
	};

}

int n_neighboring_nodes(Coord const& coord, map<Coord, Node> const& nodes) {

	int ctr = 0;

	for (Coord const& neighbor : neighbors(coord))
		if (nodes.find(neighbor) != nodes.end())
			ctr++;

	return ctr;

}

vector<Coord> read_shortcuts(string const& file_name, map<Coord, Node> const& nodes) {

	vector<Coord> shortcuts;

	fstream in_file(file_name);

	string line;

	int y = 0;

	while (getline(in_file, line)) {

		int x = 0;

		for (char c : line) {

			Coord const coord {y, x};

			if (c == '#' && n_neighboring_nodes(coord, nodes) > 1)
				shortcuts.push_back(coord);

			x++;

		}

		y++;

	}

	return shortcuts;

}

void check_and_connect(Coord const& a, Coord const& b, map<Coord, Node> & nodes) {

	if (nodes.find(a) == nodes.end() || nodes.find(b) == nodes.end())
		return;

	nodes[a].edges.push_back(& nodes[b]);

}

void connect_nodes(map<Coord, Node> & nodes, Node *& start, Node *& end) { 

	for (auto & [coord, node] : nodes) {

		switch (node.value) {
			case 'S': start = & node; break;
			case 'E': end = & node; break;
		}

		for (Coord const& neighbor : neighbors(coord))
			check_and_connect(coord, neighbor, nodes);

	}

}

int dijkstra(Node * start, Node * end, Node * shortcut_node, map<Coord, Node> & nodes) {

	vector<Node *> queue;

	for (auto & [coord, node] : nodes) {

		node.distance = numeric_limits<int>::max();
		node.visited = false;

		queue.push_back(& node);

	}

	shortcut_node->distance = numeric_limits<int>::max();
	shortcut_node->visited = false;

	queue.push_back(shortcut_node);

	start->distance = 0;
	
	while (! queue.empty()){

		sort(queue.begin(), queue.end(), distance_decreasing);
		
		Node * node = queue.back();
		
		node->visited = true;
		
		queue.pop_back();
		
		int ctr = 0;
		
		for (int i = 0; i < node->edges.size(); i++) {
			if (! node->edges[i]->visited) {
				
				int distance_update = node->distance + 1;

				if (distance_update < node->edges[i]->distance) {
				
					node->edges[i]->distance = distance_update;
				
					if (node->edges[i] == end)
						return distance_update;
				
				}
			
			}
		}

	}

	return -1;

}

void add_shortcut(Coord const& shortcut_coord, Node * shortcut_node, map<Coord, Node> & nodes) {

	for (Coord const& neighbor : neighbors(shortcut_coord)) {
		if (nodes.find(neighbor) != nodes.end()) {

			shortcut_node->edges.push_back(& nodes[neighbor]);
			nodes[neighbor].edges.push_back(shortcut_node);

		}
	}

}

void remove_shortcut(Node * shortcut_node, map<Coord, Node> & nodes) {

	for (Node * edge : shortcut_node->edges)
		edge->edges.pop_back();

	shortcut_node->edges.clear();

}

int main() {

	string const in_file_name = "input.txt";
	
	map<Coord, Node> nodes = read_nodes(in_file_name);

	vector<Coord> shortcuts = read_shortcuts(in_file_name, nodes);

	Node *start, *end;

	connect_nodes(nodes, start, end);

	Node shortcut_node;

	for (Coord const& shortcut_coord : shortcuts) {

		add_shortcut(shortcut_coord, & shortcut_node, nodes);

		cout << dijkstra(start, end, & shortcut_node, nodes) << endl;

		remove_shortcut(& shortcut_node, nodes);

	}
	
}
