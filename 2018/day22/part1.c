#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 64

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

//  printf("%i, %i, %i\n", depth, target_x, target_y);

  int  erosion_lvl[target_y + 1][target_x + 1];
  char   tile_type[target_y + 1][target_x + 1];

  int geo_idx;

  for(int x=0; x<=target_x; ++x)
    erosion_lvl[0][x] = (x * 16807 + depth) % 20183;

  for(int y=0; y<=target_y; ++y)
    erosion_lvl[y][0] = (y * 48271 + depth) % 20183;

  //anti-diagonal traversal

  //anti-diagonal traversal
//  int const Y = 4;
//  int const X = 2;
//  int arr[4][2] = {1, 2,
//                   3, 4,
//                   5, 6,
//                   7, 8};
  
  int const Y = 4;
  int const X = 3;
  int arr[4][3] = {{ 1,  2,  3},
                   { 4,  5,  6},
                   { 7,  8,  9},
                   {10, 11, 12}};

  for(int y=0; y<Y; ++y) {

    for(int x=0; x<X; ++x)
      printf("%i", arr[y][x]);
    
    printf("\n");

  }

  printf("\n");

  /*
     anti-diagonal traversal

     consider e.g. the matrix

     123
     456
     789
     ABC

     shifting like so:

     123xxx
     x456xx
     xx789x
     xxxABC

     and traversing top to bottom for each column

  */


  for(int x = 0; x < X + Y - 1; ++x) {
    
    for(int y = (x >= X ? x - X + 1 : 0); y < (x <= X - 1 ? x + 1 : Y); ++y)
      printf("%i ", arr[y][x - y]);
    
    printf("\n");

  }

}
