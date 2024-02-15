#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINES 64
#define MAX_LINE_LENGTH 16

int manhattan_dist(int x0, int y0, int x1, int y1){
  
  return abs(x0 - x1) + abs(y0 - y1);

}

void read_line(char * line, int * x, int * y){

    char str_x[MAX_LINE_LENGTH];

    char * itr = str_x;

    while(* line != ','){
      
      * itr = * line;

      line++;
      itr++;

    }

    * itr = '\0';

    line++;
      
    * x = atoi(str_x);
    * y = atoi(line);

}

int main(){
  
  FILE * in_file = fopen("input.txt", "r");

  char line[MAX_LINE_LENGTH];

  int arr_x[MAX_LINES];
  int arr_y[MAX_LINES];

  int n_lines = 0;

  int x_min = 1e9;
  int y_min = 1e9;

  int x_max = 0;
  int y_max = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){

    read_line(line, & arr_x[n_lines], & arr_y[n_lines]);

    if(arr_x[n_lines] < x_min)
      x_min = arr_x[n_lines];

    if(arr_x[n_lines] > x_max)
      x_max = arr_x[n_lines];

    if(arr_y[n_lines] < y_min)
      y_min = arr_y[n_lines];

    if(arr_y[n_lines] > y_max)
      y_max = arr_y[n_lines];

    n_lines++;

  }

  x_max -= x_min;
  y_max -= y_min;

  int voronoi_dist[y_max + 1][x_max + 1];
  int voronoi_id[y_max + 1][x_max + 1];

  for(int x=0; x<=x_max; x++){
    for(int y=0; y<=y_max; y++){

      voronoi_dist[y][x] = 1e9;

      for(int i=0; i<n_lines; i++){
        
        int dist = manhattan_dist(x, y, arr_x[i] - x_min, arr_y[i] - y_min);

        if(dist < abs(voronoi_dist[y][x])){
          
          voronoi_dist[y][x] = dist;
          voronoi_id[y][x] = i;

        }

        else if(dist == voronoi_dist[y][x] && i != voronoi_id[y][x]){

          voronoi_dist[y][x] *= -1;
          voronoi_id[y][x] = -1;

        }

      }

    }
  }

  int voronoi_area[n_lines];
  bool touches_border[n_lines];

  memset(touches_border, false, sizeof(touches_border));
  memset(voronoi_area, 0, sizeof(voronoi_area));

  for(int x=0; x<=x_max; x++){
    for(int y=0; y<=x_max; y++){
      
      if(voronoi_id[y][x] < 0)
        continue;
      
      if(x == 0 || x == x_max || y == 0 || y == y_max)
        touches_border[voronoi_id[y][x]] = true;

      voronoi_area[voronoi_id[y][x]]++;

    }
  }

  int max_area = 0;

  for(int i=0; i<n_lines; i++)
    if(! touches_border[i] && voronoi_area[i] > max_area)
      max_area = voronoi_area[i];
  
  printf("%i\n", max_area);

}
