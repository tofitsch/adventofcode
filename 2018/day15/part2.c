#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_X 64
#define MAX_Y 64
#define INF 1000
#define HEALTH 200
#define ATTACK_POWER_G 3
#define ATTACK_POWER_E_START 4

typedef struct graph_node graph_node;

struct graph_node{

  char x, y, type, n_neighbours;

  int health, distance;

  bool visited;

  graph_node * neighbours[4];

};

void make_graph(char * in_file_name, graph_node (* grid)[MAX_X], graph_node * graph[], graph_node * units[], int * n_nodes, int * n_units, int * n_e, int * n_g){
  
  FILE * in_file = fopen(in_file_name, "r");

  char line[MAX_X];

  int n_x, n_y = 0;

  * n_nodes = 0;
  * n_units = 0;
  * n_e = 0;
  * n_g = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    n_x = 0;

    while(line[n_x] != '\n'){
      
      graph_node * node = & grid[n_y][n_x];
      
      node->x = n_x;
      node->y = n_y;

      node->n_neighbours = 0;

      node->type = line[n_x];

      if(node->type == 'E' || node->type == 'G'){

        node->health = HEALTH;

        units[(* n_units)++] = node;

      }

      if(node->type != '#')
        graph[(* n_nodes)++] = node;

      if(node->type == 'E')
        (* n_e)++;

      if(node->type == 'G')
        (* n_g)++;

      n_x++;

    }
    
    n_y++;

  }

  fclose(in_file);

  for(int i=0; i<* n_nodes; i++){

    graph_node * node = graph[i];

    if(node->x > 0 && grid[node->y][node->x - 1].type != '#')
      node->neighbours[(node->n_neighbours)++] = & grid[node->y][node->x - 1];

    if(node->y > 0 && grid[node->y - 1][node->x].type != '#')
      node->neighbours[(node->n_neighbours)++] = & grid[node->y - 1][node->x];

    if(node->x < n_x - 1 && grid[node->y][node->x + 1].type != '#')
      node->neighbours[(node->n_neighbours)++] = & grid[node->y][node->x + 1];

    if(node->y < n_y - 1 && grid[node->y + 1][node->x].type != '#')
      node->neighbours[(node->n_neighbours)++] = & grid[node->y + 1][node->x];

  }

}

int from_top_left(const void * a, const void * b) {

  const graph_node ** node_a = (const graph_node **) a;
  const graph_node ** node_b = (const graph_node **) b;

  if((* node_a)->y < (* node_b)->y)
    return -1;

  if((* node_a)->y > (* node_b)->y)
    return 1;

  if((* node_a)->x < (* node_b)->x)
    return -1;

  if((* node_a)->x > (* node_b)->x)
    return 1;

  return 0;

}

int distance_decreasing(const void * a, const void * b) {

  const graph_node ** node_a = (const graph_node **) a;
  const graph_node ** node_b = (const graph_node **) b;

  return (* node_a)->distance < (* node_b)->distance;

}

int distance_increasing(const void * a, const void * b) {

  const graph_node ** node_a = (const graph_node **) a;
  const graph_node ** node_b = (const graph_node **) b;

  return (* node_a)->distance > (* node_b)->distance;

}

void dijkstra(graph_node * queue[], int n_queue, graph_node * start){

  for(int i=0; i<n_queue; i++){
    
    queue[i]->distance = INF;
    queue[i]->visited = false;

  }

  start->distance = 0;

  while(n_queue > 0){

    qsort(queue, n_queue, sizeof(graph_node *), distance_decreasing);

    graph_node * node = queue[n_queue - 1];

    node->visited = true;

    n_queue--;

    int ctr = 0;

    for(int i=0; i<node->n_neighbours; i++){
      if(! node->neighbours[i]->visited){

        int distance_update = node->distance + 1;

        if(distance_update < node->neighbours[i]->distance)
          node->neighbours[i]->distance = distance_update;

      }
    }

  }

}

graph_node * get_target(graph_node * unit){

  int min_health = INF;
  
  graph_node * enemy_neighbors[4];

  int n_enemy_neighbors = 0;

  for(int i=0; i<unit->n_neighbours; i++){
    if((unit->type == 'E' && unit->neighbours[i]->type == 'G') ||
       (unit->type == 'G' && unit->neighbours[i]->type == 'E')){
        
        enemy_neighbors[n_enemy_neighbors++] = unit->neighbours[i];

        if(unit->neighbours[i]->health < min_health)
          min_health = unit->neighbours[i]->health;

    }
  }

  qsort(enemy_neighbors, n_enemy_neighbors, sizeof(graph_node *), from_top_left);

  for(int i=0; i<n_enemy_neighbors; i++)
    if(enemy_neighbors[i]->health == min_health)
      return enemy_neighbors[i];

  return NULL;

}

void move(graph_node * units[], int n_units, graph_node * graph[], int n_nodes, int id){

  graph_node * adjacents[MAX_Y * MAX_X];

  int n_adjacents = 0;

  for(int j=0; j<n_units; j++){
    
    if(units[id]->type == units[j]->type)
      continue;

    for(int k=0; k<units[j]->n_neighbours; k++)
      if(units[j]->neighbours[k]->type == '.')
        adjacents[n_adjacents++] = units[j]->neighbours[k];

  }

  graph_node * queue[MAX_Y * MAX_X];

  int n_queue = 0;

  for(int j=0; j<n_nodes; j++){
    
    if(graph[j]->type != '.')
      continue;

    queue[n_queue++] = graph[j];

  }

  for(int j=0; j<n_units; j++)
    units[j]->distance = INF;

  queue[n_queue++] = units[id];

  graph_node * queue_cpy[MAX_Y * MAX_X];

  memcpy(queue_cpy, queue, sizeof(queue));

  dijkstra(queue, n_queue, units[id]);

  int min_dist = INF;

  for(int j=0; j<n_adjacents; j++)
    if(adjacents[j]->distance < min_dist)
      min_dist = adjacents[j]->distance;

  if(min_dist != INF){

    graph_node * clostest_adjacents[MAX_Y * MAX_X];

    int n_clostest_adjacents = 0;

    for(int j=0; j<n_adjacents; j++)
      if(adjacents[j]->distance == min_dist)
        clostest_adjacents[n_clostest_adjacents++] = adjacents[j];

    qsort(clostest_adjacents, n_clostest_adjacents, sizeof(graph_node *), from_top_left);

    dijkstra(queue_cpy, n_queue, clostest_adjacents[0]);

    for(int j=0; j<n_units; j++)
      units[j]->distance = INF;

    qsort(units[id]->neighbours, units[id]->n_neighbours, sizeof(graph_node *), distance_increasing);

    int n_min_dist_neighbours = 1;

    for(int j=1; j<units[id]->n_neighbours; j++)
      if(units[id]->neighbours[j]->distance == units[id]->neighbours[0]->distance)
        n_min_dist_neighbours++;
      else
        break;

    qsort(units[id]->neighbours, n_min_dist_neighbours, sizeof(graph_node *), from_top_left);

    units[id]->neighbours[0]->health = units[id]->health;
    units[id]->neighbours[0]->type = units[id]->type;
     
    units[id]->health = 0;
    units[id]->type = '.';

    units[id] = units[id]->neighbours[0];

  }

}

void attack(graph_node * units[], int * n_units, int * id, graph_node * target, int * n_e, int * n_g, int attack_power_e){

  if(units[* id]->type == 'E')
    target->health -= attack_power_e;
  else
    target->health -= ATTACK_POWER_G;

  if(target->health >= 0)
    return;

  if(target->type == 'E')
    (* n_e)--;
  else if(target->type == 'G')
    (* n_g)--;
  
  target->type = '.';

  int id_in_units, id_in_graph;

  for(int i=0; i<* n_units; i++){
    if(units[i] == target){

      id_in_units = i;
      break;

    }
  }

  for(int i=id_in_units; i<* n_units; i++)
    units[i] = units[i + 1];

  (* n_units)--;

  if(id_in_units < * id)
    (* id)--;

}

int main(){

  graph_node grid[MAX_Y][MAX_X];
  
  graph_node * graph[MAX_Y * MAX_X];

  graph_node * units[MAX_Y * MAX_X];

  int n_nodes, n_units, n_e, n_g, n_rounds;

  int attack_power_e = ATTACK_POWER_E_START;

  while(true){

    make_graph("input.txt", grid, graph, units, & n_nodes, & n_units, & n_e, & n_g);

    int n_e_initial = n_e;

    n_rounds = 0;

    while(n_e == n_e_initial && n_g > 0){

      qsort(units, n_units, sizeof(graph_node *), from_top_left);

      for(int id=0; id<n_units; id++){

        graph_node * target = get_target(units[id]);

        if(target == NULL)
          move(units, n_units, graph, n_nodes, id);

        target = get_target(units[id]);

        if(target != NULL)
          attack(units, & n_units, & id, target, & n_e, & n_g, attack_power_e);

        if(n_e != n_e_initial)
          goto next;

        if(n_g == 0)
          goto end;

      }

      n_rounds++;

    }

    next:;

    attack_power_e++;

  }

  end:;

  int sum_health = 0;

  for(int i=0; i<n_units; i++)
    sum_health += units[i]->health;

  printf("%i\n", n_rounds * sum_health);

}
