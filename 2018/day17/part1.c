#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 32
#define MAX_STACK 65536
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

void print_grid(char (* grid)[MAX_X], int x_min, int y_min, int x_max, int y_max){
  
  for(int y=0; y<=y_max; y++){
    
//    printf("%3i", y);

    for(int x=x_min - 2; x<=x_max + 1; x++){

        if(grid[y][x] == 'x' || grid[y][x] == '|' || grid[y][x] == '.')
          printf("x");
        else if(grid[y][x] == '#')
          printf("#");
        else
          printf(".");

    }

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

  coord water[MAX_STACK];

  water[0].x = SOURCE_X;
  water[0].y = 0;

  grid[0][SOURCE_X] = '|';

  int n_water = 1;

  bool done = false;
  
  while(! done){
//  for(int r=0; r<1357; r++){
   
    done = true;
   
    for(int i=0; i<n_water; i++){
          
      coord * w = & water[i];

//      printf("%i %i %c %i %i\n", r, i, grid[w->y][w->x], w->y, w->x);

      switch(grid[w->y][w->x]){
        
        case '|':

          if(w->y == y_max){

            grid[w->y][w->x] = '.';

          }
          else if(grid[w->y + 1][w->x] == ' '){
            
            water[n_water].x = w->x;
            water[n_water].y = w->y + 1;

            n_water++;

            grid[w->y + 1][w->x] = '|';

            done = false;

          }
          else if(grid[w->y + 1][w->x] == 'x' || grid[w->y + 1][w->x] == '#'){
            
            for(int x=w->x; x>=x_min - 1; x--)
              if(grid[w->y][x] == '#' || grid[w->y + 1][x] == ' ' || grid[w->y + 1][x] == '#')
                break;
              else if(grid[w->y + 1][x] == '|' || grid[w->y + 1][x] == '~' || grid[w->y][x] == '~')
                goto brk;

            for(int x=w->x; x<=x_max + 1; x++)
              if(grid[w->y][x] == '#' || grid[w->y + 1][x] == ' ' || grid[w->y + 1][x] == '#')
                break;
              else if(grid[w->y + 1][x] == '|' || grid[w->y + 1][x] == '~' || grid[w->y][x] == '~')
                goto brk;

            grid[w->y][w->x] = '~';

            done = false;

            brk:;

          }

          break;

        case '~':

          if(grid[w->y + 1][w->x] == 'x' || grid[w->y + 1][w->x] == '#'){

            if(grid[w->y][w->x + 1] == ' '){

              water[n_water].y = w->y;
              water[n_water].x = w->x + 1;

              n_water++;

              grid[w->y][w->x + 1] = '~';

            }

            if(grid[w->y][w->x - 1] == ' '){

              water[n_water].y = w->y;
              water[n_water].x = w->x - 1;

              n_water++;

              grid[w->y][w->x - 1] = '~';

            }

            grid[w->y][w->x] = 'x';

          }
          else
            grid[w->y][w->x] = '|';

          done = false;

          break;

      };

    }
      
  }

  int ctr = 0;

  for(int y=y_min; y<=y_max; y++)
    for(int x=x_min - 1; x<=x_max + 1; x++)
      if(grid[y][x] == 'x' || grid[y][x] == '|' || grid[y][x] == '.')
        ctr++;

//  print_grid(grid, x_min, y_min, x_max, y_max);

  printf("%i\n", ctr);

}
