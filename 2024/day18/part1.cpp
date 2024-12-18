#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <limits>

using namespace std;

int const n_x = 71;
int const n_y = 71;
int const n_bytes = 1024;

struct Coord {

	int y, x;

	bool const operator < (Coord const& other) const {
		return tie(y, x) < tie(other.y, other.x);
	}

};

struct Node {

	int distance = numeric_limits<int>::max();
	bool active{true}, visited{false};
	vector<Node*> edges{};

};

bool distance_decreasing(const Node * a, const Node * b){

	return a->distance > b->distance;

}

void deactivate_nodes(string const& file_name, map<Coord, Node> & nodes) {

	ifstream in_file(file_name);

	string line, field;

	for (int i = 0; i < n_bytes; i++) {

		getline(in_file, line);

		stringstream line_stream(line);

		getline(line_stream, field, ',');
		int x = stoi(field);

		getline(line_stream, field, ',');
		int y = stoi(field);

		nodes[{y, x}].active = false;

	}

}

void make_connections(int y, int x, map<Coord, Node> & nodes) {

	if (y > 0)
		nodes[{y, x}].edges.push_back(& nodes[{y - 1, x}]);

	if (y < n_y - 1)
		nodes[{y, x}].edges.push_back(& nodes[{y + 1, x}]);

	if (x > 0)
		nodes[{y, x}].edges.push_back(& nodes[{y, x - 1}]);

	if (x < n_x - 1)
		nodes[{y, x}].edges.push_back(& nodes[{y, x + 1}]);

}

map<Coord, Node> make_graph() {

  map<Coord, Node> nodes;

	for (int y = 0; y < n_y; ++y)
		for (int x = 0; x < n_x; ++x)
			nodes[{y, x}] = Node{};

	for (auto & [coord, node] : nodes)
		make_connections(coord.y, coord.x, nodes);

	return nodes;

}

int dijkstra(Coord coord_start, Coord coord_end, map<Coord, Node> & nodes) {

	vector<Node *> queue;

	for (auto & [coord, node] : nodes)
		if (node.active)
			queue.push_back(& node);

	nodes[coord_start].distance = 0;

	Node const* end = & nodes[coord_end];
	
	while (! queue.empty()){
	
		sort(queue.begin(), queue.end(), distance_decreasing);
		
		Node * node = queue.back();
		
		node->visited = true;
		
		queue.pop_back();
		
		int ctr = 0;
		
		for (int i = 0; i < node->edges.size(); i++) {
			if (node->edges[i]->active && ! node->edges[i]->visited) {
				
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

	map<Coord, Node> nodes = make_graph();

	deactivate_nodes("input.txt", nodes);

	cout << dijkstra({0, 0}, {n_y - 1, n_x - 1}, nodes) << endl;

}
