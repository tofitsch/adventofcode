#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>

#define MAX_LINE_LENGTH 16384
#define INF 1e8;

typedef struct node node;
typedef struct cursor cursor;

int const N = 50;

int dir[128];

struct node {
 
  node * edge[4];

  node * bfs_next;

  bool bfs_visited;

  bool done[4];

};

struct cursor {
  
  char * regex_ptr;
  node * graph_ptr;

  cursor * next;

};

node * add_node() {
  
  node * n = malloc(sizeof(node));

  for(int i=0; i<4; ++i)
    n->edge[i] = NULL;

  n->bfs_next = NULL;

  n->bfs_visited = false;

  for(int i=0; i<4; ++i)
    n->done[i] = false;

  return n;

}

node * add_edge(node * a, char dir_str) {
  
  node * b = a->edge[dir[dir_str]];
  
  if(b == NULL) {

    b = add_node();

    a->edge[dir[dir_str]] = b;
    b->edge[(dir[dir_str] + 2) % 4] = a;

  }
  
  return b;

}

cursor * add_cursor(char * regex_ptr, node * graph_ptr) {

  cursor * c = malloc(sizeof(cursor));

  c->regex_ptr = regex_ptr;
  c->graph_ptr = graph_ptr;

  c->next = NULL;

  return c;

}

void queue_node(node * queue, node * n) {

  while(queue->bfs_next != NULL)
    queue = queue->bfs_next;

  queue->bfs_next = n;

}

void append_cursor(cursor * prev) {

  cursor * c = add_cursor(prev->regex_ptr, prev->graph_ptr);
  
  while(prev->next != NULL)
    prev = prev->next;

  prev->next = c;

}

cursor * regex_step(cursor * c) {
  
  if(c == NULL)
    return NULL;
  
  c->regex_ptr++;

  cursor * tmp = c;

  int n_par_l, n_par_r;

  switch(* c->regex_ptr){
    
    case ')':
    case '$':
      c = c->next;
      free(tmp);
      break;

    case '(':
      append_cursor(c);
      n_par_l = 0;
      n_par_r = 0;
      do{

        c->regex_ptr++;

        if(* c->regex_ptr == '(')
          n_par_l++;
        else if(* c->regex_ptr == ')')
          n_par_r++;

      }
      while(* c->regex_ptr != '|' || n_par_r != n_par_l);
      break;

    case '|':
      n_par_l = 0;
      n_par_r = 0;
      do{

        c->regex_ptr++;

        if(* c->regex_ptr == '(')
          n_par_l++;
        else if(* c->regex_ptr == ')')
          n_par_r++;

      }
      while(* c->regex_ptr != ')' || n_par_r != n_par_l + 1);
      break;

    default:
      c->graph_ptr = add_edge(c->graph_ptr, * (c->regex_ptr));
      break;

  };

  return c;

}

void fill_grid(char (* grid)[N], node * n, int x, int y){

  if(n == NULL)
    return;
  
  grid[x][y] = '.';

  for(int i=0; i<4; ++i){
    
    if(n->done[i] || n->edge[i] == NULL)
      continue;

    n->done[i] = true;
      
    switch(i){

      case 0:
        grid[x][y - 1] = '-';
        fill_grid(grid, n->edge[i], x, y - 2);
        break;

      case 1:
        grid[x + 1][y] = '|';
        fill_grid(grid, n->edge[i], x + 2, y);
        break;

      case 2:
        grid[x][y + 1] = '-';
        fill_grid(grid, n->edge[i], x, y + 2);
        break;

      case 3:
        grid[x - 1][y] = '|';
        fill_grid(grid, n->edge[i], x - 2, y);
        break;
        
    };

  }
  
}

void print_grid(char (* grid)[N]){

  for(int y=0; y<N; ++y){

    for(int x=0; x<N; ++x)
      printf("%c", grid[x][y]);

    printf("\n");

  }

}

node * get_end(node * n) {
  
  while(n->bfs_next != NULL)
    n = n->bfs_next;

  return n;

}

int bfs_recurse(node * n, int n_steps){
  
  if(n == NULL)
    return n_steps;
  
  node * end = get_end(n);
  
  do{
    
    n->bfs_visited = true;

    for(int i=0; i<4; ++i)
      if(n->edge[i] != NULL && ! n->edge[i]->bfs_visited)
        queue_node(n, n->edge[i]);

    n = n->bfs_next;

  }
  while(n != end->bfs_next);

  return bfs_recurse(n, n_steps + 1);

}

int main() {

  dir['N'] = 0;
  dir['E'] = 1;
  dir['S'] = 2;
  dir['W'] = 3;

  char line[MAX_LINE_LENGTH];

  FILE * in_file = fopen("input.txt", "r");

  fgets(line, sizeof(line), in_file);

  fclose(in_file);

  node * start_node = add_node();

  cursor * active_cursor = add_cursor(line, start_node);

  while(active_cursor != NULL)
    active_cursor = regex_step(active_cursor);

  char grid[N][N];

  for(int x=0; x<N; ++x)
    for(int y=0; y<N; ++y)
      grid[x][y] = '#';

//  fill_grid(grid, start_node, N / 2, N / 2);
//  print_grid(grid);

  printf("%i\n", bfs_recurse(start_node, 0) - 1);

}
