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

  for(int x=0; x<GRID_SIZE; x++)
    for(int y=0; y<GRID_SIZE; y++)
      grid[y][x] = power_level(x + 1, y + 1, serial_num);

  int max = 0;

  int x_max, y_max;

  for(int x=0; x<GRID_SIZE - 2; x++){
    for(int y=0; y<GRID_SIZE - 2; y++){

      int conv = 0;

       for(int dx=0; dx<3; dx++)
         for(int dy=0; dy<3; dy++)
           conv += grid[y + dy][x + dx];

       if(conv > max){

         max = conv;

         x_max = x;
         y_max = y;

       }

    }
  }

  printf("%i,%i\n", x_max + 1, y_max + 1);

}
