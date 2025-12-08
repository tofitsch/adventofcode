#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

struct Node {

  Node(string const& line) {

    string field;

    stringstream line_stream(line);

    getline(line_stream, field, ',');
    x = stol(field);

    getline(line_stream, field, ',');
    y = stol(field);

    getline(line_stream, field, ',');
    z = stol(field);

  }

  size_t recurse_circuit_size() {

    if (visited)
      return 0;

    visited = true;

    size_t circuit_size{1};

    for (Node * n : neighbours)
      circuit_size += n->recurse_circuit_size();

    return circuit_size;

  }

  void print() const
    {cout << x << " " << y << " " << z;}

  long x, y, z;

  bool visited{false};

  vector<Node *> neighbours;

};

struct Edge{

  Edge(Node * _a, Node * _b)
    : a{_a}, b(_b) {

    distance_squared
      =  (a->x - b->x) * (a->x - b->x)
      +  (a->y - b->y) * (a->y - b->y)
      +  (a->z - b->z) * (a->z - b->z);

  }

  bool operator < (Edge const& other) const
    {return distance_squared < other.distance_squared;}

  void print() const
    {a->print(); cout << " - "; b->print(); cout << " | " << distance_squared << endl;}

  unsigned long distance_squared;

  Node * a, * b;

};

int main() {

  string line;

  ifstream in_file("input.txt");

  vector<Node> nodes;

  while (getline(in_file, line))
    nodes.emplace_back(line);

  vector<Edge> edges;

  for (size_t i = 0; i < nodes.size(); ++i)
    for (size_t j = i + 1; j < nodes.size(); ++j)
        edges.emplace_back(& nodes[i], & nodes[j]);

  sort(edges.begin(), edges.end());

  edges.erase(edges.begin() + 1'000, edges.end());

  for (Edge const& e : edges) {

    e.a->neighbours.push_back(e.b);
    e.b->neighbours.push_back(e.a);

  }

  vector<size_t> circuit_sizes;

  for (Edge const& e : edges) {

    circuit_sizes.push_back(e.a->recurse_circuit_size());
    circuit_sizes.push_back(e.b->recurse_circuit_size());

  }

  sort(circuit_sizes.begin(), circuit_sizes.end());

  size_t product{1};

  for (size_t i = 0; i < 3; ++i)
    product *= * (circuit_sizes.end() - 1 - i);

  cout << product << endl;
}
