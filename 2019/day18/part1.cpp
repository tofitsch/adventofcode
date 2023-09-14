#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> Coordinate;

const int infinity = 1e8;

template <typename T>
class Graph{
  
  private:

    map<T, vector<T>> edges;
    map<T, vector<T>> deactivated_edges;

    vector<T> queue;

  public:

    map<T, int> dist;

    void add_edge(T, T);

    void deactivate_node(T);
    void reactivate_node(T);

    void print_pairs();
    void print_scalars();

    void run_dijkstra(T);

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

    for(T & neighbor : edges[node])
      if(dist[node] + 1 < dist[neighbor])
        dist[neighbor] = dist[node] + 1;

  }

}

template <typename T>
void Graph<T>::deactivate_node(T a){
  
  for(T & b : edges[a])
    edges[b].erase(remove(edges[b].begin(), edges[b].end(), a), edges[b].end());

  deactivated_edges[a] = edges[a];

  edges[a] = {};
    
}

template <typename T>
void Graph<T>::reactivate_node(T a){
  
  for(T & b : deactivated_edges[a])
    edges[b].push_back(a);

  edges[a] = deactivated_edges[a];
    
}

template <typename T>
void Graph<T>::add_edge(T a, T b){
  
  if(edges.count(a) > 0) edges[a].push_back(b);
  else edges[a] = {b};

  sort(edges[a].begin(), edges[a].end());
  edges[a].erase(unique(edges[a].begin(), edges[a].end()), edges[a].end());

  if(edges.count(b) > 0) edges[b].push_back(a);
  else edges[b] = {a};

  sort(edges[b].begin(), edges[b].end());
  edges[b].erase(unique(edges[b].begin(), edges[b].end()), edges[b].end());

}

template <typename T>
void Graph<T>::print_pairs(){
  for(auto & edge : edges){
    cout<<"("<<edge.first.first<<","<<edge.first.second<<")"<<endl;
    for(auto & x : edge.second){
      cout<<"  ("<<x.first<<","<<x.second<<")"<<endl;
    }
  }
}

template <typename T>
void Graph<T>::print_scalars(){
  for(auto & edge : edges){
    cout<<edge.first<<endl;
    for(auto & x : edge.second){
      cout<<"  "<<x<<endl;
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

map<vector<char>, int> dist_min_for_given_keys_collected;

void recursive_search(int & dist_min, Graph<Coordinate> & graph, map<char, Coordinate> & remaining_key_coords, map<char, Coordinate> & gate_coords, vector<char> keys_collected, int dist_total, Coordinate start){

  if(dist_total >= dist_min) return;

  if(dist_min_for_given_keys_collected.find(keys_collected) == dist_min_for_given_keys_collected.end()
    || dist_min_for_given_keys_collected[keys_collected] > dist_total
    )
    dist_min_for_given_keys_collected[keys_collected] = dist_total;
  else
    return;

  if(dist_min_for_given_keys_collected[keys_collected] > dist_min)
    dist_min_for_given_keys_collected.erase(keys_collected);
  
  if(remaining_key_coords.size() == 0){
    
    if(dist_total < dist_min) dist_min = dist_total;

    for(char c : keys_collected) cout<<c;
    cout<<endl<<dist_total<<endl;
    return;

  }

  graph.run_dijkstra(start);

  vector<char> reachable_keys;

  for(auto & key : remaining_key_coords)
    if(graph.dist[key.second] != infinity
      && count(keys_collected.begin(), keys_collected.end(), key.first) == 0
    )
      reachable_keys.push_back(key.first);

  for(char & c : reachable_keys){

    int new_dist_total = dist_total + graph.dist[remaining_key_coords[c]];

    map<char, Coordinate> new_remaining_key_coords(remaining_key_coords);
    vector<char> new_keys_collected(keys_collected);
    Graph<Coordinate> new_graph(graph); 
  
    sort(new_keys_collected.begin(), new_keys_collected.end());

    new_keys_collected.push_back(c);
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

  for(auto & gate : gate_coords)
    graph.deactivate_node(gate.second);

  int dist_min = infinity;

  recursive_search(dist_min, graph, key_coords, gate_coords, {}, 0, start);

  cout<<dist_min<<endl;

//  graph.print_pairs();

}
