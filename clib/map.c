#include "map.h"

struct map_node{
  
  int key, value;

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

int map_hash_func(map * m, int key){
 
  int hash = abs(key) % (map_size / 2);
  if(key < 0) hash += map_size / 2;

  return hash; 

}

bool map_contains(map * m, int key){
  
  int index = map_hash_func(m, key);

  map_node * node = m->hash_table[index];

  while(node != NULL){

    if(node->key == key)
      return true;

    node = node->next;

  }

  return false;

}

int map_get_value(map * m, int key){

  if(! map_contains(m, key))
    return 0;

  int index = map_hash_func(m, key);

  map_node * node = m->hash_table[index];

  return node->value;

}

bool map_update(map * m, int key, int value){
  
  int index = map_hash_func(m, key);

  if(map_contains(m, key)){
    
    map_node * node = m->hash_table[index];

    node->value = value;

    return false;

  }

  map_node * node = (map_node *) malloc(sizeof(map_node));

  node->key = key;
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
