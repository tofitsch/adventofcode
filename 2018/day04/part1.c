#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../../clib/map.c"

#define MAX_ID 5000

int str_compare(const void *a, const void *b) {

  const char **str1 = (const char **) a;
  const char **str2 = (const char **) b;

  return strcmp(*str1, *str2);

}

int substr_to_int(char * str, int beg, int end){ //TODO: lib
  
  char buff[end - beg + 1];

  strncpy(buff, str + beg, end - beg);

  buff[end - beg] = '\0';

  return strtol(buff, NULL, 10);

}

void parse_line(char * line, int * id, int * min, int * n_guards, int guard_ids[], int guard_slept_total[], int (* guard_slept_at_min)[MAX_ID]){
  
  int next_min = substr_to_int(line, 15, 17);

  if(line[12] != '0')
    next_min -= 60;

  int b_pos = 19;

  switch(line[19]){
    
    case 'G':

      while(line[b_pos] != 'b')
        b_pos++;

      * id = substr_to_int(line, 26, b_pos);

      if(guard_slept_total[* id] == 0){

        guard_ids[* n_guards] = * id;

        (* n_guards)++;

      }
 
      break;

    case 'w':
      
      guard_slept_total[* id] += next_min - * min;

      for(int i= * min; i<next_min; i++)
        guard_slept_at_min[* id][i + 60]++;

      break;


  };

  * min = next_min;

}

int main(){

  FILE * in_file = fopen("input.txt", "r");

  char line[64];
  char * lines[1500];

  int line_ctr = 0;

  while(fgets(line, sizeof(line), in_file) != NULL){

    lines[line_ctr] = malloc(strlen(line) + 1);

    strcpy(lines[line_ctr], line);

    line_ctr++;

  }

  fclose(in_file);

  qsort(lines, line_ctr, sizeof(char *), str_compare);

  int id, min;

  int n_guards = 0;
  int guard_ids[MAX_ID];
  int guard_slept_total[MAX_ID];
  int guard_slept_at_min[120][MAX_ID];

  memset(guard_slept_total, 0, sizeof(guard_slept_total));
  memset(guard_slept_at_min, 0, sizeof(guard_slept_at_min));

  for(int i=0; i<line_ctr; i++)
    parse_line(lines[i], & id, & min, & n_guards, guard_ids, guard_slept_total, guard_slept_at_min);

  int id_max_total = guard_ids[0];

  for(int i=1; i<n_guards; i++)
    if(guard_slept_total[guard_ids[i]] > guard_slept_total[id_max_total])
      id_max_total = guard_ids[i];

  min = 0;
  
  for(int i=1; i<120; i++)
    if(guard_slept_at_min[id_max_total][i] > guard_slept_at_min[id_max_total][min])
      min = i;

  printf("%i\n", id_max_total * (min - 60));

}
