#include "main.h"
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

DictEntry dictionnary[MAX_SIZE];
int dictLen = 0;

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("please use --help\n");
    return 1;
  }

  // initialize the dict with the first 256 character
  initializeDict();

  FILE *fptr = fopen(argv[1], "rb");
  if (fptr == NULL) {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  FILE *fwrt = fopen(argv[2], "wb");
  if (fwrt == NULL) {
    printf("cant open file %s to write\n", argv[2]);
    return 1;
  }
 
  // geeksforgeeks is my goat 
  uint16_t p = fread(&p, 1, 1, fptr);
  uint8_t c;
  uint16_t sequence = 0x0;
  int currCode;

  while (fread(&c, 1, 1, fptr)) {
    // if p + c is in the table
    sequence = (uint16_t)(p << 8 | c);

    bool found = false;

    // if its in zha table
    for (int i = 0; i < dictLen; i++) { 
      // compare each bits
      for (int j = 15; j >= 0; j--) {
        // idk if i need to do this but it makes me look way smarter so im going to keep this
        if (((sequence >> j) & 1u) == ((dictionnary[i].sequence >> j) & 1u)) {
          p = sequence;
          found = true;
          currCode = dictionnary[i].code;
        }
      }
    }

    if (!found) {
      for (int i = 15; i >= 0; i--) {
        printf("la la %i; ", currCode);
      }
      printf("\n");
    }

    createNewCode(sequence);

    p = c;
  }
     
  for (int i = 15; i >= 0; i--) { 
    printf("po po %i; ", currCode);
  }
  printf("\n");

  fclose(fptr);
  fclose(fwrt);

  return 0;
}

int createNewCode(uint16_t sequence)
{
  dictionnary[dictLen].sequence = sequence;
  dictionnary[dictLen].code = dictLen;
  dictLen++;

  return 0;     
}

int writeFile(uint16_t code, FILE *fwrt)
{
  printf("write %" PRIu16 "\n", code); 

  fwrite(&code, sizeof(uint16_t), 1, fwrt);

  return 0; 
}

void initializeDict() {
  // initialize the sequences and codes
  for (int i = 0; i < MAX_SIZE; i++) {
    dictionnary[i].code = 0;
    dictionnary[i].sequence = 0x0;
  }

  while (dictLen < INIT_SIZE) {
    dictionnary[dictLen].sequence = (unsigned char)dictLen;
    dictionnary[dictLen].code = dictLen;
    dictLen++;
  }
}

