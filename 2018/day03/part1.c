#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int substr_to_int(char * str, int beg, int end){
  
  char buff[end - beg + 1];

  strncpy(buff, str + beg, end - beg);

  buff[end - beg] = '\0';

  return strtol(buff, NULL, 10);

}

void parse_line(char * line, int * x0, int * y0, int * x1, int * y1){

  int pos_at, pos_comma, pos_colon, pos_x, pos_end;

  int i = 0;

  while(line[i] != '\0'){
    
    switch(line[i]){

      case '@':
        pos_at = i;
        break;

      case ',':
        pos_comma = i;
        break;
      
      case ':':
        pos_colon = i;
        break;

      case 'x':
        pos_x = i;
        break;

      case '\n':
        pos_end = i;
        break;

    };
    
    i++;

  }

  * x0 = substr_to_int(line, pos_at + 1, pos_comma);
  * y0 = substr_to_int(line, pos_comma + 1, pos_colon);
  * x1 = substr_to_int(line, pos_colon + 1, pos_x);
  * y1 = substr_to_int(line, pos_x + 1, pos_end);

  * x1 += * x0 - 1;
  * y1 += * y0 - 1;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  int grid[1000][1000];

  memset(grid, 0, sizeof(grid));

  char line[64];

  int ctr = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){
   
    int x0, y0, x1, y1;

    parse_line(line, & x0, & y0, & x1, & y1);

    for(int x=x0; x<=x1; x++)
      for(int y=y0; y<=y1; y++){

        grid[y][x]++;

        if(grid[y][x] == 2)
          ctr++;

      }

  }

  printf("%i\n", ctr);

  fclose(in_file);

}
