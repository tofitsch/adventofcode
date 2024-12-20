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

int dijkstra(Node * start, Node * end, map<Coord, Node> & nodes) {

	vector<Node *> queue;

	for (auto & [coord, node] : nodes)
		queue.push_back(& node);

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

int main() {

	string const in_file_name = "example.txt";
	
	map<Coord, Node> nodes = read_nodes(in_file_name);

	vector<Coord> shortcuts = read_shortcuts(in_file_name, nodes);

	Node *start, *end;

	connect_nodes(nodes, start, end);

	cout << dijkstra(start, end, nodes) << endl;
	
}
