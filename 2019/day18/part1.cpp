#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

#define ASCII_UPPER_LOWER_CASE_DIFF 32

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

    map<T*, int> idx_of_node;
    map<char, int> idx_of_char;
    map<int, char> char_of_idx;

    map<int, int> dist_to_node;

    vector<int> get_connections(T*, string);

  public:
    
    string chars = "";
    map<int, char> dist_to_key;

    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    
    void add_edge(T, T, int);
    void add_edge_or_update_weight(T*, T*, int);
    void prune(vector<vector<char>> &);
    void print(vector<vector<char>> &);
    void calc_maps(vector<vector<char>> &);
    void run_dijkstra(int, string);
    void run_dijkstra(char, string);

};

template <typename T>
void Graph<T>::run_dijkstra(char source, string keys){
  
  run_dijkstra(idx_of_char[source], keys);

}

template <typename T>
void Graph<T>::run_dijkstra(int idx_source, string keys){

  queue.clear();
  dist_to_node.clear();

  for(int & n : non_empty_nodes){
    
    char tile = char_of_idx[n];

    if(isupper(tile) && find(keys.begin(), keys.end(), tile + ASCII_UPPER_LOWER_CASE_DIFF) == keys.end()) continue;
    
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

  dist_to_key.clear();

  for(pair<int, int> key : dist_to_node){

    char tile = char_of_idx[key.first];
    int dist = key.second;

    if(islower(tile) &&
       dist < infinity &&
       find(keys.begin(), keys.end(), tile) == keys.end()
      )
      dist_to_key[tile] = dist;

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
  
 idx_of_char.clear();
 char_of_idx.clear();
 neighbours_of.clear();
 weights_of.clear();

 for(int & n : non_empty_nodes)
   idx_of_node[&nodes[n]] = n;

 for(int & n : non_empty_nodes){

   char tile = grid[nodes[n].first][nodes[n].second];

   chars += tile;

   idx_of_char[tile] = n;
   char_of_idx[n] = tile;

   neighbours_of[n] = {};

   vector<int> edges_in = get_connections(&nodes[n], "in");
   vector<int> edges_out = get_connections(&nodes[n], "out");

   for(int & i : edges_in) neighbours_of[n].push_back(idx_of_node[edges[i].out]);
   for(int & i : edges_out) neighbours_of[n].push_back(idx_of_node[edges[i].in]);

   for(int & i : edges_in) weights_of[n].push_back(edges[i].weight);
   for(int & i : edges_out) weights_of[n].push_back(edges[i].weight);

 }

 sort(chars.begin(), chars.end());

}

template <typename T>
void Graph<T>::prune(vector<vector<char>> & grid){
  
  bool done = false;
  
  while(!done){
 
    done = true;

    for(int & n : non_empty_nodes){
      
      char tile = grid[nodes[n].first][nodes[n].second];
      
      if(isalpha(tile) || tile == '@') continue;
      
      vector<int> edges_in  = get_connections(&nodes[n], "in");
      vector<int> edges_out = get_connections(&nodes[n], "out");
      vector<int> edges_all = get_connections(&nodes[n], "all");

      for(int & i : edges_in)
        for(int & j : edges_in)
          add_edge_or_update_weight(edges.at(i).out, edges.at(j).out, edges.at(i).weight + edges.at(j).weight);

      for(int & i : edges_out)
        for(int & j : edges_out)
          add_edge_or_update_weight(edges.at(i).in, edges.at(j).in, edges.at(i).weight + edges.at(j).weight);

      for(int & i : edges_in)
        for(int & j : edges_out)
          add_edge_or_update_weight(edges.at(i).out, edges.at(j).in, edges.at(i).weight + edges.at(j).weight);

      for(int & e : edges_all)
        edges.erase(edges.begin() + e);

      non_empty_nodes.erase(remove(non_empty_nodes.begin(), non_empty_nodes.end(), n), non_empty_nodes.end());

      done = false;

      break;

    }

  }

}

template <typename T>
void Graph<T>::print(vector<vector<char>> & grid){

  cout<<"edges:"<<endl;

  for(Edge<T> & edge : edges){

      char tile_in = grid[edge.in->first][edge.in->second];
      char tile_out = grid[edge.out->first][edge.out->second];

      cout<<tile_in<<" ("<<edge.in<<" | "<<edge.in->first<<", "<<edge.in->second<<") -> "<<tile_out<<" ("<<edge.out<<" | "<<edge.out->first<<", "<<edge.out->second<<") "<<edge.weight<<endl;
    
  }

  cout<<"number of connections of nodes:"<<endl;

  for(int & n : non_empty_nodes)
    cout<<grid[nodes[n].first][nodes[n].second]<<" "<<&nodes[n]<<" "<<get_connections(&nodes[n], "all").size()<<endl;

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

template <typename T>
void recursive_find(Graph<T> & graph, int & min_dist, int dist, char source, string keys){
  
  if(!isalpha(source) && source != '@') return;
  
  cout<<source<<" "<<keys<<" "<<dist<<endl;
  
  graph.run_dijkstra(source, keys);

//  for(pair<char, int> key : graph.dist_to_key)
//    cout<<key.first<<" : "<<key.second<<endl;

//  cout<<graph.dist_to_key.size()<<endl;

  for(pair<char, int> key : graph.dist_to_key){
    
    int new_dist = dist + key.second;
    string new_keys = keys + key.first;

    if(new_keys.size() == graph.chars.size() && new_dist < min_dist){

      cout<<new_dist<<endl;
      min_dist = new_dist;

    }

    sort(new_keys.begin(), new_keys.end());

    recursive_find(graph, min_dist, new_dist, key.first, new_keys);

  }

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

  graph.calc_maps(grid);

  graph.print(grid);

//  graph.run_dijkstra('@', "ab");
//
//  for(pair<char, int> key : graph.dist_to_key)
//    cout<<key.first<<" : "<<key.second<<endl;
//
//  cout<<graph.chars<<endl;

  int min_dist = infinity;

  recursive_find(graph, min_dist, 0, '@', "");

  cout<<min_dist<<endl;

}
