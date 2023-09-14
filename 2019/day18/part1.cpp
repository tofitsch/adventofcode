#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

typedef pair<int, int> Coordinate;

template <typename T>
class Graph{
  
  private:

    map<T, vector<T>> edges;
    map<T, vector<T>> deactivated_edges;

    map<T, int> dist;
    vector<T> queue;

    int infinity = 1e8;

  public:

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
  for(auto & key : edges){
    cout<<"("<<key.first.first<<","<<key.first.second<<")"<<endl;
    for(auto & x : key.second){
      cout<<"  ("<<x.first<<","<<x.second<<")"<<endl;
    }
  }
}

template <typename T>
void Graph<T>::print_scalars(){
  for(auto & key : edges){
    cout<<key.first<<endl;
    for(auto & x : key.second){
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
  map<char, Coordinate> gates;
  map<char, Coordinate> keys;
  Coordinate start;

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].size(); x++){

      if(grid[y][x] >= 'A' && grid[y][x] <= 'Z') gates[grid[y][x]] = {y, x}; 
      if(grid[y][x] >= 'a' && grid[y][x] <= 'z') keys[grid[y][x]] = {y, x}; 
      if(grid[y][x] == '@') start = {y, x}; 

      if(grid[y][x] == '#') continue; 

      for(Coordinate & neighbour : get_neighbours({y, x}, grid))
        if(grid[neighbour.first][neighbour.second] != '#')
          graph.add_edge({y, x}, neighbour);

    }
  }

  for(auto & key : gates)
    graph.deactivate_node(key.second);

//  graph.print_pairs();

  graph.run_dijkstra(start);

}
