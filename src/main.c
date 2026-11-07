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

  FILE *fptr = fopen(argv[1], "rb");
  if (fptr == NULL) {
    printf("Coudnt open %s, please make sure that the name is correct\n",
           argv[1]);
    return 1;
  }

  FILE *fwrt = fopen(argv[2], "wb");
  if (fwrt == NULL) {
    printf("cant open file %s to write\n", argv[2]);
    return 1;
  }


  unsigned char byte;

  while (fread(&byte, 1, 1, fptr)) {
    buildCodes(byte, fwrt);
  }

  fclose(fptr);

  printf("\n");
  return 0;
}

// return 1 if written or 0 if not
int buildCodes(uint16_t sequence, FILE *fwrt)
{
  uint16_t currCode = 0x0, newSequence = 0x0; 
  
  for (int i = 15; i != 0; i--) {
    uint16_t bits = (sequence >> i) & 0x07u;
    newSequence = bits;

    for (int j = 0; j < dictLen; j++) {
      if (dictionnary[j].sequence == bits) {
        newSequence = 0x0;

        currCode = dictionnary[j].code;

        // try and find a new code
        break;
      }
    }

    // if they didnt find a new code write currCode and put this new code
    if (newSequence) {
      // write to file
      writeFile(currCode, fwrt); 
     
      // create new code
      createNewCode(newSequence);
    }
  }

  return 1;
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

void initializeList() {
  // initialize the sequences and codes
  for (int i = 0; i < MAX_SIZE; i++) {
    dictionnary[i].code = 0;
    dictionnary[i].sequence = 0x0;
  }

  while (dictLen < INIT_SIZE) {
    dictionnary[dictLen].sequence = (uint16_t)dictLen;
    dictionnary[dictLen].code = dictLen;
    dictLen++;
  }
}

