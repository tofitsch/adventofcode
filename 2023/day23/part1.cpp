#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;
  
class Graph{

  public:
    
    int n_y, n_x;

    int run_dijkstra();

    Graph(string);

  private:
    
    struct Edge;
    struct Node;

    vector<vector<Node>> nodes;

    Node * start_node = nullptr;
    Node * end_node = nullptr;

    string in_file_name;

    int static const infinity = numeric_limits<int>::max();

    void add_nodes();
    void link_nodes();

    bool static distance_decreasing(const Node *, const Node *);

};

Graph::Graph(string in_file_name) : in_file_name(in_file_name) {
  
  add_nodes();

  link_nodes();

}

struct Graph::Edge{

  Node * node;
  int weight;

  Edge(Node * n, int w) : node(n), weight(w) {}

};

struct Graph::Node{
  
  vector<Edge> edges;

  int y, x;

  char c;

  int distance = infinity;
  bool visited = false;
  Node * previous = nullptr;

  Node * reset();
  void link(Node *, int);

  Node(int y, int x, char c) : y(y), x(x), c(c) {}
  
};

Graph::Node * Graph::Node::reset(){

  distance = infinity;
  visited = false;
  previous = nullptr;

  return this;

}

void Graph::Node::link(Node * node, int weight){
  
  edges.push_back(Edge(node, weight));

}

void Graph::add_nodes(){
  
  string line;

  ifstream in_file(in_file_name);

  while(getline(in_file, line)){
    
    nodes.push_back({});

    for(char & c : line)
      nodes.back().push_back(Node(nodes.back().size(), nodes.size() - 1, c));

  }

  n_x = nodes[0].size();
  n_y = nodes.size();
  
  start_node = & nodes[0][1];
  end_node = & nodes[n_y - 1][n_x - 2];

}

void Graph::link_nodes(){

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      
      if(nodes[y][x].c == '#')
        continue;
      
      if(y - 1 >= 0 && (nodes[y - 1][x].c == '.' || nodes[y - 1][x].c == '^') && (nodes[y][x].c == '.' || nodes[y][x].c == '^'))
        nodes[y][x].link(& nodes[y - 1][x], 1);
      
      if(x - 1 >= 0 && (nodes[y][x - 1].c == '.' || nodes[y][x - 1].c == '<') && (nodes[y][x].c == '.' || nodes[y][x].c == '<'))
        nodes[y][x].link(& nodes[y][x - 1], 1);
      
      if(y + 1 < n_y && (nodes[y + 1][x].c == '.' || nodes[y + 1][x].c == 'v') && (nodes[y][x].c == '.' || nodes[y][x].c == 'v'))
        nodes[y][x].link(& nodes[y + 1][x], 1);
      
      if(x + 1 < n_x && (nodes[y][x + 1].c == '.' || nodes[y][x + 1].c == '>') && (nodes[y][x].c == '.' || nodes[y][x].c == '>'))
        nodes[y][x].link(& nodes[y][x + 1], 1);

    }
  }

}

bool Graph::distance_decreasing(const Node * a, const Node * b){

  return a->distance > b->distance;

}

int Graph::run_dijkstra(){

  vector<Node *> queue;

  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      queue.push_back(nodes[y][x].reset());

  start_node->distance = 0;

  while(! queue.empty()){
    
    sort(queue.begin(), queue.end(), distance_decreasing);

    Node * node = queue.back();

    node->visited = true;

    queue.pop_back();

    int ctr = 0;

    for(Edge & edge : node->edges){
      if(! edge.node->visited){
        
	int distance_update = node->distance + edge.weight;
	  
	if(distance_update < edge.node->distance){

	  edge.node->distance = distance_update;

          edge.node->previous = node;

        }

      }
    }

  }

  return end_node->distance;

}

int main(){
  
  Graph graph("input.txt");

  cout << graph.run_dijkstra() << endl;

}
