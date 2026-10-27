#ifndef MAIN_H
#define MAIN_H
 
typedef struct {
  char *sequence;
  int code;
} DictEntry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

void initialize_list(DictEntry dict[]);

#endif
