#include<stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>

#define GRID_SIZE 50
#define N_STEPS 1000000000
#define MAX_STEPS 1000
#define MAX_LOOKBACK 100

typedef struct tile tile;
typedef struct state state;

struct state {

  char value;
  int n_neigh_tree, n_neigh_lumb;

};

struct tile {
  
  state current, next;

  int n_neigh;

  tile * neigh[8];

};

void update_tile_next(tile * t, char value) {

  t->next.value = value;

  if(t->current.value == '|')
    for(int n=0; n<t->n_neigh; ++n)
      t->neigh[n]->next.n_neigh_tree--;
  else if(t->current.value == '#')
    for(int n=0; n<t->n_neigh; ++n)
      t->neigh[n]->next.n_neigh_lumb--;
  
  if(t->next.value == '|')
    for(int n=0; n<t->n_neigh; ++n)
      t->neigh[n]->next.n_neigh_tree++;
  else if(t->next.value == '#')
    for(int n=0; n<t->n_neigh; ++n)
      t->neigh[n]->next.n_neigh_lumb++;

}

void evolve_tile(tile * t) {
  
  if(t->current.value == '.' && t->current.n_neigh_tree >= 3)
    update_tile_next(t, '|');
  else if(t->current.value == '|' && t->current.n_neigh_lumb >= 3)
    update_tile_next(t, '#');
  else if(t->current.value == '#' && (t->current.n_neigh_lumb == 0 || t->current.n_neigh_tree == 0))
    update_tile_next(t, '.');

}

void promote_next_to_current(tile (* grid)[GRID_SIZE]) {

  for(int y=0; y<GRID_SIZE; ++y) {
    for(int x=0; x<GRID_SIZE; ++x) {

      grid[y][x].current.value = grid[y][x].next.value;
      grid[y][x].current.n_neigh_tree = grid[y][x].next.n_neigh_tree;
      grid[y][x].current.n_neigh_lumb = grid[y][x].next.n_neigh_lumb;

    }
  }

}

void step(tile (* grid)[GRID_SIZE]) {

  for(int y=0; y<GRID_SIZE; ++y)
    for(int x=0; x<GRID_SIZE; ++x)
      evolve_tile(& grid[y][x]);

  promote_next_to_current(grid);

}

void init_grid(tile (* grid)[GRID_SIZE]) {

  for(int y=0; y<GRID_SIZE; ++y) {
    for(int x=0; x<GRID_SIZE; ++x) {

      grid[y][x].n_neigh = 0;

      grid[y][x].current.n_neigh_tree = 0;
      grid[y][x].current.n_neigh_lumb = 0;

      grid[y][x].next.n_neigh_tree = 0;
      grid[y][x].next.n_neigh_lumb = 0;

      for(int X=x-1; X<=x+1; ++X) {
        for(int Y=y-1; Y<=y+1; ++Y) {

          if(X < 0 || X >= GRID_SIZE || Y < 0 || Y >= GRID_SIZE || (X == x && Y == y))
            continue;

          grid[y][x].neigh[grid[y][x].n_neigh++] = & grid[Y][X];

        }
      }

    }
  }

}

void read_grid(tile (* grid)[GRID_SIZE], FILE * in_file) {

  char line[GRID_SIZE + 2];

  for(int y=0; y<GRID_SIZE; ++y) {

    fgets(line, sizeof(line), in_file);

    for(int x=0; x<GRID_SIZE; ++x)
      update_tile_next(& grid[y][x], line[x]);

  }

  promote_next_to_current(grid);

}

int score_grid(tile (* grid)[GRID_SIZE]) {
  
  int n_tree = 0;
  int n_lumb = 0;

  for(int y=0; y<GRID_SIZE; ++y)
    for(int x=0; x<GRID_SIZE; ++x)
      if(grid[y][x].current.value == '|')
        n_tree++;
      else if(grid[y][x].current.value == '#')
        n_lumb++;

  return n_tree * n_lumb;

}

void save_to_history(int i_step, tile (* grid)[GRID_SIZE], char history[][GRID_SIZE][GRID_SIZE]) {

  for(int y=0; y<GRID_SIZE; ++y)
    for(int x=0; x<GRID_SIZE; ++x)
      history[i_step][y][x] = grid[y][x].current.value;

}

int search_history(int i_step, char history[][GRID_SIZE][GRID_SIZE]) {
  
  for(int i=i_step - 1; i>=0 && i_step - i < MAX_LOOKBACK; --i) {

    for(int y=0; y<GRID_SIZE; ++y)
      for(int x=0; x<GRID_SIZE; ++x)
        if(history[i_step][y][x] != history[i][y][x])
          goto next;

    return i;

    next:;

  }

  return -1;

}

int main() {

  tile grid[GRID_SIZE][GRID_SIZE];
  char history[MAX_STEPS][GRID_SIZE][GRID_SIZE];

  init_grid(grid);

  FILE * in_file = fopen("input.txt", "r");

  read_grid(grid, in_file);

  fclose(in_file);

  int offset, period;

  for(int i=0; i<MAX_STEPS; ++i) {

    step(grid);

    save_to_history(i, grid, history);

    offset = search_history(i, history);

    if(offset > 0) {
      
      period = i - offset;

      break;
      
    }

  }

  int add_steps = (N_STEPS - offset) % period - 1;

  for(int i=0; i<add_steps; ++i)
    step(grid);

  printf("%i\n", score_grid(grid));

}
