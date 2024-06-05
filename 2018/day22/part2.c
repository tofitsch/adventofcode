#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 64
#define MOD 20183
#define FAC_X 48271
#define FAC_Y 16807
#define INF 1e5

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

      free(node->value);

      free(node);

      node = next;

    }

  }

  free(m);

}

char get_tile(node * n) {

  char tile = n->erosion_lvl % 3;

  return tile;

}

bool possible(node * a, int target_x, int target_y) {
  
  char tile = get_tile(a);

  if(tile == ROCKY && a->tool == NEITHER)
    return false;

  if(tile == WET && a->tool == TORCH)
    return false;

  if(tile == NARROW && a->tool == GEAR)
    return false;

  return true;

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

  char tile = get_tile(n);

  for(int i=0; i<3; i++) {
    
    if(i == n->tool || map_contains(m, n->x, n->y, i))
      continue;

    new_node = malloc(sizeof(node));

    init_node(new_node);

    new_node->x = n->x;
    new_node->y = n->y;

    new_node->tool = i;

    new_node->erosion_lvl = n->erosion_lvl;

    if(possible(new_node, target_x, target_y) && possible(n, target_x, target_y)) {

      n->edge[4 + i] = new_node;
      new_node->edge[4 + n->tool] = n;

    }
    
    map_update(m, n->x, n->y, i, new_node);

  }

}

node * add_node(node * n, char dir, int tool, int depth, int target_x, int target_y, map * m) { //dir = 0:above, 1:right, ...

  if(n != NULL && ((n->x == 0 && dir == LEFT) || (n->y == 0 && dir == ABOVE)))
    return NULL;
   
  if(n == NULL) {
    
    node * new_node = malloc(sizeof(node));

    init_node(new_node);

    new_node->x = 0;
    new_node->y = 0;

    new_node->tool = tool;

    new_node->erosion_lvl = depth % MOD;

    map_update(m, 0, 0, tool, new_node);
    
    add_tool_change_nodes(new_node, target_x, target_y, m);

    return new_node;

  }

  int x = n->x;
  int y = n->y;

  switch(dir) {

    case ABOVE:
      y--;
      break;

    case RIGHT:
      x++;
      break;

    case BELOW:
      y++;
      break;

    case LEFT:
      x--;
      break;

  };

  node * new_node = NULL;

  if(map_contains(m, x, y, n->tool)) {

    new_node = map_get_value(m, x, y, n->tool);
    goto end;

  }
  else
    new_node = malloc(sizeof(node));

  init_node(new_node);

  new_node->x = x;
  new_node->y = y;

  new_node->tool = n->tool;

  if(y == 0)
    new_node->erosion_lvl = (x * FAC_Y + depth) % MOD;
  else if(x == 0)
    new_node->erosion_lvl = (y * FAC_X + depth) % MOD;
  else {
   
    node * node_left = map_get_value(m, x - 1, y, n->tool);
    node * node_above = map_get_value(m, x, y - 1, n->tool);

    if(node_left == NULL)
      node_left = add_node(new_node, LEFT, new_node->tool, depth, target_x, target_y, m);

    if(node_above == NULL)
      node_above = add_node(new_node, ABOVE, new_node->tool, depth, target_x, target_y, m);

    new_node->erosion_lvl = (node_left->erosion_lvl * node_above->erosion_lvl + depth) % MOD;

  }

  if(new_node->x == target_x && new_node->y == target_y)
    new_node->erosion_lvl = depth % MOD;

  end:;

  if(possible(new_node, target_x, target_y) && possible(n, target_x, target_y)) {

    n->edge[dir] = new_node;
    new_node->edge[(dir + 2) % 4] = n;

  }

  map_update(m, new_node->x, new_node->y, new_node->tool, new_node);
  
  add_tool_change_nodes(new_node, target_x, target_y, m);

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

int dijkstra(node * start_node, int target_x, int target_y, int depth, map * m) {

  start_node->distance = 0;

  node * q = start_node;

  char c[4] = {'.', '=', '|', 'T'}; //X

  while(q != NULL){

    q->visited = true;
    
    if(q->x == target_x && q->y == target_y && q->tool == TORCH)
      return q->distance;
      
    for(int i=0; i<7; ++i) {
    
      if(q->edge[i] == NULL) {
        
        add_node(q, i, q->tool, depth, target_x, target_y, m);

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
  
  FILE * in_file = fopen("input.txt", "r");

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

  node * start_node = add_node(NULL, 0, TORCH, depth, target_x, target_y, m);

  printf("%i\n", dijkstra(start_node, target_x, target_y, depth, m));

  map_free(m);

}
