#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct {
  char sequence;
  uint16_t code;
} DictEntry;

#define MAX_SIZE 4096

int buildCodes(char *buff, int sbuff, int *ebuff, char **currCode);
int allocFinal(char **final, int size);
void createNewCode(uint16_t s);
int read16(FILE *f, uint16_t *s);

#endif
