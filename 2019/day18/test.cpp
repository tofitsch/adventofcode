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
    vector<Edge<T>> edges;

    vector<int> get_connections(T*, bool);

  public:

    int n_nodes = 0;
    
    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    
    void add_edge(T, T, int);
    void add_edge_or_update_weight(T*, T*, int);
    void prune(vector<vector<char>> &);
    void print(vector<vector<char>> &);

};

template <typename T>
void Graph<T>::add_edge_or_update_weight(T* ptr_a, T* ptr_b, int weight){

  for(Edge<T> & edge : edges){

    if((edge.in == ptr_a && edge.out == ptr_b) ||
       (edge.in == ptr_b && edge.out == ptr_a)
    ){
      
      if(edge.weight > weight) edge.weight = weight;
      
      return;

    }

  }

  edges.push_back(Edge<T>(ptr_a, ptr_b, weight));

}

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

  add_edge_or_update_weight(ptr_a, ptr_b, weight);

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
vector<int> Graph<T>::get_connections(T* node, bool in){
  
 vector<int> connections;
  
  for(int e=0; e<edges.size(); e++){

    if(!in && edges.at(e).in == node) connections.push_back(e);
    if(in && edges.at(e).out == node) connections.push_back(e);
     
  }

  return connections;

}

template <typename T>
void Graph<T>::prune(vector<vector<char>> & grid){
  
  bool done = false;
  
  while(!done){
 
    done = true;

    for(int n=0; n<n_nodes; n++){
      
      char tile = grid[nodes[n].first][nodes[n].second];
      
      if(isalpha(tile) || tile == '@') continue;
      
      vector<int> edges_in  = get_connections(&nodes[n], true);
      vector<int> edges_out = get_connections(&nodes[n], false);

      vector<int> edges_all = edges_in;

      edges_all.insert(edges_all.end(), edges_out.begin(), edges_out.end());
      sort(edges_all.begin(), edges_all.end(), greater<>());
      edges_all.erase(unique(edges_all.begin(), edges_all.end()), edges_all.end());

      if(edges_all.size() == 0) continue;

      for(int & i : edges_in)
        for(int & j : edges_in)
          if(i != j)
            add_edge_or_update_weight(edges.at(i).in, edges.at(j).in, edges.at(i).weight + edges.at(j).weight);

      for(int & i : edges_out)
        for(int & j : edges_out)
          if(i != j)
            add_edge_or_update_weight(edges.at(i).out, edges.at(j).out, edges.at(i).weight + edges.at(j).weight);

      for(int & i : edges_in)
        for(int & j : edges_out)
          if(i != j)
            add_edge_or_update_weight(edges.at(i).in, edges.at(j).out, edges.at(i).weight + edges.at(j).weight);

      for(int & e : edges_all)
        edges.erase(edges.begin() + e);

      done = false;

      break;

    }

  }

}

template <typename T>
void Graph<T>::print(vector<vector<char>> & grid){

  for(Edge<T> & edge : edges){

      char tile_in = grid[edge.in->first][edge.in->second];
      char tile_out = grid[edge.out->first][edge.out->second];

      cout<<tile_in<<" ("<<edge.in->first<<", "<<edge.in->second<<") -> "<<tile_out<<" ("<<edge.out->first<<", "<<edge.out->second<<") "<<edge.weight<<endl;
    
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

  graph.print(grid);

  graph.prune(grid);

  cout<<endl;
  graph.print(grid);

}
