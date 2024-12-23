#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <list>
#include <algorithm>

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

void recurse(map<string, Node> & graph, list<string> r, list<string> p, list<string> x, vector<string> & max_cliques) {

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

		recurse(graph, r_next, p_next, x_next, max_cliques);

		p.remove(v);
		x.push_front(v);

	}

	if (p.empty() && x.empty()) {

		string max_clique = "";
		
		for (string const& v : r)
			max_clique += v + ",";

		max_clique.pop_back();

		max_cliques.push_back(max_clique);

	}

}

string bron_kerbosch(map<string, Node> & graph) {

	vector<string> max_cliques;

	list<string> r, p, x;

	for (auto & [name, node] : graph)
		p.push_front(name);

	recurse(graph, r, p, x, max_cliques);

	auto by_length = [](const string& a, const string& b) {

		return a.length() < b.length();

	};

	sort(max_cliques.begin(), max_cliques.end(), by_length);

	return max_cliques.back();

}

int main() {

	map<string, Node> graph = read_graph("input.txt");

	cout << bron_kerbosch(graph) << endl;

}
