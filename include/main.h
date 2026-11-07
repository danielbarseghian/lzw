#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct {
  uint16_t sequence;
  uint16_t code;
} DictEntry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

int buildCodes(uint16_t sequence, FILE *fwrt);
int writeFile(uint16_t code, FILE *fwrt);
int createNewCode(uint16_t sequence);
int read16(FILE *f, uint16_t *s);
void initializeDict();

#endif
