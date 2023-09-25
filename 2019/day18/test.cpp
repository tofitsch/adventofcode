#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> Coordinate;

template <typename T>
struct Edge{
  
  T* in;
  T* out;
  int weight;

  Edge(T* a, T* b, int w) : in(a), out(b), weight(w) {}

};

template <typename T>
class Graph{
 
  private:

    T* nodes;
    int n_nodes = 0;
    vector<Edge<T>> edges;

  public:
    
    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    

    void add_edge(T, T, int);
    void prune(vector<vector<char>> &);

};

template <typename T>
void Graph<T>::add_edge(T a, T b, int weight){
  
  T* ptr_a = nullptr;
  T* ptr_b = nullptr;

  for(int n=0; n<n_nodes; n++){

    if(nodes[n] == a) ptr_a = &nodes[n];
    if(nodes[n] == b) ptr_b = &nodes[n];

  }

  if(ptr_a == nullptr){
    
    nodes[n_nodes] = a;
    ptr_a = &nodes[n_nodes];
    n_nodes++;

  }

  if(ptr_b == nullptr){
    
    nodes[n_nodes] = b;
    ptr_b = &nodes[n_nodes];
    n_nodes++;

  }

  edges.push_back(Edge<T>(ptr_a, ptr_b, weight));

}

vector<Coordinate> get_neighbours(Coordinate coord, vector<vector<char>> & grid){
  
  int y = coord.first;
  int x = coord.second;

  vector<Coordinate> neighbours;

  vector<Coordinate> possible_neighbours = {{y + 1, x}, {y, x + 1}, {y - 1, x}, {y, x - 1}};

  for(Coordinate neighbour : possible_neighbours)
    if(neighbour.first > 0
       && neighbour.first < grid.size()
       && neighbour.second > 0
       && neighbour.second < grid.at(0).size()
      )
      neighbours.push_back(neighbour);

  return neighbours;

}

template <typename T>
void Graph<T>::prune(vector<vector<char>> & grid){
  
  bool done = false;
  
  while(!done){
 
    done = true;

    for(int e=0; e<edges.size(); e++){

      T* node_in = edges.at(e).in;
      T* node_out = edges.at(e).out;
      
      if(!isalpha(grid[node_in->first][node_in->second]) &&
         !isalpha(grid[node_out->first][node_out->second])
       ){
        
        edges.erase(edges.begin() + e);
        done = false;
        break;
        
      }

    }

  }

}

void read_grid(string in_file_name, vector<vector<char>> & grid, map<char, Coordinate> & gate_coords, map<char, Coordinate> & key_coords, Coordinate & start){

  ifstream in_file(in_file_name);

  string line, field;

  while(getline(in_file, line)){
    
    grid.push_back({});
    
    for(char & c : line)
      grid.back().push_back(c);
    
  }

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].size(); x++){

      if(grid[y][x] >= 'A' && grid[y][x] <= 'Z') gate_coords[grid[y][x]] = {y, x}; 
      if(grid[y][x] >= 'a' && grid[y][x] <= 'z') key_coords[grid[y][x]] = {y, x}; 
      if(grid[y][x] == '@') start = {y, x}; 

    }
  }

}

template <typename T>
void make_graph(vector<vector<char>> & grid, Graph<T> & graph){

  for(int y=0; y<grid.size(); y++)
    for(int x=0; x<grid[y].size(); x++)
      if(grid[y][x] != '#')
        for(Coordinate & neighbour : get_neighbours({y, x}, grid))
          if(grid[neighbour.first][neighbour.second] != '#')
            graph.add_edge({y, x}, neighbour, 1);

}

int main(){

  vector<vector<char>> grid;
  map<char, Coordinate> gate_coords;
  map<char, Coordinate> key_coords;
  Coordinate start;

  read_grid("example.txt", grid, gate_coords, key_coords, start);

  int n_coordinates = grid.at(0).size() * grid.size();

  Graph<Coordinate> graph(n_coordinates);

  make_graph(grid, graph);

  graph.prune(grid);

}
