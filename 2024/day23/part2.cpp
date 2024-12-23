#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>

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

void recurse(map<string, Node> & graph, list<string> r, list<string> p, list<string> x) {

	if (p.empty() && x.empty()) {

		string max_clique = "";
		
		for (const string& v : r)
			max_clique += v + ",";

		max_clique.pop_back();

	  cout << max_clique << endl;

		exit(0);

	}

	while (! p.empty()) {

		list<string> r_next = r;
		list<string> p_next = p;
		list<string> x_next = x;

		string const v = p.front();

		r_next.push_front(v);

		auto not_in_edges_v = [&](string const& s) {

			return graph[v].edges.find(s) == graph[v].edges.end();

		};

		p_next.remove_if(not_in_edges_v);
		x_next.remove_if(not_in_edges_v);

		recurse(graph, r_next, p_next, x_next);

		p.remove(v);
		x.push_front(v);

	}

}

void bron_kerbosch(map<string, Node> & graph) {

	list<string> r, p, x;

	for (auto & [name, node] : graph)
		p.push_front(name);

	recurse(graph, r, p, x);

}

int main() {

	map<string, Node> graph = read_graph("example.txt");

	bron_kerbosch(graph);

}
