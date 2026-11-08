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
 
  char sequence[17];
  int currCode = 0;
  bool found = false;

  // geeksforgeeks is my goat 
  unsigned char byte;

  while (fread(&byte, 1, 1, fptr)) {

    for (int i = 7; i >= 0 ; i--) {
      unsigned bit = (byte >> i) & 1u;

      found = false;
      
      sequence = (byte >> i) & 1u;

      for (int j = 0; j < dictLen; j++) {
        if (sequence == dictionnary[j].sequence) {
          currCode = dictionnary[j].code;
          found = true;
  
          // find a new code
          break;
        }
      }

      // There is already a code and it didn't find it this loop
      if ((currCode != 0) && (!found)) {
        // printf("%i; ", currCode);

        // create new code
        createNewCode(sequence);

        sequence = 0x0;
        currCode = 0;
      }

    }
  }

  fclose(fptr);
  fclose(fwrt);

  printf("\n");
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

