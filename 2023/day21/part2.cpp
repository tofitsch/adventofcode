#include<algorithm>
#include<iostream>
#include<fstream>
#include<vector>
#include<set>

using namespace std;
  
class Graph{

  public:
    
    int n_y, n_x;

    void step();
    int count_active_edges();

    void print();

    Graph(string);

  private:
    
    struct Node;
    struct Edge;

    vector<vector<Node>> grid;
    set<Edge> active_edges;

    Node * start_node = nullptr;

    string in_file_name;

    void add_nodes();
    void link_nodes();

};

Graph::Graph(string in_file_name) : in_file_name(in_file_name) {
  
  add_nodes();

  link_nodes();

}

struct Graph::Node{
  
  vector<Edge> edges;

  int x, y;

  char value;

  bool active = false;

  Node(int x, int y, char c) : x(x), y(y), value(c) {}
  
};

struct Graph::Edge{
  
  Node * node = nullptr;

  int grid_y = 0 ;
  int grid_x = 0;

  Edge() {}
  Edge(Node * n) : node(n) {}
  Edge(Node * n, int y, int x) : node(n), grid_y(y), grid_x(x) {}

  bool operator<(const Edge & e) const {
    
    return (grid_y < e.grid_y || grid_x < e.grid_x || node->y < e.node->y || node->x < e.node->x);
    
  }


};

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
          grid[y][x].edges.push_back(Edge(& grid[y - 1][x]));

	if(x - 1 >= 0 && grid[y][x - 1].value != '#')
          grid[y][x].edges.push_back(Edge(& grid[y][x - 1]));

	if(y + 1 < n_y && grid[y + 1][x].value != '#')
          grid[y][x].edges.push_back(Edge(& grid[y + 1][x]));

	if(x + 1 < n_x && grid[y][x + 1].value != '#')
          grid[y][x].edges.push_back(Edge(& grid[y][x + 1]));

    }
  }

  for(int y=0; y<n_y; y++){

    grid[y][n_x - 1].edges.push_back(Edge(& grid[y][0], 0, 1));
    grid[y][0].edges.push_back(Edge(& grid[y][n_x - 1], 0, -1));

  }
    
  for(int x=0; x<n_x; x++){

    grid[n_y - 1][x].edges.push_back(Edge(& grid[0][x], 1, 0));
    grid[0][x].edges.push_back(Edge(& grid[n_y - 1][x], -1, 0));

  }

  active_edges.insert(Edge(start_node));

}

void Graph::step(){
  
  set<Edge> new_active_edges;

  for(Edge edge : active_edges)
    for(Edge link : edge.node->edges)
      new_active_edges.insert(Edge(link.node, edge.grid_y + link.grid_y, edge.grid_x + link.grid_x));

  active_edges = new_active_edges;

}

int Graph::count_active_edges(){

  return active_edges.size();

}

void Graph::print(){
  
  for(Edge edge : active_edges)
    edge.node->active = true;

  for(int y=0; y<n_y; y++){

    for(int x=0; x<n_x; x++){

      if(grid[y][x].active)
        cout << "\033[1;31mO\033[0m";
      else
        cout << grid[y][x].value;

    }

    cout << endl;

  }

}

int main(){
  
  Graph graph("example.txt");

  for(int i=0; i<6; i++)
    graph.step();

  cout << graph.count_active_edges() << endl;

  graph.print();

}
