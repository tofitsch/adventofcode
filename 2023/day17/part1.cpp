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

    void print();

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
  Node * previous = nullptr;
  bool visited = false;
  bool on_path = false;

  void link(Node *, int);
  bool horizontal_to(Node *);

  Node(int x, int y, int v) : x(x), y(y), value(v) {}
  
};

void Graph::Node::link(Node * node, int weight){
  
  node->edges.push_back(Edge(this, weight));

  edges.push_back(Edge(node, weight));

}

bool Graph::Node::horizontal_to(Node * node){
  
  if(abs(x - node->x) > 0)
    return true;

  return false;

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
      
      int weight_h = 0;
      int weight_v = 0;

      for(int i=1; i<4; i++){

	if(y - i >= 0){
	  weight_h += grid.nodes_v[y - i][x].value;
          grid.nodes_v[y][x].link(& grid.nodes_h[y - i][x], weight_h);
	}

	if(x - i >= 0){
	  weight_v += grid.nodes_v[y][x - i].value;
          grid.nodes_h[y][x].link(& grid.nodes_v[y][x - i], weight_v);
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

  end_node->link(& grid.nodes_v[end_y][end_x], 0);
  end_node->link(& grid.nodes_h[end_y][end_x], 0);

  vector<Node *> queue;

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      for(Node * n : {& grid.nodes_v[y][x], & grid.nodes_h[y][x]}){
      
        n->distance = infinity;
        n->previous = nullptr;
        n->visited = false;
        n->on_path = false;

        queue.push_back(n);

      }
    }
  }

  start_node->distance = 0;
  start_node->previous = nullptr;
  start_node->visited = false;
  start_node->on_path = false;
  queue.push_back(start_node);

  end_node->distance = infinity;
  end_node->previous = nullptr;
  end_node->visited = false;
  end_node->on_path = false;
  queue.push_back(end_node);

  while(queue.size() > 0){
    
    sort(queue.begin(), queue.end(), distance_decreasing);

    Node * node = queue.back();

    node->visited = true;

    if(node == end_node)
      break;

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

  start_node->on_path = true;

  Node * path_node = end_node;

  while(path_node != start_node){
    
    path_node->on_path = true;

    path_node = path_node->previous;

  }

  return end_node->distance;

}

void Graph::print(){
  
  for(int y=0; y<n_y; y++){

    for(int x=0; x<n_x; x++){

      if(grid.nodes_v[y][x].on_path)
        cout << "\033[1;31m" << grid.nodes_v[y][x].value << "\033[0m";
      else if(grid.nodes_h[y][x].on_path)
        cout << "\033[1;32m" << grid.nodes_v[y][x].value << "\033[0m";
      else
        cout << grid.nodes_v[y][x].value;

    }

    cout << endl;

  }

}

int main(){
  
  Graph graph("example.txt");

  cout << graph.run_dijkstra(0, 0, graph.n_y - 1, graph.n_x - 1) << endl;

  graph.print();

}
