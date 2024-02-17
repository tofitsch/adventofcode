#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_LINE_LENGTH 64
#define MAX_LINES 512

typedef struct star star;

struct star{

  int x, y, v_x, v_y;

};

int substr_to_int(char * str, int beg, int end){ //TODO: lib

  char buff[end - beg + 1];

  strncpy(buff, str + beg, end - beg);

  buff[end - beg] = '\0';

  return strtol(buff, NULL, 10);

}

void simulate(int t, star stars[], int n_stars, int * x_min, int * x_max, int * y_min, int * y_max){

  * x_min = 1e8; 
  * y_min = 1e8; 

  * x_max = -1e8; 
  * y_max = -1e8; 

  for(int i=0; i<n_stars; i++){

    stars[i].x += t * stars[i].v_x;
    stars[i].y += t * stars[i].v_y;

    if(stars[i].x < * x_min)
      * x_min = stars[i].x;

    if(stars[i].x > * x_max)
      * x_max = stars[i].x;

    if(stars[i].y < * y_min)
      * y_min = stars[i].y;

    if(stars[i].y > * y_max)
      * y_max = stars[i].y;

  }

}

void read_line(char * line, star * s){
  

  s->x   = substr_to_int(line, 10, 16);
  s->y   = substr_to_int(line, 18, 24);
  s->v_x = substr_to_int(line, 36, 38);
  s->v_y = substr_to_int(line, 40, 42);

}

int main(){
  
  FILE * in_file = fopen("input.txt", "r");
  
  char line[MAX_LINE_LENGTH];

  star stars[MAX_LINES];

  int n_stars = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){

    read_line(line, & stars[n_stars]);

    n_stars++;

  }

  fclose(in_file);
  
  int x_min, x_max, y_min, y_max;

  long area;

  long min_area = 1e12;

  int t_min_area;

  int t = 0;

  while(true){

    simulate(1, stars, n_stars, & x_min, & x_max, & y_min, & y_max);

    area = x_max - x_min;
    area *= y_max - y_min;

    if(area < min_area){

      min_area = area;

      t_min_area = t;

    }

    if(area > min_area * 10)
      break;

    t++;

  }

  printf("%i\n", t_min_area + 1);

}
