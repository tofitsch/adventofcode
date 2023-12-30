#include<algorithm>
#include<iostream>
#include<fstream>
#include<sstream>
#include<vector>
#include<map>

using namespace std;
  
class Graph{

  private:
    
    struct Edge;
    struct Node;

    map<string, Node> nodes;
    vector<Edge> edges;

    void traverse(Edge *, int &);

  public:
    
    Graph(string);

    void activate_all_edges();
    vector<int> get_subgraph_sizes();

};

struct Graph::Edge{

  Node * in, * out;

  bool active = true;

  Edge(Node * in, Node * out) : in(in), out(out) {}

};

struct Graph::Node{
  
  vector<Edge *> edges;

  string label;

  Node() {}
  Node(string label) : label(label) {}
  
};

Graph::Graph(string in_file_name){
  
  string line, field;

  ifstream in_file(in_file_name);

  vector<vector<string>> lines;

  while(getline(in_file, line)){
    
    lines.push_back({});

    stringstream line_stream(line);

    while(getline(line_stream, field, ' '))
      lines.back().push_back(field);

    lines.back().front().pop_back();

    for(string & label : lines.back())
      if(nodes.find(label) == nodes.end())
        nodes[label] = Node(label);

  }

  for(vector<string> & labels : lines)
    for(int i=1; i<labels.size(); i++)
      edges.push_back(Edge(& nodes[labels[0]], & nodes[labels[i]]));

  for(Edge & edge : edges){
    
    edge.in->edges.push_back(& edge);
    edge.out->edges.push_back(& edge);

  }
    
}

void Graph::activate_all_edges(){

  for(Edge & edge : edges)
    edge.active = true;

}

void Graph::traverse(Edge * edge, int & ctr){
  
  if(! edge->active)
    return;

  ctr++;
  
  edge->active = false;

  for(Edge * e : edge->in->edges)
    traverse(e, ctr);

  for(Edge * e : edge->out->edges)
    traverse(e, ctr);

}

vector<int> Graph::get_subgraph_sizes(){
  
  vector<int> subgraph_sizes;
  
  for(Edge & edge : edges){
    
    int ctr = 0;

    traverse(& edge, subgraph_sizes.back());
    
    if(ctr > 0)
      subgraph_sizes.push_back(ctr);

  }

  return subgraph_sizes;

}

int main(){
  
  Graph graph("example.txt");

  graph.activate_all_edges();

  vector<int> subgraph_sizes = graph.get_subgraph_sizes();

  for(int & s : subgraph_sizes)
    cout << s << endl;

}
