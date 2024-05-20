#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LINE_LENGTH 16
#define GRID_SIZE 300

int power_level(int x, int y, int serial_num){
  
  int rack_id = x + 10;

  int power = rack_id * y;

  power += serial_num;

  power *= rack_id;

  power /= 100;

  power %= 10;

  power -= 5;

  return power;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");
  
  char line[MAX_LINE_LENGTH];

  fgets(line, sizeof(line), in_file);

  fclose(in_file);

  int serial_num = atoi(line);

  int grid[GRID_SIZE][GRID_SIZE];
  int grid_conv[GRID_SIZE][GRID_SIZE];

  memset(grid_conv, 0, sizeof(grid_conv));

  for(int x=0; x<GRID_SIZE; x++)
    for(int y=0; y<GRID_SIZE; y++)
      grid[y][x] = power_level(x + 1, y + 1, serial_num);

  int x_max, y_max, z_max;

  int max = 0;

  for(int z=0; z<300; z++){
    
    for(int x=0; x<GRID_SIZE - z; x++){
      for(int y=0; y<GRID_SIZE - z; y++){

         for(int dx=0; dx<=z; dx++)
           grid_conv[y][x] += grid[y + z][x + dx];

         for(int dy=0; dy<=z; dy++)
           grid_conv[y][x] += grid[y + dy][x + z];

         grid_conv[y][x] -= grid[y + z][x + z];

         if(grid_conv[y][x] > max){

           max = grid_conv[y][x];

           x_max = x;
           y_max = y;
           z_max = z;

         }

      }
    }

  }

  printf("%i,%i,%i\n", x_max + 1, y_max + 1, z_max + 1);

}
