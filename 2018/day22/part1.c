#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MOD 20183
#define FAC_X 48271
#define FAC_Y 16807

void read_input(int * depth, int * target_x, int * target_y) {
  
  FILE * in_file = fopen("example.txt", "r");

  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  char * ptr = line;

  while(* ptr != ' ')
    ptr++;

  * depth = atoi(ptr);

  fgets(line, sizeof(line), in_file);

  ptr = line;

  while(* ptr != ',')
    ptr++;

  * ptr = '\0';

  ptr = line;

  while(* ptr != ' ')
    ptr++;

  * target_x = atoi(ptr);

  while(* ptr != '\0')
    ptr++;

  * target_y = atoi(ptr + 1);

  fclose(in_file);

}

int main() {
  
  int depth, target_x, target_y;

  read_input(& depth, & target_x, & target_y);

  printf("%i, %i, %i\n", depth, target_x, target_y);

  int  erosion_lvl[target_y + 1][target_x + 1];
  char   tile_type[target_y + 1][target_x + 1];

  for(int x=0; x<=target_x; ++x)
    erosion_lvl[0][x] = (x * FAC_Y + depth) % MOD;

  for(int y=0; y<=target_y; ++y)
    erosion_lvl[y][0] = (y * FAC_X + depth) % MOD;

  /*
     anti-diagonal traversal

     consider e.g. the matrix arr[Y=4][X=3]:

     123
     456
     789
     ABC

     shifting like so:

     123xxx
     x456xx
     xx789x
     xxxABC

     and traversing top to bottom for each column traverses anti-diagonally over the whole matrix:

     for(int x = 0; x < X + Y - 1; ++x)
       for(int y = (x >= X ? x - X + 1 : 0); y < (x <= X - 1 ? x + 1 : Y); ++y)
         printf("%i ", arr[y][x - y]);

     1
     2 4
     3 5 7
     6 8 A
     9 B
     C


     in addition to that, the following skips row 0 and column 0 of the original matrix

  */


  int X = target_x + 1;
  int Y = target_y + 1;

  for(int x = 0; x < X + Y - 1; ++x)
    for(int y = (x >= X ? x - X + 1 : 1); y < (x <= X ? x : Y); ++y)
      erosion_lvl[y][x - y] = (erosion_lvl[y - 1][x - y] * erosion_lvl[y][x - y - 1] + depth) % MOD;

  erosion_lvl[target_y][target_x] = depth % MOD;

/*
  for(int y=0; y<=target_y; ++y) {

    for(int x=0; x<=target_x; ++x) {

      switch(erosion_lvl[y][x] % 3) {
        
        case 0:
          printf(".");
          break;

        case 1:
          printf("=");
          break;

        case 2:
          printf("|");
          break;

      };

    }

    printf("\n");

  }
 */
  
  int risk_lvl = 0;

  for(int y=0; y<=target_y; ++y)
    for(int x=0; x<=target_x; ++x)
      risk_lvl += erosion_lvl[y][x] % 3;

  printf("%i\n", risk_lvl);

}
