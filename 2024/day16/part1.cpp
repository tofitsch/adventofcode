#include <iostream>
#include <fstream>
#include <limits>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Coord {

	int y, x, d;

	bool const operator < (Coord const& other) const {
		return tie(y, x, d) < tie(other.y, other.x, other.d);
	}

};

struct Node {

	char value;

	vector<Node*> edges {};
	vector<int> weights {};

	int distance = numeric_limits<int>::max();
	bool visited = false;

	bool const operator < (Node const& other) const {
		return distance < other.distance;
	}

};

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
					nodes[{y, x, d}] = {c};

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

	int r = a % b;

	return r < 0 ? r + b : r;

}

Node * connect_nodes(map<Coord, Node> & nodes) { 

	Node * start = nullptr;

	for (auto & [coord, node] : nodes) {

		if (node.value == 'S' && coord.d == 1)
			start = & node;

		switch (coord.d) {
			case 0: check_and_connect(coord, {coord.y - 1, coord.x, 0}, 1, nodes);
			case 1: check_and_connect(coord, {coord.y, coord.x + 1, 1}, 1, nodes);
			case 2: check_and_connect(coord, {coord.y + 1, coord.x, 2}, 1, nodes);
			case 3: check_and_connect(coord, {coord.y + 1, coord.x, 3}, 1, nodes);
		}

		check_and_connect(coord, {coord.y, coord.x, mod(coord.d + 1, 4)}, 1000, nodes);
		check_and_connect(coord, {coord.y, coord.x, mod(coord.d - 1, 4)}, 1000, nodes);

	}

	return start;

}

int dijkstra(Node * start, map<Coord, Node> & nodes) {

  vector<Node *> queue;

	for (auto & [coord, node] : nodes)
		queue.push_back(* node);

  start->distance = 0;

  while (! queue.empty()){
    
    sort(queue.begin(), queue.end());

    Node * node = queue.back();

    node->visited = true;

    queue.pop_back();

    int ctr = 0;

		for (int i = 0; i < node->edges.size(); i++) {
      if(! node->edges[i]->visited){
        
        int distance_update = node->distance + node->weights[i];
          
        if(distance_update < node->edges[i]->distance){
        
          node->edges[i]->distance = distance_update;

					if (node->edges[i]->value == 'E')
						return distance_update;

        }

      }
    }

  }

	return -1;

}

int main() {

	map<Coord, Node> nodes = read_nodes("example.txt");

	Node *start = connect_nodes(nodes);

	cout << dijkstra(start, nodes) << endl;
	
}
