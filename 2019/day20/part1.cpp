#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> Coordinate;

const int infinity = 1e8;

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

    vector<int> non_empty_nodes;

    int n_nodes = 0;

    vector<int> queue;

    map<int, vector<int>> neighbours_of;
    map<int, vector<int>> weights_of;

    map<T*, int> idx_of;
    map<int, int> dist_to_node;

    map<string, map<char, int>> dijkstra_memoized;

    vector<int> get_connections(T*, string);

  public:
    
    string chars = "";
    string keys = "";

    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    
    void add_edge(T, T, int);
    void add_edge_or_update_weight(T*, T*, int);
    void calc_maps(vector<vector<char>> &);
    void run_dijkstra(T, string);

};

template <typename T>
void Graph<T>::run_dijkstra(T source, string keys){
  
  int idx_source = idx_of[source];
  
  queue.clear();
  dist_to_node.clear();

  for(int & n : non_empty_nodes){

    dist_to_node[n] = (n == idx_source) ? 0 : infinity;

    queue.push_back(n);

  }

  while(queue.size() > 0){

    int min_dist = infinity;
    int min_dist_pos;

    for(int i=0; i<queue.size(); i++){
      if(dist_to_node[queue.at(i)] <= min_dist){
        
        min_dist = dist_to_node[queue.at(i)];
        min_dist_pos = i;
        
      }
    }

    int node_idx = queue.at(min_dist_pos);

    queue.erase(queue.begin() + min_dist_pos);

    for(int i=0; i<neighbours_of[node_idx].size(); i++){
      
      if(find(queue.begin(), queue.end(), neighbours_of[node_idx][i]) == queue.end()) continue;
      
      int neighbour_idx = neighbours_of[node_idx][i];
      int neighbour_weight = weights_of[node_idx][i];

      if(dist_to_node[node_idx] + neighbour_weight < dist_to_node[neighbour_idx])
        dist_to_node[neighbour_idx] = dist_to_node[node_idx] + neighbour_weight;

    }

  }

}

template <typename T>
void Graph<T>::add_edge_or_update_weight(T* ptr_a, T* ptr_b, int weight){
  
  if(ptr_a == ptr_b) return;

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
    non_empty_nodes.push_back(n_nodes);
    n_nodes++;

  }

  if(ptr_b == nullptr){
    
    nodes[n_nodes] = b;
    ptr_b = &nodes[n_nodes];
    non_empty_nodes.push_back(n_nodes);
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
vector<int> Graph<T>::get_connections(T* node, string type){
  
  vector<int> connections;
  
  for(int e=0; e<edges.size(); e++){

    if((type == "all" || type == "in")  && edges.at(e).in == node)  connections.push_back(e);
    if((type == "all" || type == "out") && edges.at(e).out == node) connections.push_back(e);
     
  }

  sort(connections.begin(), connections.end(), greater<int>());

  return connections;

}

template <typename T>
void Graph<T>::calc_maps(vector<vector<char>> & grid){
  
 neighbours_of.clear();
 weights_of.clear();

 for(int & n : non_empty_nodes)
   idx_of[nodes[n]] = n;

 for(int & n : non_empty_nodes){

   char tile = grid[nodes[n].first][nodes[n].second];

   chars += tile;

   if(islower(tile)) keys += tile;

   neighbours_of[n] = {};

   vector<int> edges_in = get_connections(&nodes[n], "in");
   vector<int> edges_out = get_connections(&nodes[n], "out");

   for(int & i : edges_in) neighbours_of[n].push_back(idx_of[*edges[i].out]);
   for(int & i : edges_out) neighbours_of[n].push_back(idx_of[*edges[i].in]);

   for(int & i : edges_in) weights_of[n].push_back(edges[i].weight);
   for(int & i : edges_out) weights_of[n].push_back(edges[i].weight);

 }

 sort(chars.begin(), chars.end());
 sort(keys.begin(), keys.end());

}

template <typename T>
void read_grid(string in_file_name, vector<vector<char>> & grid, map<char, Coordinate> & gate_coords, map<char, Coordinate> & key_coords){
  
  ifstream in_file(in_file_name);

  string line, field;

  while(getline(in_file, line)){
    
    grid.push_back({});
    
    for(char & c : line)
      grid.back().push_back(c);
    
  }

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].size(); x++){

      if(isupper(grid[y][x])) gate_coords[grid[y][x]] = {y, x}; 
      if(islower(grid[y][x])) key_coords[grid[y][x]] = {y, x}; 

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

  read_grid("input.txt", grid, gate_coords, key_coords);

  int n_coordinates = grid.at(0).size() * grid.size();

  Graph<Coordinate> graph(n_coordinates);

  make_graph(grid, graph);

  graph.prune(grid);

  graph.calc_maps(grid);

  int min_dist = infinity;
  
  map<string, int> min_dists_memoized;

  recursive_find(graph, min_dist, min_dists_memoized, 0, '@', "");

  cout<<min_dist<<endl;

}
