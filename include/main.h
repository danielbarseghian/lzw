#include <stdbool.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct {
  char *sequence;
  int code;
} DictEntry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

void initializeList(DictEntry dict[]);
void buildCode(DictEntry *dict, char *buff, int sbuff, int ebuff); 
#endif
