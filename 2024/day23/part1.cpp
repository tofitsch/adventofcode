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

set<set<string>> get_subnets(map<string, Node> & graph) {

	set<set<string>> subnets;

	for (auto & [name, node] : graph)
		for (string const& a : node.edges)
			for (string const& b : node.edges)
				if (a != b)
					if (graph[a].edges.find(b) != graph[a].edges.end())
						subnets.insert({name, a, b});

	return subnets;

}

int count_relevant(set<set<string>> & subnets) {

	int ctr = 0;

	for (set<string>  subnet : subnets) {
		for (string const& name : subnet)
			if (name[0] == 't') {
				ctr++;
				goto next;
			}
		next:;
	}

	return ctr;
}

int main() {

	map<string, Node> graph = read_graph("input.txt");

	set<set<string>> subnets = get_subnets(graph);

	cout << count_relevant(subnets) << endl;

}
