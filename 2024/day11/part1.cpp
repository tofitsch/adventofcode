#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

long n_digits(long in) {return static_cast<long>(log10(in)) + 1;}

long split_digits(long & in) {

	long orig = in;

	long n = n_digits(in) / 2;

	long divisor = static_cast<long>(pow(10, n)); 

	in /= divisor;

	return orig % divisor;

}

struct Node {

	long value;

	Node *l = nullptr, *r = nullptr;

	Node(long v) : value(v) {}
	Node(string str) {value = stol(str);}

	void transform(vector<Node> & nodes) {

		if (value == 0) {
			value++;
			return;
		}

		if (n_digits(value) % 2 == 0) {
			nodes.push_back(Node(split_digits(value)));
			return;
		}

		value *= 2024;

	}

};

int main () {

	int const n_steps = 25;

	string line, field;

	vector<Node> nodes;

	fstream in_file("input.txt");

	getline(in_file, line);

	stringstream line_stream(line);

	while (getline(line_stream, field, ' '))
		nodes.push_back(Node(field));

  int n_nodes = nodes.size();

	for (int s = 0; s < n_steps; s++) {

		for (int i = 0; i < n_nodes; i++)
			nodes[i].transform(nodes);

		n_nodes = nodes.size();

//		cout << s << ": " << n_nodes << endl;

	}

//	for (Node & n : nodes)
//		cout << n.value << endl; 

	cout << n_nodes << endl;

}
