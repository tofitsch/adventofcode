#include <iostream>
#include <fstream>
#include <vector>
#include <map>

using namespace std;

struct Coord {

	int y, x, d;

	bool const operator < (Coord const& other) const {
		return y < other.y ? true :
			y > other.y ? false : 
				x < other.x ? true :
					x > other.x ? false :
						d < other.d;
	}

};

struct Node {char value; vector<Node*> edges; vector<int> weights;};

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
					nodes[{y, x, d}] = {c, {}, {}};

		  x++;

		}

		y++;

	}

	return nodes;

}

void connect(Node * const a, Node * const b, int weight) {

	a->edges.push_back(b);
	a->weights.push_back(weight);

}

Node * connect_nodes(map<Coord, Node> & nodes) { 

	Node * start = nullptr;

	return start;

}

int main() {

	map<Coord, Node> nodes = read_nodes("example.txt");

	Node *start = connect_nodes(nodes);
	
}
