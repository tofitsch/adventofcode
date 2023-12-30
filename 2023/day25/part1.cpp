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

    void traverse(Edge *);
    int count_subgraphs();

  public:
    
    Graph(string);
    int find_subgraphs();

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

void Graph::traverse(Edge * edge){
  
  if(! edge->active)
    return;

  edge->active = false;

  for(Edge * e : edge->in->edges)
    traverse(e);

  for(Edge * e : edge->out->edges)
    traverse(e);

}

int Graph::count_subgraphs(){
  
  int ctr = 0;
  
  for(Edge & edge : edges){
    
    if(! edge.active)
      continue;

    ctr++;
    
    traverse(& edge);
    
  }

  return ctr;

}

int Graph::find_subgraphs(){
  
  for(Edge & a : edges){
    for(Edge & b : edges){
      for(Edge & c : edges){

        for(Edge & edge : edges)
          edge.active = true;

        a.active = false;
        b.active = false;
        c.active = false;

        if(count_subgraphs() == 2){
          cout << a.in->label << " " << a.out->label << " ";
          cout << b.in->label << " " << b.out->label << " ";
          cout << c.in->label << " " << c.out->label << " ";
          cout << endl;
          exit(0); //TODO
        }

      }
    }
  }

  return 0;

}

int main(){
  
  Graph graph("example.txt");

  cout << graph.find_subgraphs() << endl;

}
