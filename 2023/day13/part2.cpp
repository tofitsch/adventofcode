#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>

using namespace std;

vector<string> transpose(vector<string> & grid){

  int n_x = grid[0].length();
  int n_y = grid.size();

  vector<string> grid_t(n_x, "");

  for(int x=0; x<n_x; x++)
    for(int y=0; y<n_y; y++)
      grid_t[x] += grid[y][x];

  return grid_t;

}

bool more_than_one_char_diff(string & a, string & b){
  
  int n_differences = 0;
  
  for(int i=0; i<a.length(); i++){
    if(a[i] != b[i]){
      
      n_differences++;

      if(n_differences > 1)
        return true;

    }
  }

  return false;

}

int get_mirror_pos(vector<string> & grid){
  
  for(int i=1; i<grid.size(); i++){

    bool is_axis = true;

    int n_differences = 0;

    for(int j=1; j<=max(i, (int) grid.size() - i); j++){
      
     
      if((i + j - 1 < grid.size() && i - j >= 0 ) && grid[i + j - 1] != grid[i - j]){
        
	if(more_than_one_char_diff(grid[i + j - 1], grid[i - j])){
	  
	  is_axis = false;
	  break;

	}
	else{

	  n_differences++;

	  if(n_differences > 1){
	    
	    is_axis = false;
	    break;

	  }

	}

      }

    }

    if(is_axis && n_differences == 1)
      return i;

  }

  return -1;

}

int main(){

  string line;

  ifstream in_file("input.txt");

  vector<vector<string>> grids = {{}};

  while(getline(in_file, line))
    if(line.length() > 0)
      grids.back().push_back(line);
    else
      grids.push_back({});

  int sum = 0;

  for(vector<string> & grid : grids){
    
    int axis_h = get_mirror_pos(grid);

    if(axis_h >= 0)
      sum += axis_h * 100;
    else{

      vector<string> grid_t = transpose(grid);
      
      int axis_v = get_mirror_pos(grid_t);

      if(axis_v >= 0)
        sum += axis_v;

    }

  }

  cout << sum << endl;

}
