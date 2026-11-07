#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct {
  unsigned char sequence;
  uint16_t code;
} DictEntry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

int buildCodes(unsigned char byte, FILE *fwrt);
int writeFile(uint16_t code, FILE *fwrt);
int createNewCode(unsigned char sequence);
int read16(FILE *f, uint16_t *s);
void initializeDict();

#endif
