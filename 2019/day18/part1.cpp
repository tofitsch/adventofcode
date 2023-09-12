#include<iostream>
#include<fstream>
#include<map>
#include<vector>
#include<algorithm>

using namespace std;

template <typename T> //T: type of nodes
struct Graph{
  
  map<T, vector<T>> edges;

  void add_edge(T, T);

  void print_pairs();
  void print_scalars();

};

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

vector<pair<int, int>> get_neighbours(pair<int, int> coord, vector<vector<char>> & grid){
  
  int y = coord.first;
  int x = coord.second;

  vector<pair<int, int>> neighbours;

  vector<pair<int, int>> possible_neighbours = {{y + 1, x}, {y, x + 1}, {y - 1, x}, {y, x - 1}};

  for(pair<int, int> neighbour : possible_neighbours)
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

  Graph<pair<int, int>> grid_graph;

  for(int y=0; y<grid.size(); y++){
    for(int x=0; x<grid[y].size(); x++){

      if(grid[y][x] == '#') continue; 

      for(pair<int, int> & neighbour : get_neighbours({y, x}, grid))
        if(grid[neighbour.first][neighbour.second] != '#')
          grid_graph.add_edge({y, x}, neighbour);

    }
  }

  grid_graph.print_pairs();

}
