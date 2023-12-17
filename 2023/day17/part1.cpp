#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<limits>

using namespace std;
  
class Graph{

  public:
    
    int n_y, n_x;

    void run_dijkstra(int, int, int, int);

    void print();

    Graph(string);

  private:
    
    struct Node;

    vector<vector<Node>> grid;

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

  Node(int x, int y, int v) : x(x), y(y), value(v) {}
  
};

void Graph::Node::link(Node * node){
  
  node->neighbours.push_back(this);

  neighbours.push_back(node);

}

void Graph::add_nodes(){
  
  string line;

  ifstream in_file(in_file_name);

  while(getline(in_file, line)){
    
    grid.push_back({});

    for(char & c : line)
      grid.back().push_back(Node(grid.size() - 1, grid.back().size(), c - '0'));

  }

  n_x = grid[0].size();
  n_y = grid.size();

}

void Graph::link_nodes(){
  
  for(int y=0; y<n_y; y++)
    for(int x=0; x<n_x; x++)
      for(pair<int, int> neighbour : vector<pair<int, int>> { {y, x + 1}, {y, x - 1}, {y + 1, x}, {y - 1, x} })
        if(neighbour.first >= 0 && neighbour.first < n_y  && neighbour.second >= 0 && neighbour.second < n_y)
	  grid[y][x].link(& grid[neighbour.first][neighbour.second]);

}

bool Graph::distance_decreasing(const Node * a, const Node * b){

  return a->distance > b->distance;

}

void Graph::run_dijkstra(int start_y, int start_x, int end_y, int end_x){
  
  Node * end_node = & grid[end_y][end_x];
  Node * start_node = & grid[start_y][start_x];

  vector<Node *> queue;

  for(int y=0; y<n_y; y++){
    for(int x=0; x<n_x; x++){
      
      grid[y][x].distance = infinity;
      grid[y][x].previous = nullptr;
      grid[y][x].visited = false;
      grid[y][x].on_path = false;

      queue.push_back(& grid[y][x]);

    }
  }

  start_node->distance = 0;

  while(queue.size() > 0){
   
    sort(queue.begin(), queue.end(), distance_decreasing);

    Node * node = queue.back();

    node->visited = true;

    if(node == end_node)
      break;

    queue.pop_back();

    for(Node * neighbour : node->neighbours){
      if(! neighbour->visited){
        
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

  while(path_node != start_node){
    
    path_node->on_path = true;

    path_node = path_node->previous;

  }

}

void Graph::print(){
  
  for(int y=0; y<n_y; y++){

    for(int x=0; x<n_x; x++){

      if(grid[y][x].on_path)
        cout << "\033[1;31m" << grid[y][x].value << "\033[0m";
      else
        cout << grid[y][x].value;

    }

    cout << endl;

  }

}

int main(){
  
  Graph graph("example.txt");

  graph.run_dijkstra(0, 0, graph.n_y - 1, graph.n_x - 1);

  graph.print();

}
