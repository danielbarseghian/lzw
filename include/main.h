#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef MAIN_H

#define MAIN_H
#define MAX_SIZE 4096
#define INIT_SIZE 256

typedef struct {
  unsigned char sequence;
  uint16_t code;
} DictEntry;

int buildCodes(unsigned char byte, FILE *fwrt);
int writeFile(uint16_t code, FILE *fwrt);
int createNewCode(unsigned char sequence);
int read16(FILE *f, uint16_t *s);
void initializeDict();

#endif
