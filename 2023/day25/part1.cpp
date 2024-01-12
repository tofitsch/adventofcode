#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<algorithm>
#include<cstdlib>

using namespace std;
  
class Graph{

  private:

    struct Edge;

    vector<string> nodes;
    vector<Edge> edges;

    void contract_random_edge();
   
  public:
    
    Graph(string);

    void run_karger(int);

};

struct Graph::Edge{

  string in, out;

  Edge(string in, string out) : in(in), out(out) {}

  bool operator==(const Edge & other){
    return (this->in == other.in && this->out == other.out) ||
           (this->in == other.out && this->out == other.in);
  }

};

Graph::Graph(string in_file_name){
  
  string line, field;

  ifstream in_file(in_file_name);

  while(getline(in_file, line)){
    
    vector<string> fields;
    
    stringstream line_stream(line);

    while(getline(line_stream, field, ' '))
      fields.push_back(field);

    fields[0].pop_back();

    for(string & n : fields){

      if(find(nodes.begin(), nodes.end(), n) == nodes.end())
        nodes.push_back(n);

      if(n == fields[0])
        continue;

      Edge e(fields[0], n);
      if(find(edges.begin(), edges.end(), e) == edges.end())
        edges.push_back(e);

    }

  }
  
}

void Graph::contract_random_edge(){
  
  int id = rand() % edges.size();

  Edge edge = edges[id];
 
  edges.erase(remove(edges.begin(), edges.end(), edge), edges.end());

  nodes.erase(remove(nodes.begin(), nodes.end(), edge.in), nodes.end());
  nodes.erase(remove(nodes.begin(), nodes.end(), edge.out), nodes.end());

  string merged_node = edge.in + ',' + edge.out;

  nodes.push_back(merged_node);

  for(Edge & e : edges){
    
    if(e.in == edge.in || e.in == edge.out)
      e.in = merged_node;

    if(e.out == edge.in || e.out == edge.out)
      e.out = merged_node;

  }

}

void Graph::run_karger(int n_cuts){
  
  vector<string> nodes_original = nodes;
  vector<Edge> edges_original = edges;

  while(edges.size() != n_cuts){

    nodes = nodes_original;
    edges = edges_original;

    while(nodes.size() > 2)
      contract_random_edge();

  }

  int result = 1;

  for(int i=0; i<2; i++){

    int n_nodes = 1;

    for(char c : nodes[i])
      if(c == ',')
        n_nodes++;

    result *= n_nodes;

  }

  cout << result << endl;

}

int main(){
    
  Graph graph("input.txt");

  graph.run_karger(3);

}
