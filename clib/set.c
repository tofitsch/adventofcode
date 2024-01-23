struct set_node{
  
  int key;

  set_node * next;

};

struct set{
  
  static int const size = 2e5;
  
  set_node * hash_table[size];

};

set * set_create(){
  
  set * s = (set *) malloc(sizeof(set));

  for(int i=0; i<s->size; i++)
    s->hash_table[i] = NULL;

  return s;

}

int set_hash_func(set * s, int key){
 
  int hash = abs(key) % (s->size / 2);
  if(key < 0) hash += s->size / 2;

  return hash; 

}

bool set_contains(set * s, int key){
  
  int index = set_hash_func(s, key);

  set_node * node = s->hash_table[index];

  while(node != NULL){

    if(node->key == key)
      return true;

    node = node->next;

  }

  return false;

}

bool set_insert(set * s, int key){
  
  if(set_contains(s, key))
    return false;

  int index = set_hash_func(s, key);

  set_node * node = (set_node *) malloc(sizeof(set_node));

  node->key = key;

  node->next = s->hash_table[index];

  s->hash_table[index] = node;

  return true;

}

void set_free(set * s){

  for(int i=0; i<s->size; i++){

    set_node * node = s->hash_table[i];

    while(node != NULL){
      
      set_node * next = node->next;

      free(node);

      node = next;

    }

  }

  free(s);

}
