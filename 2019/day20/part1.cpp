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

    vector<int> get_connections(T*, string);

  public:
    
    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    
    void add_edge(T, T, int);
    void add_edge_or_update_weight(T*, T*, int);

    void calc_maps();

    int run_dijkstra(T, T);

};

template <typename T>
int Graph<T>::run_dijkstra(T source, T goal){
  
  int idx_source = idx_of[source];
  int idx_goal = idx_of[goal];
  
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

      if(neighbour_idx == idx_goal && dist_to_node[idx_goal] != infinity)
        return dist_to_node[idx_goal];

    }

  }

  return infinity;

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
void Graph<T>::calc_maps(){
  
 neighbours_of.clear();
 weights_of.clear();

 for(int & n : non_empty_nodes)
   idx_of[nodes[n]] = n;

 for(int & n : non_empty_nodes){

   neighbours_of[n] = {};

   vector<int> edges_in = get_connections(&nodes[n], "in");
   vector<int> edges_out = get_connections(&nodes[n], "out");

   for(int & i : edges_in) neighbours_of[n].push_back(idx_of[*edges[i].out]);
   for(int & i : edges_out) neighbours_of[n].push_back(idx_of[*edges[i].in]);

   for(int & i : edges_in) weights_of[n].push_back(edges[i].weight);
   for(int & i : edges_out) weights_of[n].push_back(edges[i].weight);

 }

}

string join(vector<char> chars){

  string str = "";

  for(char & c : chars)
    str += c;

  return str;

}

Coordinate pick_out_by_key(vector<pair<string, Coordinate>> & portal_coords, string key){

  for(int i=0; i<portal_coords.size(); i++){
    if(portal_coords[i].first == key){

      Coordinate coord = portal_coords[i].second;

      portal_coords.erase(portal_coords.begin() + i);

      return coord;

    }
  }

  return {infinity, infinity};

}

void read_grid(string in_file_name, vector<vector<char>> & grid, vector<pair<string, Coordinate>> & portal_coords, Coordinate & source, Coordinate & goal){
  
  ifstream in_file(in_file_name);

  string line, field;

  while(getline(in_file, line)){
    
    grid.push_back({});
    
    for(char & c : line)
      grid.back().push_back(c);
    
  }

  for(int y=0; y<grid.size(); y++)
    for(int x=1; x<grid[y].size(); x++)
      if(isupper(grid[y][x]) && isupper(grid[y][x-1]))
        if(x < grid[y].size() - 1 && grid[y][x+1] == '.')
          portal_coords.push_back({join({grid[y][x-1], grid[y][x]}), {y, x+1}});
        else
          portal_coords.push_back({join({grid[y][x-1], grid[y][x]}), {y, x-2}});

  for(int x=0; x<grid[0].size(); x++)
    for(int y=1; y<grid.size(); y++)
      if(isupper(grid[y][x]) && isupper(grid[y-1][x]))
        if(y < grid.size() - 1 && grid[y+1][x] == '.')
          portal_coords.push_back({join({grid[y-1][x], grid[y][x]}), {y+1, x}});
        else
          portal_coords.push_back({join({grid[y-1][x], grid[y][x]}), {y-2, x}});

  source = pick_out_by_key(portal_coords, "AA");
  goal = pick_out_by_key(portal_coords, "ZZ");

}

template <typename T>
void make_graph(vector<vector<char>> & grid, vector<pair<string, Coordinate>> portal_coords, Graph<T> & graph){

  for(int y=0; y<grid.size(); y++)
    for(int x=0; x<grid[y].size(); x++)
      if(grid[y][x] == '.')
        for(Coordinate & neighbour : get_neighbours({y, x}, grid))
          if(grid[neighbour.first][neighbour.second] == '.')
            graph.add_edge({y, x}, neighbour, 1);

  while(portal_coords.size() > 0){
    for(int i=1; i<portal_coords.size(); i++){
      if(portal_coords[0].first == portal_coords[i].first){

        graph.add_edge(portal_coords[0].second, portal_coords[i].second, 1);

        portal_coords.erase(portal_coords.begin() + i);
        portal_coords.erase(portal_coords.begin());

        break;

      }
    }
  }

}

int main(){

  vector<vector<char>> grid;
  vector<pair<string, Coordinate>> portal_coords;

  Coordinate source;
  Coordinate goal;

  read_grid("example.txt", grid, portal_coords, source, goal);

  int n_coordinates = grid.at(0).size() * grid.size();

  Graph<Coordinate> graph(n_coordinates);

  make_graph(grid, portal_coords, graph);

//  graph.calc_maps();
//
//  int min_dist = graph.run_dijkstra(portal_coords["AA"], portal_coords["ZZ"]);
//
//  cout<<min_dist<<endl;

}
