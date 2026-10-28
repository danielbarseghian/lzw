#ifndef MAIN_H
#define MAIN_H
#include <stdbool.h>

typedef struct {
  char *sequence;
  int code;
} DictEntry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

void initializeList(DictEntry dict[]);
bool isInList(DictEntry *dict, char *entry);

#endif
