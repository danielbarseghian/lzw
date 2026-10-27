#ifndef MAIN_H
#define MAIN_H
 
typedef struct {
  char *sequence;
  int code;
} DictEntry;

#define MAX_SIZE 4096

DictEntry dictionnary[MAX_SIZE];
int base_dict_size = 256;

#endif
