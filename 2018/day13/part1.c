#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define MAX_LINES 512
#define MAX_LINE_LENGTH 512
#define MAX_CARTS 64

typedef struct cart cart;

struct cart{

  int x, y;
  char facing, state;

};

void read_file(char * file_name, char (* grid)[MAX_LINE_LENGTH], cart carts[], int * n_carts, int * n_x, int * n_y){

  char line[MAX_LINE_LENGTH];

  FILE * in_file = fopen(file_name, "r");

  * n_carts = 0;

  * n_y = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    char * ptr = line;

    * n_x = 0;

    while(* ptr != '\n'){
      
      switch(* ptr){

        case '^':
          grid[* n_y][* n_x] = '|';
          break;

        case '>':
          grid[* n_y][* n_x] = '-';
          break;

        case 'v':
          grid[* n_y][* n_x] = '|';
          break;

        case '<':
          grid[* n_y][* n_x] = '-';
          break;

        default:
          grid[* n_y][* n_x] = * ptr;
          break;

      };

      if(* ptr == '^' || * ptr == '>' ||* ptr == 'v' ||* ptr == '<'){

        carts[* n_carts].x = * n_x;
        carts[* n_carts].y = * n_y;

        carts[* n_carts].facing = * ptr;

        carts[* n_carts].state = 0;

        (* n_carts)++;

      }
      

      ptr++;
      (* n_x)++;

    }

    (* n_y)++;

  }

  fclose(in_file);

}

int from_top_left(const void * a, const void * b) {

  const cart * cart_a = (const cart *) a;
  const cart * cart_b = (const cart *) b;

  if(cart_a->y > cart_b->y)
    return -1;

  if(cart_a->y < cart_b->y)
    return 1;

  if(cart_a->x > cart_b->x)
    return -1;

  if(cart_a->x < cart_b->x)
    return 1;

  return 0;

}

bool step(char (* grid)[MAX_LINE_LENGTH], bool (* grid_occupied)[MAX_LINE_LENGTH], cart carts[], int n_carts, int * crash_x, int * crash_y){

  qsort(carts, n_carts, sizeof(cart), from_top_left);

  for(int i=0; i<n_carts; i++){
    
    cart * c = & carts[i];

    grid_occupied[c->y][c->x] = false;
    
    switch(c->facing){

      case '^':
        c->y--;
        break;

      case '>':
        c->x++;
        break;

      case 'v':
        c->y++;
        break;

      case '<':
        c->x--;
        break;
        
    };

    if(grid_occupied[c->y][c->x]){
      
      * crash_x = c->x;
      * crash_y = c->y;

      return false;

    }

    grid_occupied[c->y][c->x] = true;

    switch(grid[c->y][c->x]){
      
      case '/':
        switch(c->facing){

          case '^':
            c->facing = '>';
            break;

          case '>':
            c->facing = '^';
            break;

          case 'v':
            c->facing = '<';
            break;

          case '<':
            c->facing = 'v';
            break;

        };
        break;

      case '\\':
        switch(c->facing){

          case '^':
            c->facing = '<';
            break;

          case '>':
            c->facing = 'v';
            break;

          case 'v':
            c->facing = '>';
            break;

          case '<':
            c->facing = '^';
            break;

        };
        break;

      case '+':
        switch(c->facing){

          case '^':
            switch(c->state){

              case 0:
                c->facing = '<';
                break;

              case 2:
                c->facing = '>';
                break;

            };
            break;

          case '>':
            switch(c->state){

              case 0:
                c->facing = '^';
                break;

              case 2:
                c->facing = 'v';
                break;

            };
            break;

          case 'v':
            switch(c->state){

              case 0:
                c->facing = '>';
                break;

              case 2:
                c->facing = '<';
                break;

            };
            break;

          case '<':
            switch(c->state){

              case 0:
                c->facing = 'v';
                break;

              case 2:
                c->facing = '^';
                break;

            };
            break;

        };
        c->state++;
        c->state %= 3;
        break;

    };

  }

  return true;

}

int main(){
  
  char grid[MAX_LINES][MAX_LINE_LENGTH];
  bool grid_occupied[MAX_LINES][MAX_LINE_LENGTH];

  memset(grid_occupied, false, sizeof(grid_occupied));

  cart carts[MAX_CARTS];

  int n_carts, n_x, n_y;

  read_file("input.txt", grid, carts, & n_carts, & n_x, & n_y);

  int crash_x, crash_y;

  while(step(grid, grid_occupied, carts, n_carts, & crash_x, & crash_y))
    continue;

  printf("%i,%i\n", crash_x, crash_y);

}
