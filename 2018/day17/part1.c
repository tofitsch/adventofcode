#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 32
#define MAX_STACK 32768
#define MAX_X 1024
#define MAX_Y 2048
#define SOURCE_X 500

typedef struct coord coord;

struct coord{

  int x, y;

};

void read_line(char * line, char (* grid)[MAX_X], int * x_min, int * y_min, int * x_max, int * y_max){
  
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
      grid[y][x] = '#';

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
      grid[y][x] = '#';

  }

}

void rm_coord(int * idx, coord a[], int * n){
  
  (* n)--;
 
  for(int i=* idx; i<* n; i++)
    a[i] = a[i + 1];

  (* idx)--;

}

void insert_coord(int * idx, coord a[], int * n, int y, int x){
  
  for(int i=(* n) - 1; i>* idx; i--)
    a[i + 1] = a[i];

  (* idx)++;

  a[* idx].x = x;
  a[* idx].y = y;

  (* n)++;


}

void print_grid(char (* grid)[MAX_X], int x_min, int y_min, int x_max, int y_max){
  
  printf("\n");

  for(int y=y_min; y<=y_max; y++){

    for(int x=x_min; x<=x_max; x++)
        printf("%c", grid[y][x]);

    printf("\n");

  }

}

int main(){
  
  char grid[MAX_Y][MAX_X];

  int x_min = MAX_X;
  int y_min = MAX_Y;

  int x_max = 0;
  int y_max = 0;

  memset(grid, ' ', sizeof(grid));
  
  char line[MAX_LINE_LENGTH];
  
  FILE * in_file = fopen("input.txt", "r");

  while(fgets(line, sizeof(line), in_file) != NULL)
    read_line(line, grid, & x_min, & y_min, & x_max, & y_max);

  fclose(in_file);

  coord stack[MAX_STACK];

  int n_water = 0;

  int n_water_prev = -1;

  int n_settled = 0;

  int n_total = 0;
  int n_total_prev = -1;

  for(int r=0; r<1600; r++){//XXX
//  for(int r=0; r<0; r++){//XXX
//  while(n_total_prev != n_total){//XXX
    
    n_total_prev = n_total;
    
    water[n_water].x = SOURCE_X;
    water[n_water].y = 0;

    n_water++;

    for(int i=0; i<n_water; i++){
      
      coord * w = & water[i];

      if(w->y == y_max){

        grid[w->y][w->x] = ' ';

        rm_coord(& i, water, & n_water);

      }
      else if(grid[w->y + 1][w->x] == ' '){

        grid[w->y][w->x] = ' ';

        w->y++;

        grid[w->y][w->x] = '~';


      }
      else if(grid[w->y][w->x - 1] == ' '){

        if(grid[w->y][w->x + 1] == ' '){
          
          insert_coord(& i, water, & n_water, w->y, w->x + 1);

          grid[w->y][w->x + 1] = '~';

        }

        grid[w->y][w->x] = ' ';

        w->x--;

        grid[w->y][w->x] = '~';

      }
      else if(grid[w->y][w->x + 1] == ' '){

        grid[w->y][w->x] = ' ';

        w->x++;

        grid[w->y][w->x] = '~';

      }
      else{

        grid[w->y][w->x] = '-';

        rm_coord(& i, water, & n_water);

        n_settled++;

      }

    }

    n_total = n_water + n_settled;

//    printf("%i\n", n_total);
    
  }

  print_grid(grid, x_min, y_min, x_max, y_max);

  printf("%i\n", n_total);

}
