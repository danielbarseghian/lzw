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
    printf("Coudnt open %s, please make sure that the name is correct\n",
           argv[1]);
    return 1;
  }

  FILE *fwrt = fopen(argv[2], "wb");
  if (fwrt == NULL) {
    printf("cant open file %s to write\n", argv[2]);
    return 1;
  }

  // geeksforgeeks is one of the best websites i used so far
  unsigned char byte;
  unsigned char firstBit;

  bool first = true;

  while (fread(&byte, 1, 1, fptr)) {
    
    int currBit = 1;
  
    if (first) {
      firstBit = byte & 1;

      first = false;
    }

    // and the byte after 
    unsigned char nextBit = byte & currBit + 1;

    // this is the code we are going to create
    unsigned char nextCode = 0;

    uint16_t code = 0x0;
    bool found = false;

    for (int i = 0; i < dictLen; i++)
    {
      nextCode = firstBit | (nextBit << 1);

      printf("Comparint %uc and %uc \n", dictionnary[i].sequence, nextBit);
      if (nextCode == dictionnary[i].sequence)
      {
        found = true;

        p = nextCode; 

        code = dictionnary[i].code; 
      }
    }

    if (found)
      printf("code for %uc: %" PRIu16 ";\n", r, code);
    
    createNewCode(nextCode);

    p = c;
  }

  fclose(fptr);
  fclose(fwrt);

  printf("\n");
  return 0;
}

int createNewCode(unsigned char sequence)
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

