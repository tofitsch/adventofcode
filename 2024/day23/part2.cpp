#include <iostream>
#include <fstream>
#include <map>
#include <set>

using namespace std;

struct Node {

	string name;

	set<string> edges{};

};

map<string, Node> read_graph(string const& in_file_name) {

	map<string, Node> graph;

	ifstream in_file(in_file_name);

	string line;

	while (getline(in_file, line))
		graph[line.substr(0, 2)] = {};

	in_file.clear();
  in_file.seekg(0, ios::beg);

	while (getline(in_file, line)) {

		graph[line.substr(0, 2)].edges.insert(line.substr(3, 2));
		graph[line.substr(3, 2)].edges.insert(line.substr(0, 2));

	}

	return graph;

}

set<string> set_union(set<string> a, string b) {

	a.insert(b);

	return a;

}

set<string> set_intersect(set<string> & a, set<string> & b) {

	set<string> c;

	for (string x : a)
		if (b.find(x) != b.end())
			c.insert(x);

	return c;

}

string recurse(map<string, Node> & graph, set<string> r, set<string> p, set<string> x) {

	cout << r.size() << endl;

	if (p.empty() && x.empty()) {

		string max_clique = "";
		
		for (const string& v : r)
			max_clique += v + ",";

		max_clique.pop_back();

		return max_clique;

	}

	if (! p.empty()) {

		for (set<string>::iterator it = p.begin(); it != p.end(); ) {

  	  string v = *it;

			recurse(graph, set_union(r, v), set_intersect(p, graph[v].edges), set_intersect(x, graph[v].edges));

			x.insert(v);

			it = p.erase(it);

		}

	}

}

string bron_kerbosch(map<string, Node> & graph) {

	set<string> r, p, x;

	for (auto & [name, node] : graph)
		p.insert(name);

	return recurse(graph, r, p, x);

}

int main() {

	map<string, Node> graph = read_graph("example.txt");

	cout << bron_kerbosch(graph) << endl;

}
