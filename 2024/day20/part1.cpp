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

		check_and_connect(coord, {coord.y - 1, coord.x}, nodes);
		check_and_connect(coord, {coord.y, coord.x + 1}, nodes);
		check_and_connect(coord, {coord.y + 1, coord.x}, nodes);
		check_and_connect(coord, {coord.y, coord.x - 1}, nodes);

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

	map<Coord, Node> nodes = read_nodes("example.txt");

	Node *start, *end;

	connect_nodes(nodes, start, end);

	cout << dijkstra(start, end, nodes) << endl;
	
}
