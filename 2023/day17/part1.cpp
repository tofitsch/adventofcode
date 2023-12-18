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

struct Graph::Node{
  
  vector<Node *> neighbours;

  int x, y, value;

  int distance = infinity;
  Node * previous = nullptr;
  bool visited = false;
  bool on_path = false;

  void link(Node *);
  bool horizontal_to(Node *);
  int straight_path_length(Node *);

  Node(int x, int y, int v) : x(x), y(y), value(v) {}
  
};

void Graph::Node::link(Node * node){
  
  node->neighbours.push_back(this);

  neighbours.push_back(node);

}

bool Graph::Node::horizontal_to(Node * node){
  
  if(abs(x - node->x) > 0)
    return true;

  return false;

}

int Graph::Node::straight_path_length(Node * node){
  
  int length = 1;
   
  bool direction = horizontal_to(node);

  while(node->previous && node->horizontal_to(node->previous) == direction){

    node = node->previous;
    length++;

  }

  return length;

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

      for(pair<int, int> neighbour : vector<pair<int, int>> { {y + 1, x}, {y - 1, x} }){
        if(neighbour.first >= 0 && neighbour.first < n_y){

	  grid.nodes_v[y][x].link(& grid.nodes_h[neighbour.first][neighbour.second]);
	  grid.nodes_v[y][x].link(& grid.nodes_v[neighbour.first][neighbour.second]);

	}
      }

      for(pair<int, int> neighbour : vector<pair<int, int>> { {y, x + 1}, {y, x - 1} }){
        if(neighbour.second >= 0 && neighbour.second < n_y){

	  grid.nodes_h[y][x].link(& grid.nodes_h[neighbour.first][neighbour.second]);
	  grid.nodes_h[y][x].link(& grid.nodes_v[neighbour.first][neighbour.second]);

	}
      }

    }
  }

}

bool Graph::distance_decreasing(const Node * a, const Node * b){

  return a->distance > b->distance;

}

int Graph::run_dijkstra(int start_y, int start_x, int end_y, int end_x){
  
  Node * start_node = & grid.nodes_v[start_y][start_x];
  Node * end_node_h = & grid.nodes_h[end_y][end_x];
  Node * end_node_v = & grid.nodes_h[end_y][end_x];
  Node * end_node = nullptr;

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

  while(queue.size() > 0){
   
    sort(queue.begin(), queue.end(), distance_decreasing);

    Node * node = queue.back();

    node->visited = true;

    if(node == end_node_h || node == end_node_v){
      
      end_node = node;

      break;

    }

    queue.pop_back();

    int ctr = 0;

    for(Node * neighbour : node->neighbours){
      if(! neighbour->visited && neighbour->straight_path_length(node) < 4){
        
	int distance_update = node->distance + neighbour->value;
	  
	if(distance_update < neighbour->distance){

	  neighbour->distance = distance_update;
	  neighbour->previous = node;

	}

      }
    }

  }

  start_node->on_path = true;

  Node * path_node = end_node;

  int sum = 0;

  while(path_node != start_node){
    
    path_node->on_path = true;

    sum += path_node->value;

    path_node = path_node->previous;

  }

  return sum;

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
