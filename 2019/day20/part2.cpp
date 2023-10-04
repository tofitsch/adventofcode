#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

#define N_LEVELS 100

using namespace std;

typedef pair<int, int> Coordinate;
typedef tuple<int, int, int> Coordinate3d;

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

    int n_nodes = 0;

    vector<int> queue;

    map<int, vector<int>> neighbours_of;
    map<int, vector<int>> weights_of;

    map<T, int> idx_of;
    map<int, int> dist_to_node;

    vector<int> get_connections(T*, string);

  public:
    
    vector<Edge<T>> edges;
    vector<int> non_empty_nodes;

    Graph(int size) : nodes(new T[size]) {}
    ~Graph(){delete[] nodes;}
    
    void add_edge(T, T, int);
    void add_edge_or_update_weight(T*, T*, int);

    void prune(map<string, Coordinate> &, map<string, Coordinate> &, Coordinate &, Coordinate &);

    void calc_maps();

    int run_dijkstra(T, T);

    void print(map<string, Coordinate> &, map<string, Coordinate> &, Coordinate &, Coordinate &); //XXX

};

template <typename T>//XXX
void Graph<T>::print(map<string, Coordinate> & portal_coords_inner, map<string, Coordinate> & portal_coords_outer, Coordinate & source, Coordinate & goal){
  
  map<Coordinate, string> portal_names;

  for(auto & key : portal_coords_inner)
    portal_names[key.second] = key.first; 

  for(auto & key : portal_coords_outer)
    portal_names[key.second] = key.first; 

  portal_names[source] = "AA";
  portal_names[goal] = "ZZ";

  for(auto & edge : edges)
//    cout<<"("<<get<0>(*edge.in)<<", "<<get<1>(*edge.in)<<") -> ("<<get<0>(*edge.out)<<", "<<get<1>(*edge.out)<<")"<<endl;
//    cout<<portal_names[{get<0>(*edge.in), get<1>(*edge.in)}]<<get<2>(*edge.in)<<" -> "<<portal_names[{get<0>(*edge.out), get<1>(*edge.out)}]<<get<2>(*edge.out)<<" | "<<edge.weight<<endl;
    cout<<portal_names[{get<0>(*edge.in), get<1>(*edge.in)}]<<" -> "<<portal_names[{get<0>(*edge.out), get<1>(*edge.out)}]<<" | "<<edge.weight<<endl;
 
// for(int & n : non_empty_nodes)
//   cout<<portal_names[{get<0>(nodes[n]), get<1>(nodes[n])}]<<" "<<get<2>(nodes[n])<<" | "<<dist_to_node[n]<<endl;

}

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

template <typename T>
void Graph<T>::prune(map<string, Coordinate> & portal_coords_inner, map<string, Coordinate> & portal_coords_outer, Coordinate & source, Coordinate & goal){
  
  vector<Coordinate> portal_coords;

  for(auto & key : portal_coords_inner)
    portal_coords.push_back(key.second);

  for(auto & key : portal_coords_outer)
    portal_coords.push_back(key.second);

  portal_coords.push_back(source);
  portal_coords.push_back(goal);

  bool done = false;

  while(!done){

    done = true;

    for(int & n : non_empty_nodes){

      if(find(portal_coords.begin(), portal_coords.end(), nodes[n]) != portal_coords.end())
        continue;

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

int read_grid(string in_file_name, vector<vector<char>> & grid, map<string, Coordinate> & portal_coords_inner, map<string, Coordinate> & portal_coords_outer, Coordinate & source, Coordinate & goal){
  
  ifstream in_file(in_file_name);

  string line, field;

  while(getline(in_file, line)){
    
    grid.push_back({});
    
    for(char & c : line)
      grid.back().push_back(c);
    
  }

  vector<pair<string, Coordinate>> portal_coords;

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

  for(auto & key : portal_coords){

    int y = key.second.first;
    int x = key.second.second;

    if(x > 2 && x < grid[0].size() - 3 &&
       y > 2 && y < grid.size() - 3
      )
      portal_coords_inner[key.first] = key.second;
    else
      portal_coords_outer[key.first] = key.second;

  }
  
  int n_tiles = 0;

  for(int y=0; y<grid.size(); y++)
    for(int x=1; x<grid[y].size(); x++)
      if(grid[y][x] == '.')
        n_tiles++;

  return n_tiles;

}

template <typename T>
void make_graph_2d(vector<vector<char>> & grid, Graph<T> & graph){
  
  for(int y=0; y<grid.size(); y++)
    for(int x=0; x<grid[y].size(); x++)
      if(grid[y][x] == '.')
        for(Coordinate & neighbour : get_neighbours({y, x}, grid))
          if(grid[neighbour.first][neighbour.second] == '.')
            graph.add_edge({y, x}, neighbour, 1);

}

template <typename T, typename U>
void make_graph_3d(Graph<T> & graph_3d, Graph<U> & graph_2d, map<string, Coordinate> & portal_coords_inner, map<string, Coordinate> & portal_coords_outer, int n_levels){

  for(int l=0; l<n_levels; l++)
    for(auto & edge : graph_2d.edges)
      graph_3d.add_edge({edge.in->first, edge.in->second, l}, {edge.out->first, edge.out->second, l}, edge.weight);

  vector<string> portal_names;

  for(auto & key : portal_coords_inner)
    portal_names.push_back(key.first);

  for(int l=1; l<n_levels; l++){

    for(string & portal_name : portal_names){

      Coordinate3d a = {portal_coords_outer[portal_name].first, portal_coords_outer[portal_name].second, l};
      Coordinate3d b = {portal_coords_inner[portal_name].first, portal_coords_inner[portal_name].second, l - 1};

      graph_3d.add_edge(a, b, 1);

    }
  }

}

int main(){

  vector<vector<char>> grid;
  map<string, Coordinate> portal_coords_inner;
  map<string, Coordinate> portal_coords_outer;

  Coordinate source;
  Coordinate goal;

  int n_tiles = read_grid("input.txt", grid, portal_coords_inner, portal_coords_outer, source, goal);

  int n_coordinates = n_tiles;

  Graph<Coordinate> graph_2d(n_coordinates);

  make_graph_2d(grid, graph_2d);

  graph_2d.prune(portal_coords_inner, portal_coords_outer, source, goal);

//  graph_2d.print(portal_coords_inner, portal_coords_outer, source, goal);

  graph_2d.calc_maps();

  Graph<Coordinate3d> graph_3d(graph_2d.non_empty_nodes.size() * (N_LEVELS + 1));

  make_graph_3d(graph_3d, graph_2d, portal_coords_inner, portal_coords_outer, N_LEVELS);

  graph_3d.calc_maps();

  Coordinate3d source3d = {source.first, source.second, 0};
  Coordinate3d goal3d = {goal.first, goal.second, 0};

  int min_dist = graph_3d.run_dijkstra(source3d, goal3d);

//  graph_3d.print(portal_coords_inner, portal_coords_outer, source, goal);

  cout<<min_dist<<endl;

}
