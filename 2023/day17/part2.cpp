#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;
  
class Graph{

  public:
    
    int n_y, n_x;

    int run_dijkstra(int, int, int, int);

    Graph(string);

  private:
    
    struct Edge;

    struct Node;

    struct Grid{
      
      vector<vector<Node>> nodes_h;
      vector<vector<Node>> nodes_v;
    
    };

    Grid grid;

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

  int x, y, value;

  int distance = infinity;
  bool visited = false;
  bool on_path = false;

  Node * reset();
  void link(Node *, int);

  Node(int x, int y, int v) : x(x), y(y), value(v) {}
  
};

Graph::Node * Graph::Node::reset(){

  distance = infinity;
  visited = false;
  on_path = false;

  return this;

}

void Graph::Node::link(Node * node, int weight){
  
  edges.push_back(Edge(node, weight));

}

void Graph::add_nodes(){
  
  string line;

  ifstream in_file(in_file_name);

  vector<string> lines;

  while(getline(in_file, line))
    lines.push_back(line);

  for(vector<vector<Node>> * nodes : {& grid.nodes_v, & grid.nodes_h}){

    for(string & l : lines){
      
      nodes->push_back({});

      for(char & c : l)
        nodes->back().push_back(Node(nodes->size() - 1, nodes->back().size(), c - '0'));

    }

  }

  n_x = grid.nodes_v[0].size();
  n_y = grid.nodes_v.size();

}

void Graph::link_nodes(){

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      
      int weight_u = 0;
      int weight_r = 0;
      int weight_d = 0;
      int weight_l = 0;

      for(int i=1; i<11; i++){

	if(y - i >= 0){
	  weight_u += grid.nodes_v[y - i][x].value;
	  if(i > 3)
            grid.nodes_v[y][x].link(& grid.nodes_h[y - i][x], weight_u);
	}

	if(x - i >= 0){
	  weight_l += grid.nodes_v[y][x - i].value;
	  if(i > 3)
            grid.nodes_h[y][x].link(& grid.nodes_v[y][x - i], weight_l);
	}

	if(y + i < n_y){
	  weight_d += grid.nodes_v[y + i][x].value;
	  if(i > 3)
            grid.nodes_v[y][x].link(& grid.nodes_h[y + i][x], weight_d);
	}

	if(x + i < n_x){
	  weight_r += grid.nodes_v[y][x + i].value;
	  if(i > 3)
            grid.nodes_h[y][x].link(& grid.nodes_v[y][x + i], weight_r);
	}

      }
    }
  }

}

bool Graph::distance_decreasing(const Node * a, const Node * b){

  return a->distance > b->distance;

}

int Graph::run_dijkstra(int start_y, int start_x, int end_y, int end_x){
  
  Node * start_node = new Node(start_y, start_x, 0);
  Node * end_node = new Node(end_y, end_x, 0);

  start_node->link(& grid.nodes_v[start_y][start_x], 0);
  start_node->link(& grid.nodes_h[start_y][start_x], 0);

  (& grid.nodes_v[end_y][end_x])->link(end_node, 0);
  (& grid.nodes_h[end_y][end_x])->link(end_node, 0);

  vector<Node *> queue;

  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      for(Node * n : {& grid.nodes_v[y][x], & grid.nodes_h[y][x]})
        queue.push_back(n->reset());

  start_node->reset();
  end_node->reset();

  start_node->distance = 0;

  queue.push_back(start_node);
  queue.push_back(end_node);

  while(queue.size() > 0){
    
    sort(queue.begin(), queue.end(), distance_decreasing);

    Node * node = queue.back();

    node->visited = true;

    if(node == end_node)
      return node->distance;

    queue.pop_back();

    int ctr = 0;

    for(Edge & edge : node->edges){
      if(! edge.node->visited){
        
	int distance_update = node->distance + edge.weight;
	  
	if(distance_update < edge.node->distance)
	  edge.node->distance = distance_update;

      }
    }

  }

  return 0;

}

int main(){
  
  Graph graph("input.txt");

  cout << graph.run_dijkstra(0, 0, graph.n_y - 1, graph.n_x - 1) << endl;

}
