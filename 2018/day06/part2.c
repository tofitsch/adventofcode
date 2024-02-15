#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINES 64
#define MAX_LINE_LENGTH 16
#define MAX_DIST 10000

int manhattan_dist(int x0, int y0, int x1, int y1){
  
  return abs(x0 - x1) + abs(y0 - y1);

}

void update_area(int x, int y, int arr_x[], int arr_y[], int n_lines, int * area, bool * full_area_contained){
    
     
      int dist = 0;

      for(int l=0; l<n_lines; l++)
        dist += manhattan_dist(x, y, arr_x[l], arr_y[l]);

      if(dist < MAX_DIST){

        (* area)++;
        (* full_area_contained) = false;

      }

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

  int area = 0;

  bool full_area_contained;

  int x_origin = (x_max - x_min) / 2;
  int y_origin = (y_max - y_min) / 2;
      
  int x, y;

  int spiral_ctr = 0;

  int side_length = 1;
  
  do{

    full_area_contained = true;

    x = x_origin - spiral_ctr;
    y = y_origin - spiral_ctr;

    for(int i=0; i<side_length; i++){

      update_area(x, y, arr_x, arr_y, n_lines, & area, & full_area_contained);

      x++;

    }

    for(int i=0; i<side_length; i++){

      update_area(x, y, arr_x, arr_y, n_lines, & area, & full_area_contained);

      y++;

    }

    for(int i=0; i<side_length; i++){

      update_area(x, y, arr_x, arr_y, n_lines, & area, & full_area_contained);

      x--;

    }

    for(int i=0; i<side_length; i++){

      update_area(x, y, arr_x, arr_y, n_lines, & area, & full_area_contained);

      y--;

    }

    side_length += 2;

    spiral_ctr++;

  }while(! full_area_contained);

  printf("%i\n", area);

}
