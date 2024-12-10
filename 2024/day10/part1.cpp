#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

struct Node {char value; vector<Node*> edges;};

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
			nodes.push_back({c, {}});

  }

  return move(nodes);

}

void check_and_connect(Node * const a, Node * const b) {

	switch (b->value - a->value) {
		case  1: a->edges.push_back(b); break;
		case -1: b->edges.push_back(a); break;
	};

}

vector<Node*> connect_nodes(vector<Node> & nodes, int len) { 

	vector<Node*> start_nodes;

	for (int i=0; i < nodes.size(); i++) {

		if (nodes[i].value == '0')
			start_nodes.push_back(& nodes[i]);

		if (i % len > 0)
		  check_and_connect(& nodes[i], & nodes[i - 1]);

		if (i >= len)
			check_and_connect(& nodes[i], & nodes[i - len]);

	}

	return move(start_nodes);

}

void traverse(Node *n, set<Node*> & heads) {

	if(! heads.insert(n).second)
		return;

	for (Node *e : n->edges)
		traverse(e, heads);

}

int score(Node *n) {

	set<Node*> heads;

	traverse(n, heads);

	int count = 0;

	for (Node * h : heads)
		if (h->value == '9')
			count++;

	return count;

}

int main() {

	int len;

	vector<Node> nodes = read_nodes("input.txt", len);

	vector<Node*> start_nodes = connect_nodes(nodes, len);

	int sum = 0;

	for (Node * n : start_nodes)
		sum += score(n);
  
	cout << sum << endl;

}
