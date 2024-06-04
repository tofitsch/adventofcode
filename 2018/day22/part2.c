#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 64
#define MOD 20183
#define FAC_X 48271
#define FAC_Y 16807
#define INF 1e8

typedef struct node node;

typedef struct map_node map_node;
typedef struct map map;

const int map_size = 1e6;

enum Tool {
  NEITHER,
  GEAR,
  TORCH,
};

enum Tile {
  ROCKY,
  WET,
  NARROW,
  TARGET,
};

enum Direction {
  ABOVE,
  RIGHT,
  BELOW,
  LEFT,
};

struct node {
  
  int x, y, erosion_lvl, distance, tool;

  bool visited;

  node * next;

  int weight[7];

  node * edge[7];

};

struct map_node{
  
  int x, y, tool;

  node * value;

  map_node * next;

};

struct map{
  
  map_node ** hash_table;

};

map * map_create(){
  
  map * m = (map *) malloc(sizeof(map));

  m->hash_table = (map_node **)malloc(map_size * sizeof(map_node *));

  return m;

}

int map_hash_func(map * m, int x, int y, int tool){
 
  int hash = (tool + 1 + (x + 1) * 10 + (y + 1) * 10000) % map_size;

  return hash; 

}

bool map_contains(map * m, int x, int y, int tool){
  
  int index = map_hash_func(m, x, y, tool);

  map_node * node = m->hash_table[index];

  while(node != NULL){

    if(node->x == x && node->y == y && node->tool == tool)
      return true;

    node = node->next;

  }

  return false;

}

node * map_get_value(map * m, int x, int y, int tool){

  if(! map_contains(m, x, y, tool))
    return NULL;

  int index = map_hash_func(m, x, y, tool);

  map_node * node = m->hash_table[index];

  return node->value;

}

bool map_update(map * m, int x, int y, int tool, node * value){
  
  int index = map_hash_func(m, x, y, tool);

  if(map_contains(m, x, y, tool)){
    
    map_node * node = m->hash_table[index];

    node->value = value;

    return false;

  }

  map_node * node = (map_node *) malloc(sizeof(map_node));

  node->x = x;
  node->y = y;
  node->tool = tool;

  node->value = value;

  node->next = m->hash_table[index];

  m->hash_table[index] = node;

  return true;

}

void map_free(map * m){

  for(int i=0; i<map_size; i++){

    map_node * node = m->hash_table[i];

    while(node != NULL){
      
      map_node * next = node->next;

      free(node);

      node = next;

    }

  }

  free(m);

}

char get_tile(node * n, int target_x, int target_y) {

  char tile = n->erosion_lvl % 3;

  if(n->x == target_x, n->y == target_y)
    tile = TARGET;

  return tile;

}

void connect_nodes(node * a, node * b, int target_x, int target_y, int dir) {
  
  char tile_a = get_tile(a, target_x, target_y);
  char tile_b = get_tile(b, target_x, target_y);

  if(tile_b == ROCKY && a->tool == NEITHER)
    goto skip;

  if(tile_b == WET && a->tool == TORCH)
    goto skip;

  if(tile_b == NARROW && a->tool == GEAR)
    goto skip;

  a->edge[dir] = b;

  skip:;
    
  if(tile_a == ROCKY && b->tool == NEITHER)
    return;

  if(tile_a == WET && b->tool == TORCH)
    return;

  if(tile_a == NARROW && b->tool == GEAR)
    return;

  b->edge[(dir + 2) % 4] = a;

}

void init_node(node * n) {

  n->next = NULL;

  n->distance = INF;

  n->visited = false;

  for(int i=0; i<7; ++i) {
    
    n->edge[i] = NULL;
    n->weight[i] = (i > 3 ? 7 : 1);

  }

}

void add_tool_change_nodes(node * n, int target_x, int target_y, map * m) {
  
  node * new_node = NULL;

  char tile = get_tile(n, target_x, target_y);

  for(int i=0; i<3; i++) {
    
    if(i == n->tool || map_contains(m, n->x, n->y, i))
      continue;

    if(tile == ROCKY && i == NEITHER)
      continue;

    if(tile == WET && i == TORCH)
      continue;

    if(tile == NARROW && i == GEAR)
      continue;

    if(tile == TARGET && i != TORCH)
      continue;
  
    new_node = malloc(sizeof(node));

    init_node(new_node);

    new_node->x = n->x;
    new_node->y = n->y;

    new_node->tool = i;

    new_node->erosion_lvl = n->erosion_lvl;

    n->edge[4 + i] = new_node;
    new_node->edge[4 + n->tool] = n;
    
    map_update(m, n->x, n->y, i, new_node);

  }

}

node * add_node(node * n, char dir, int tool, int depth, int target_x, int target_y, map * m) { //dir = 0:above, 1:right, ...
  
  if(n != NULL && ((n->x == 0 && dir == LEFT) || (n->y == 0 && dir == ABOVE)))
    return NULL;
   
  node * new_node = malloc(sizeof(node));

  init_node(new_node);

  if(n == NULL) {
    
    new_node->x = 0;
    new_node->y = 0;

    new_node->tool = tool;

    new_node->erosion_lvl = depth % MOD;

    map_update(m, 0, 0, 0, new_node);
    
    add_tool_change_nodes(new_node, target_x, target_y, m);

    return new_node;

  }

  new_node->x = n->x;
  new_node->y = n->y;

  new_node->tool = n->tool;

  switch(dir) {

    case ABOVE:
      new_node->y--;
      break;

    case RIGHT:
      new_node->x++;
      break;

    case BELOW:
      new_node->y++;
      break;

    case LEFT:
      new_node->x--;
      break;

  };

  if(map_contains(m, new_node->x, new_node->y, new_node->tool)) {
    
    free(new_node); //TODO don't allocate in the first place

    return NULL;

  }

  map_update(m, new_node->x, new_node->y, new_node->tool, new_node);
  
  add_tool_change_nodes(new_node, target_x, target_y, m);

  if(new_node->y == 0)
    new_node->erosion_lvl = (new_node->x * FAC_Y + depth) % MOD;
  else if(new_node->x == 0)
    new_node->erosion_lvl = (new_node->y * FAC_X + depth) % MOD;
  else {
   
    node * node_left = map_get_value(m, new_node->x - 1, new_node->y, new_node->tool);
    node * node_above = map_get_value(m, new_node->x, new_node->y - 1, new_node->tool);

    if(node_left == NULL)
      node_left = add_node(new_node, LEFT, new_node->tool, depth, target_x, target_y, m);

    connect_nodes(node_left, new_node, target_x, target_y, RIGHT);

    if(node_above == NULL)
      node_above = add_node(new_node, ABOVE, new_node->tool, depth, target_x, target_y, m);

    connect_nodes(node_above, new_node, target_x, target_y, BELOW);

    new_node->erosion_lvl = (node_left->erosion_lvl * node_above->erosion_lvl + depth) % MOD;

  }

  connect_nodes(n, new_node, target_x, target_y, dir);

  return new_node;

}

void dequeue(node * q, node * n) {

  node * prev = NULL;
  
  while(q != n && q->next != NULL) {

    prev = q;
    q = q->next;

  }

  if(q == n)
    if(prev == NULL)
      q = q->next;
    else
      prev->next = q->next;

  n->next = NULL;

}

node * queue(node * q, node * n) {
  
  if(q->distance > n->distance) {
    
    n->next = q;

    return n;

  }
  
  node * Q = q;
  
  while(Q->distance < n->distance && Q->next != NULL)
    Q = Q->next;

  n->next = Q->next;
  Q->next = n;

  return q;

}

void free_queue(node * n) {
  
  do {

    node * n_done = n;
    n = n->next;

    free(n_done);

  } while(n != NULL);

}

int dijkstra(node * start_node, int target_x, int target_y, int depth, map * m) {

  start_node->distance = 0;

  node * q = start_node;

  queue(q, add_node(start_node, RIGHT, q->tool, depth, target_x, target_y, m));
  queue(q, add_node(start_node, BELOW, q->tool, depth, target_x, target_y, m));

  while(q != NULL){
    
    printf("%i %i %i %i\n", q->tool, q->x, q->y, q->distance);
    
    q->visited = true;

    if(q->x == target_x && q->y == target_y && q->tool == TORCH) {
      
      int d = q->distance;

      free_queue(start_node);

      return d;

    }

    for(int i=0; i<7; ++i) {
    
      if(q->edge[i] == NULL) {

        q->edge[i] = add_node(q, i, q->tool, depth, target_x, target_y, m);

        if(q->edge[i] == NULL)
          continue;

      }

      if(q->edge[i]->visited)
        continue;

      int d = q->distance + q->weight[i];

      if(d < q->edge[i]->distance) {
       
        dequeue(q, q->edge[i]);

        q->edge[i]->distance = d;

        q = queue(q, q->edge[i]);

      }

    }

    q = q->next;

  }

  return -1;

}

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

  map * m = map_create();

  node * start_node = add_node(NULL, 0, NEITHER, depth, target_x, target_y, m);

  printf("%i\n", dijkstra(start_node, target_x, target_y, depth, m));

  map_free(m);

}
