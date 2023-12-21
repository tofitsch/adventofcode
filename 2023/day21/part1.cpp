#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;
  
class Graph{

  public:
    
    int n_y, n_x;

    void run_dijkstra();
    int count_reachable(int);

    void print();

    Graph(string);

  private:
    
    struct Edge;
    struct Node;

    vector<vector<Node>> grid;

    Node * start_node = nullptr;

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

  Edge(Node * n) : node(n), weight(1) {}
  Edge(Node * n, int w) : node(n), weight(w) {}

};

struct Graph::Node{
  
  vector<Edge> edges;

  int x, y;
  char value;

  int distance = infinity;
  bool visited = false;
  bool on_path = false;

  Node * reset();
  void link(Node *, int);
  void link(Node *);

  Node(int x, int y, char c) : x(x), y(y), value(c) {}
  
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

void Graph::Node::link(Node * node){

  link(node, 1);

}

void Graph::add_nodes(){
  
  string line;

  ifstream in_file(in_file_name);

  vector<string> lines;

  while(getline(in_file, line))
    lines.push_back(line);

  for(string & l : lines){
    
    grid.push_back({});

    for(char & c : l)
      grid.back().push_back(Node(grid.size() - 1, grid.back().size(), c));

  }

  n_y = grid.size();
  n_x = grid[0].size();

}

void Graph::link_nodes(){

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      
      if(grid[y][x].value == '#')
        continue;
      
      if(grid[y][x].value == 'S')
        start_node = & grid[y][x];
      
	if(y - 1 >= 0 && grid[y - 1][x].value != '#')
          grid[y][x].link(& grid[y - 1][x]);

	if(x - 1 >= 0 && grid[y][x - 1].value != '#')
          grid[y][x].link(& grid[y][x - 1]);

	if(y + 1 < n_y && grid[y + 1][x].value != '#')
          grid[y][x].link(& grid[y + 1][x]);

	if(x + 1 < n_x && grid[y][x + 1].value != '#')
          grid[y][x].link(& grid[y][x + 1]);

    }
  }

}

bool Graph::distance_decreasing(const Node * a, const Node * b){

  return a->distance > b->distance;

}

void Graph::run_dijkstra(){
  
  vector<Node *> queue;

  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      queue.push_back(grid[y][x].reset());

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
	  
	if(distance_update < edge.node->distance)
	  edge.node->distance = distance_update;

      }
    }

  }

}

int Graph::count_reachable(int dist){
  
  int ctr = 0;

  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      if(grid[y][x].value != '#' && grid[y][x].distance == dist){

        grid[y][x].on_path = true;
        ctr++;

      }

  return ctr;

}

void Graph::print(){

  for(int y=0; y<n_y; y++){

    for(int x=0; x<n_x; x++){

      if(grid[y][x].on_path)
        cout << "\033[1;31mO\033[0m";
      else
        cout << grid[y][x].value;

    }

    cout << endl;

  }

}

int main(){
  
  Graph graph("example.txt");

  graph.run_dijkstra();

  cout << graph.count_reachable(6) << endl;

  graph.print();

}
