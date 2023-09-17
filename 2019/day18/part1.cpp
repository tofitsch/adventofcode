#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<chrono>
#include<algorithm>

using namespace std;

auto g_start = chrono::steady_clock::now();

double time_total = 0;
double time_in_routine = 0;

typedef pair<int, int> Coordinate;

const int infinity = 1e8;

template <typename T>
class Graph{
  
  private:

    map<T, vector<pair<T, int>>> edges;
    map<T, vector<pair<T, int>>> deactivated_edges;

    vector<T> queue;

  public:

    map<T, int> dist;

    void add_edge(T, T);

    void deactivate_node(T);
    void reactivate_node(T);

    void print(vector<vector<char>> &);

    void sort_neighbors(T);
    void run_dijkstra(T);
    void prune(vector<vector<char>> &);

};


template <typename T>
void Graph<T>::run_dijkstra(T source){

  dist.clear();

  for(auto & key : edges){
    
    T node = key.first;

    dist[node] = node == source ? 0 : infinity;

    queue.push_back(node);

  }

  while(queue.size() > 0){
    
    int min_dist = infinity;
    int min_dist_pos;

    for(int i=0; i<queue.size(); i++){
      if(dist[queue.at(i)] <= min_dist){
        
        min_dist = dist[queue.at(i)];
        min_dist_pos = i;
        
      }
    }

    T node = queue.at(min_dist_pos);

    queue.erase(queue.begin() + min_dist_pos);

    for(auto & key : edges[node]){

      T & neighbor = key.first;
      int & weight = key.second;

      if(dist[node] + 1 < dist[neighbor])
        dist[neighbor] = dist[node] + weight;

    }

  }

}

template <typename T>
void Graph<T>::prune(vector<vector<char>> & grid){
  
  bool done = false;
  
  while(!done){
 
    done = true;

    for(auto & key : edges){

      T edge = key.first;
      auto neighbors = key.second;
      
      if(neighbors.size() != 2 || grid[edge.first][edge.second] != '.') continue;

      for(int i : {0, 1}){

        edges[neighbors.at(i).first].erase(remove(edges[neighbors.at(i).first].begin(), edges[neighbors.at(i).first].end(), (pair<T, int>){edge, neighbors.at(i).second}), edges[neighbors.at(i).first].end());

        edges[neighbors.at(i).first].push_back(neighbors.at((i + 1) % 2));

        sort_neighbors(neighbors.at(i).first);

      }

      cout<<"pruning "<<edge.first<<" "<<edge.second<<" '"<<grid[edge.first][edge.second]<<"'"<<endl;

      edges.erase(edge);

      done = false;

      break;

    }

  }

}

template <typename T>
void Graph<T>::deactivate_node(T a){
  
  for(auto & key : edges[a]){

    T & b = key.first;
    int & w_b = key.second;

    edges[b].erase(remove(edges[b].begin(), edges[b].end(), (pair<T, int>){a, w_b}), edges[b].end());

  }

  deactivated_edges[a] = edges[a];

  edges[a] = {};
    
}

template <typename T>
void Graph<T>::reactivate_node(T a){
  
  for(auto & key : deactivated_edges[a]){

    T & b = key.first;
    int & w_b = key.second;

    edges[b].push_back({a, w_b});

  }

  edges[a] = deactivated_edges[a];
    
}

template <typename T>
void Graph<T>::add_edge(T a, T b){
  
  if(edges.count(a) > 0) edges[a].push_back({b, 1});
  else edges[a] = {{b, 1}};

  if(edges.count(b) > 0) edges[b].push_back({a, 1});
  else edges[b] = {{a, 1}};

  sort_neighbors(a);
  sort_neighbors(b);

}

template <typename T>
void Graph<T>::sort_neighbors(T a){

  sort(edges[a].begin(), edges[a].end());
  edges[a].erase(unique(edges[a].begin(), edges[a].end()), edges[a].end());

}

template <typename T>
void Graph<T>::print(vector<vector<char>> & grid){
  for(auto & edge : edges){
    cout<<"("<<edge.first.first<<","<<edge.first.second<<") '"<<grid[edge.first.first][edge.first.second]<<"'"<<endl;
    for(auto & x : edge.second){
      cout<<"  ("<<x.first.first<<","<<x.first.second<<") '"<<grid[x.first.first][x.first.second]<<"' "<<x.second<<endl;
    }
  }
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

map<string, vector<pair<char, int>>> dists_for_pos;
map<string, int> min_dist_for_keys;

void recursive_search(int & dist_min, Graph<Coordinate> & graph, map<char, Coordinate> & remaining_key_coords, map<char, Coordinate> & gate_coords, string keys_collected, int dist_total, Coordinate start){
  
  if(dist_total >= dist_min) return;

  vector<pair<char, int>> reachable_keys_dists;

  if(dists_for_pos.find(keys_collected) == dists_for_pos.end()){
    
    auto routine_start = chrono::steady_clock::now(); //XXX

    graph.run_dijkstra(start);

    for(auto & key : remaining_key_coords)
      if(graph.dist[key.second] != infinity
        && count(keys_collected.begin(), keys_collected.end(), key.first) == 0
      )
        reachable_keys_dists.push_back({key.first, graph.dist[key.second]});

    dists_for_pos[keys_collected] = reachable_keys_dists;

    auto routine_end = chrono::steady_clock::now(); //XXX
    chrono::duration<double> elapsed_seconds = routine_end - routine_start; //XXX
    time_in_routine += elapsed_seconds.count(); //XXX

  }
  else{
    
    reachable_keys_dists = dists_for_pos[keys_collected];

  }

  sort(keys_collected.begin(), keys_collected.end());
    
  if(min_dist_for_keys[keys_collected] > 0 && min_dist_for_keys[keys_collected] <= dist_total )
    return;
  else
    min_dist_for_keys[keys_collected] = dist_total;
  
  if(remaining_key_coords.size() == 0){
    
    if(dist_total < dist_min) dist_min = dist_total;

    cout<<dist_total<<endl;
    return;

  }

  for(auto & key : reachable_keys_dists){
    
    char & c = key.first;

    int new_dist_total = dist_total + key.second;

    map<char, Coordinate> new_remaining_key_coords(remaining_key_coords);
    string new_keys_collected(keys_collected);
    Graph<Coordinate> new_graph(graph); 

    new_keys_collected += c;

    new_graph.reactivate_node(gate_coords[toupper(c)]);
    new_remaining_key_coords.erase(c);

    recursive_search(dist_min, new_graph, new_remaining_key_coords, gate_coords, new_keys_collected, new_dist_total, remaining_key_coords[c]);

  }

}

int main(){
  
  ifstream in_file("example.txt");

  string line, field;

  vector<vector<char>> grid;

  while(getline(in_file, line)){
    
    grid.push_back({});
    
    for(char & c : line)
      grid.back().push_back(c);
    
  }

  Graph<Coordinate> graph;
  map<char, Coordinate> gate_coords;
  map<char, Coordinate> key_coords;
  Coordinate start;

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].size(); x++){

      if(grid[y][x] >= 'A' && grid[y][x] <= 'Z') gate_coords[grid[y][x]] = {y, x}; 
      if(grid[y][x] >= 'a' && grid[y][x] <= 'z') key_coords[grid[y][x]] = {y, x}; 
      if(grid[y][x] == '@') start = {y, x}; 

      if(grid[y][x] == '#') continue; 

      for(Coordinate & neighbour : get_neighbours({y, x}, grid))
        if(grid[neighbour.first][neighbour.second] != '#')
          graph.add_edge({y, x}, neighbour);

    }
  }
   

  graph.prune(grid);

  for(auto & gate : gate_coords)
    graph.deactivate_node(gate.second);

  graph.print(grid);

  int dist_min = infinity;

  recursive_search(dist_min, graph, key_coords, gate_coords, "", 0, start);

  cout<<dist_min<<endl;

  auto routine_end = chrono::steady_clock::now();

  chrono::duration<double> elapsed_seconds = routine_end - g_start;

  time_total += elapsed_seconds.count();

  cout<<time_total<<" "<<time_in_routine<<endl;

}
