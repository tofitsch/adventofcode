#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct ht_Node{
  
  int key;
  ht_Node * next;

};

struct ht_HashTable{
  
  static int const size = 10000;
  
  ht_Node * table[size];

};

ht_HashTable * ht_create(){
  
  ht_HashTable * ht = (ht_HashTable *) malloc(sizeof(ht_HashTable));

  for(int i=0; i<ht->size; i++)
    ht->table[i] = NULL;

  return ht;

}

int ht_hash_func(ht_HashTable * ht, int key){
 
  int hash = abs(key) % (ht->size / 2);
  if(key < 0) hash += ht->size / 2;

  return hash; 

}

bool ht_contains(ht_HashTable * ht, int key){
  
  int index = ht_hash_func(ht, key);

  ht_Node * node = ht->table[index];

  while(node != NULL){

    if(node->key == key)
      return true;

    node = node->next;

  }

  return false;

}

bool ht_insert(ht_HashTable * ht, int key){
  
  if(ht_contains(ht, key))
    return false;

  int index = ht_hash_func(ht, key);

  ht_Node * node = (ht_Node *) malloc(sizeof(ht_Node));

  node->key = key;
  node->next = ht->table[index];
  ht->table[index] = node;

  return true;

}

void ht_free(ht_HashTable * ht){

  for(int i=0; i<ht->size; i++){

    ht_Node * node = ht->table[i];

    while(node != NULL){
      
      ht_Node * next = node->next;

      free(node);

      node = next;

    }

  }

  free(ht);

}

int find_repeating_sum(FILE * in_file){

  char line[8];

  int sum = 0;

  ht_HashTable * ht = ht_create();

  while(true){

    while(fgets(line, sizeof(line), in_file) != NULL){

      sum += atoi(line);

      if(! ht_insert(ht, sum))

        return sum;
    }

    fseek(in_file, 0, SEEK_SET);

  }

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  printf("%i\n", find_repeating_sum(in_file));

  fclose(in_file);
  
}
