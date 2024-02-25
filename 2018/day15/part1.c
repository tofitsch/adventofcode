#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_X 64
#define MAX_Y 64
#define INF 1000

typedef struct graph_node graph_node;

struct graph_node{

  char x, y, type, health, n_neighbours;

  int distance;

  bool visited;

  graph_node * neighbours[4];

};

void make_graph(char * in_file_name, graph_node (* grid)[MAX_X], graph_node * graph[], graph_node * units[], int * n_nodes, int * n_units){
  
  FILE * in_file = fopen(in_file_name, "r");

  char line[MAX_X];

  int n_x, n_y = 0;

  * n_nodes = 0;
  * n_units = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){
    
    n_x = 0;

    while(line[n_x] != '\n'){
      
      graph_node * node = & grid[n_y][n_x];
      
      node->x = n_x;
      node->y = n_y;

      node->n_neighbours = 0;

      node->type = line[n_x];

      if(node->type == 'E' || node->type == 'G'){

        node->health = 200;

        units[(* n_units)++] = node;

      }

      if(node->type != '#')
        graph[(* n_nodes)++] = node;

      n_x++;

    }
    
    n_y++;

  }

  fclose(in_file);

  //XXX
//  for(int y=0; y<n_y; y++){
//
//    for(int x=0; x<n_x; x++)
//      printf("%c", grid[y][x].type);
//
//    printf("\n");
//
//  }

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

int main(){

  graph_node grid[MAX_Y][MAX_X];
  
  graph_node * graph[MAX_Y * MAX_X];

  graph_node * units[MAX_Y * MAX_X];

  int n_nodes;
  int n_units;

  make_graph("example.txt", grid, graph, units, & n_nodes, & n_units);

  qsort(units, n_units, sizeof(graph_node *), from_top_left);

  for(int i=0; i<n_units; i++){

    printf("from: %c %c\n", units[i]->x + '0', units[i]->y + '0');

    graph_node * target = get_target(units[i]);

    if(target == NULL){ //move

      graph_node * adjacents[MAX_Y * MAX_X];

      int n_adjacents = 0;

      for(int j=0; j<n_units; j++){
        
        if(units[i]->type == units[j]->type)
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

      queue[n_queue++] = units[i];

      graph_node * queue_cpy[MAX_Y * MAX_X];

      memcpy(queue_cpy, queue, sizeof(queue));

      dijkstra(queue, n_queue, units[i]);

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

        qsort(units[i]->neighbours, units[i]->n_neighbours, sizeof(graph_node *), distance_increasing);

        int n_min_dist_neighbours = 1;

        for(int j=1; j<units[i]->n_neighbours; j++)
          if(units[i]->neighbours[j]->distance == units[i]->neighbours[0]->distance)
            n_min_dist_neighbours++;
          else
            break;

        qsort(units[i]->neighbours, n_min_dist_neighbours, sizeof(graph_node *), from_top_left);

        units[i]->neighbours[0]->health = units[i]->health;
        units[i]->neighbours[0]->type = units[i]->type;

        units[i]->health = 0;
        units[i]->type = '.';

        units[i] = units[i]->neighbours[0];

      }

    }

    printf("to: %c %c\n", units[i]->x + '0', units[i]->y + '0');

    target = get_target(units[i]);

    if(target != NULL) //attack
      printf("target: %c %c\n\n", target->x + '0', target->y + '0');
    else
      printf("target: NULL\n\n");

  }

}
