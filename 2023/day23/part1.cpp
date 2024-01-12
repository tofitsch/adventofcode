#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;
  
class Graph{

  private:
    
    struct Edge;
    struct Node;

    vector<vector<Node>> nodes;

    vector<int> path_lengths;

    Node * start_node = nullptr;
    Node * end_node = nullptr;

    string in_file_name;

    int static const infinity = numeric_limits<int>::max();

    void add_nodes();
    void link_nodes();

    bool static distance_decreasing(const Node *, const Node *);

  public:
    
    int n_y, n_x;

    void run_dijkstra();
    void make_directional();
    void simplify();
    void simplify_node(Node *);
    int get_longest_path_length();
    void find_path(Node *, int);

    Graph(string);

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
  vector<Edge> simple_edges;

  int y, x;

  char c;

  int distance = infinity;
  bool visited = false;
  bool on_path = false;
  Node * previous = nullptr;

  int n_edges_in = 0;

  Node * reset();

  Node(int y, int x, char c) : y(y), x(x), c(c) {}
  
};

Graph::Node * Graph::Node::reset(){

  distance = infinity;
  visited = false;
  on_path = false;
  previous = nullptr;

  return this;

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
        nodes[y][x].edges.push_back(Edge(& nodes[y - 1][x], 1));
      
      if(x - 1 >= 0 && (nodes[y][x - 1].c == '.' || nodes[y][x - 1].c == '<') && (nodes[y][x].c == '.' || nodes[y][x].c == '<'))
        nodes[y][x].edges.push_back(Edge(& nodes[y][x - 1], 1));
      
      if(y + 1 < n_y && (nodes[y + 1][x].c == '.' || nodes[y + 1][x].c == 'v') && (nodes[y][x].c == '.' || nodes[y][x].c == 'v'))
        nodes[y][x].edges.push_back(Edge(& nodes[y + 1][x], 1));
      
      if(x + 1 < n_x && (nodes[y][x + 1].c == '.' || nodes[y][x + 1].c == '>') && (nodes[y][x].c == '.' || nodes[y][x].c == '>'))
        nodes[y][x].edges.push_back(Edge(& nodes[y][x + 1], 1));

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

  Node * node = end_node;

  while(node->previous != nullptr){
    
    node->on_path = true;

    node = node->previous;

  }

  start_node->on_path = true;

}

void Graph::make_directional(){

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      
      Node * node = & nodes[y][x];

      vector<Edge> forward_edges;

      for(Edge & edge : node->edges)
        if(edge.node->distance >= node->distance || node->c != '.'){
          forward_edges.push_back(edge);
          edge.node->n_edges_in++;
        }

      node->edges = forward_edges;

    }
  }

}

void Graph::simplify(){

  simplify_node(start_node);

  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      nodes[y][x].edges = nodes[y][x].simple_edges;

}

void Graph::simplify_node(Graph::Node * node){
  
  if(node->simple_edges.size() > 0)
    return;

  for(Edge & next_edge : node->edges){
  
    Node * next = next_edge.node;

    int weight = 1;
    
    while(! (next == start_node || next == end_node || next->edges.size() != 1 || next->n_edges_in > 1)){

      next = next->edges.front().node;

      weight++;

    }

    if(next->edges.size() == 0 && next != end_node)
      continue;

    node->simple_edges.push_back(Edge(next, weight));

    simplify_node(next);

  }

}

int Graph::get_longest_path_length(){
  
  find_path(start_node, 0);
  
  sort(path_lengths.begin(), path_lengths.end());

  return path_lengths.back();

}

void Graph::find_path(Node * node, int path_length){
 
  if(node == end_node)
    path_lengths.push_back(path_length);
  
  for(Edge & edge : node->edges)
    find_path(edge.node, path_length + edge.weight);

}

int main(){
  
  Graph graph("input.txt");

  graph.run_dijkstra();

  graph.make_directional();

  graph.simplify();

  cout << graph.get_longest_path_length() << endl;

}
