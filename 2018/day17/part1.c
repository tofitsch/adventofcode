#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 32
#define MAX_X 1012
#define MAX_Y 2048

void read_line(char * line, bool (* grid)[MAX_X], int * x_min, int * y_min, int * x_max, int * y_max){
  
  char * pos_char_0 = & line[2];
  
  char * ptr = line;

  while(* ptr != ',')
    ptr++;
  
  * ptr = '\0';

  while(* ptr != '=')
    ptr++;

  ptr++;

  char * pos_char_1 = ptr;

  while(* ptr != '.')
    ptr++;

  * ptr = '\0';

  char * pos_char_2 = ptr + 2;

  int num_0 = atoi(pos_char_0);
  int num_1 = atoi(pos_char_1);
  int num_2 = atoi(pos_char_2);

  bool is_horizontal = (line[0] == 'y');

  if(is_horizontal){

    int y = num_0;

    if(y < * y_min)
      * y_min = y;

    if(y > * y_max)
      * y_max = y;

    if(num_1 < * x_min)
      * x_min = num_1;

    if(num_2 > * x_max)
      * x_max = num_2;

    for(int x=num_1; x<=num_2; x++)
      grid[y][x] = true;

  }
  else{

    int x = num_0;

    if(x < * x_min)
      * x_min = x;

    if(x > * x_max)
      * x_max = x;

    if(num_1 < * y_min)
      * y_min = num_1;

    if(num_2 > * y_max)
      * y_max = num_2;

    for(int y=num_1; y<=num_2; y++)
      grid[y][x] = true;

  }

}

int main(){
  
  bool grid[MAX_Y][MAX_X];

  int x_min = MAX_X;
  int y_min = MAX_Y;

  int x_max = 0;
  int y_max = 0;

  memset(grid, false, sizeof(grid));
  
  char line[MAX_LINE_LENGTH];
  
  FILE * in_file = fopen("example.txt", "r");

  while(fgets(line, sizeof(line), in_file) != NULL)
    read_line(line, grid, & x_min, & y_min, & x_max, & y_max);

  fclose(in_file);

  for(int y=y_min; y<=y_max; y++){

    for(int x=x_min; x<=x_max; x++)
      if(grid[y][x])
        printf("#");
      else
        printf(".");

    printf("\n");

  }

}
