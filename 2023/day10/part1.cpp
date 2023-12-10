#include<iostream>
#include<fstream>
#include<sstream>
#include<set>

using namespace std;

bool is_one_of(char & c, string str){

  for(char & s : str)
    if(c == s)
      return true;

  return false;

}

struct Node{
 
  char value = ' ';
  set<Node*> links;

  bool visited = false; //XXX

  void connect(Node *node){
    
    links.insert(node);
    node->links.insert(this);

  }

  Node *next(Node *prev){

    for(Node *n : links)
      if(n != prev)
        return n;

    return this;

  }

};

struct Graph{

  size_t n_rows, n_cols;

  int y = 0;
  
  Node *start = nullptr;

  Node **grid;

  Graph(size_t n_rows, size_t n_cols) : n_rows(n_rows), n_cols(n_cols){

   grid = new Node *[n_rows];

   for(size_t i=0; i<n_rows; ++i)
     grid[i] = new Node[n_cols];

  }

  ~Graph(){

    for(size_t i=0; i<n_rows; ++i)
      delete[] grid[i];

    delete[] grid;

  }

  void add_line(string & line){
    
    for(int x=0; x<line.length(); x++){

      grid[y][x].value = line[x];

      Node *new_node = & grid[y][x];
      Node *above = y == 0 ? nullptr : & grid[y - 1][x];
      Node *left = x == 0 ? nullptr : & grid[y][x - 1];

      if(line[x] == 'S')
        start = new_node;

      if(is_one_of(line[x], "|LJS") && above && is_one_of(above->value, "|7FS"))
        above->connect(& grid[y][x]);
      if(is_one_of(line[x], "-7JS") && left && is_one_of(left->value, "-LFS"))
        left->connect(& grid[y][x]);

    }

    y++;

  }

  void print(){
    for(int y=0; y<n_rows; ++y){
      for(int x=0; x<n_cols; ++x)
        if(grid[y][x].visited)
          cout << grid[y][x].value;
	else
	  cout << ' ';
      cout<<endl;
    }
    cout<<endl;
  }

  void print_links(){
    for(int y=0; y<n_rows; ++y){
      for(int x=0; x<n_cols; ++x)
        if(grid[y][x].links.size() == 0 || !(*grid[y][x].links.begin())->visited)
          cout<<' ';
        else
//          cout << (*grid[y][x].links.begin())->value;
          cout << grid[y][x].links.size();
      cout<<endl;
    }
    cout<<endl;
  }

};

int main(){
  
  string line;

  ifstream in_file("input.txt");
  
  getline(in_file, line);

  int n_cols =  line.length();
  int n_rows = 1;

  while(getline(in_file, line))
    n_rows++;

  Graph graph(n_cols, n_rows);

  in_file.clear();
  in_file.seekg(0, ios::beg);

  while(getline(in_file, line))
    graph.add_line(line);
  
  int n_steps = 0;

  Node *pos = graph.start;
  Node *prev = nullptr;

  do{
    
    pos->visited = true;
    
    cout << pos->value;

    Node *new_prev = pos;

    pos = pos->next(prev);

    prev = new_prev;

    n_steps++;

  }while(pos != graph.start);

//  graph.print();
  graph.print_links();

  cout << endl << n_steps / 2 << endl;

}
