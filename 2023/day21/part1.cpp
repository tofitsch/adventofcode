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
    int count_active_nodes();

    Graph(string);

  private:
    
    struct Node;

    vector<vector<Node>> grid;
    set<Node *> active_nodes;

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
  
  vector<Node *> links;

  int x, y;

  char value;

  bool active = false;

  Node(int x, int y, char c) : x(x), y(y), value(c) {}
  
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
          grid[y][x].links.push_back(& grid[y - 1][x]);

	if(x - 1 >= 0 && grid[y][x - 1].value != '#')
          grid[y][x].links.push_back(& grid[y][x - 1]);

	if(y + 1 < n_y && grid[y + 1][x].value != '#')
          grid[y][x].links.push_back(& grid[y + 1][x]);

	if(x + 1 < n_x && grid[y][x + 1].value != '#')
          grid[y][x].links.push_back(& grid[y][x + 1]);

    }
  }

  active_nodes.insert(start_node);

}

void Graph::step(){
  
  set<Node *> new_active_nodes;

  for(Node * node : active_nodes)
    for(Node * link : node->links)
      new_active_nodes.insert(link);

  active_nodes = new_active_nodes;

}

int Graph::count_active_nodes(){

  return active_nodes.size();

}

int main(){
  
  Graph graph("input.txt");

  for(int i=0; i<64; i++)
    graph.step();

  cout << graph.count_active_nodes() << endl;

}
