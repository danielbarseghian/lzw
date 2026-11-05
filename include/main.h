#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#ifndef MAIN_H
#define MAIN_H

typedef struct {
  uint8_t sequence;
  uint16_t code;
} dictentry;

#define MAX_SIZE 4096
#define INIT_SIZE 256

int buildCodes(uint16_t sequence, char **currCode);
int allocFinal(char **final, int size);
void createNewCode(uint16_t s);
int read16(FILE *f, uint16_t *s);
int count01(int x);
void initializeDict();

#endif
