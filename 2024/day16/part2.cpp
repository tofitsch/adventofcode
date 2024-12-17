#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

using namespace std;

struct Coord {

	int y, x, d;

	bool const operator < (Coord const& other) const {
		return tie(y, x, d) < tie(other.y, other.x, other.d);
	}

};

struct Tile {

	int y, x;

	bool const operator < (Tile const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

};

struct Node {

	char value;

	Tile tile;

	vector<Node*> edges {};
	vector<int> weights {};

	vector<Node*> previous{};

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
				for (char d = 0; d < 4; d++)
					nodes[{y, x, d}] = {c, {y, x}};

			x++;

		}

		y++;

	}

	return nodes;

}

void check_and_connect(Coord const& a, Coord const& b, int weight, map<Coord, Node> & nodes) {

	if (nodes.find(a) == nodes.end() || nodes.find(b) == nodes.end())
		return;

	nodes[a].edges.push_back(& nodes[b]);
	nodes[a].weights.push_back(weight);

}

int mod(int a, int b) {

	while (a < 0)
		a += b;

	return a % b;

}

Node * connect_nodes(map<Coord, Node> & nodes, vector<Node*> & ends) { 

	Node * start = nullptr;

	for (auto & [coord, node] : nodes) {

		if (node.value == 'S' && coord.d == 1)
			start = & node;

		else if (node.value == 'E')
			ends.push_back(& node);

		switch (coord.d) {
			case 0: check_and_connect(coord, {coord.y - 1, coord.x, 0}, 1, nodes); break;
			case 1: check_and_connect(coord, {coord.y, coord.x + 1, 1}, 1, nodes); break;
			case 2: check_and_connect(coord, {coord.y + 1, coord.x, 2}, 1, nodes); break;
			case 3: check_and_connect(coord, {coord.y, coord.x - 1, 3}, 1, nodes); break;
		}

		check_and_connect(coord, {coord.y, coord.x, mod(coord.d + 1, 4)}, 1000, nodes);
		check_and_connect(coord, {coord.y, coord.x, mod(coord.d - 1, 4)}, 1000, nodes);

	}

	return start;

}

void dijkstra(Node * start, map<Coord, Node> & nodes) {

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
				
				int distance_update = node->distance + node->weights[i];

				if (distance_update <= node->edges[i]->distance) {

				  if (distance_update < node->edges[i]->distance)
						node->edges[i]->previous.clear();

					node->edges[i]->previous.push_back(node);
				
					node->edges[i]->distance = distance_update;
				
				}
			
			}
		}

	}

}

void traverse(Node const* node, set<Tile> & tiles) {

	tiles.insert(node->tile);

	for (Node const* prev: node->previous)
		traverse(prev, tiles);

}

int count_tiles_on_best_paths(vector<Node*> ends) {

	set<Tile> tiles;

	int min_dist = numeric_limits<int>::max();

	for (Node const* end : ends)
		if (end->distance < min_dist)
			min_dist = end->distance;

	for (Node const* end : ends)
		if (end->distance == min_dist)
			traverse(end, tiles);

	return tiles.size();
	
}

int main() {

	map<Coord, Node> nodes = read_nodes("input.txt");

	vector<Node*> ends;

	Node *start = connect_nodes(nodes, ends);

	dijkstra(start, nodes);

	cout << count_tiles_on_best_paths(ends) << endl;

}
