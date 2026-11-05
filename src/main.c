#include "main.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

DictEntry dictionnary[MAX_SIZE];
int dictLen = 0;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("please use --help\n");
    return 1;
  }

  FILE *fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  uint16_t s = 0x0;
  uint16_t currCode = 0x0;

  while(read16(fptr, &s) != 0)
  {
    buildCodes(s, currCode);    
  }

  printf("%u\n", s);
 
  fclose(fptr);

  printf("\n");
  return 0;
}

// returns 1 if it succeed or 0 if not
int read16(FILE *f, uint16_t *s)
{
  // we can read the file byte by byte (8 by 8) then assemble them together to make 16 bits
  int lower = fgetc(f);
  int upper = fgetc(f);

  if (lower == EOF)
    return 1;

  if (upper == EOF)
    upper = 0;

  *s = (upper<<8) | lower;

  return 0;
}

// return 1 if written or 0 if not
int buildCodes(uint16_t sequence, uint16_t currCode)
{
  for (int i = 15; i != 0; i--)
  {
    uint16_t bits = (sequence >> i) & 0x07u;

    for (int j = 0; j < dictLen; i++)
    {
      if (dictionnary[j].sequence == bits)
      {
        currCode = dictionnary[j].sequence;
        
        // try and find a new code
        break;
      }
    }
  }

  printf("%u\n", currCode);
}

void initializeList()
{
  // initialize the sequences and codes
  for (int i = 0; i < MAX_SIZE; i++)
  {
    dictionnary[i].code = 0;
    dictionnary[i].sequence = 0x0;
  }

  while (dictLen < INIT_SIZE)
  {
    dictionnary[dictLen].sequence = (uint16_t)dictLen;
    dictionnary[dictLen].code = dictLen;
    dictLen++;
  }
}

void createNewCode(uint16_t s)
{
  if (dictLen >= MAX_SIZE)
    return;

  dictionnary[dictLen].sequence = s; 
  dictionnary[dictLen].code = dictLen;
  
  dictLen++;
}

int allocFinal(char **final, int size)
{
  char *tmp = realloc(*final, size);
  if (tmp == NULL) 
    return 0;

  *final = tmp;
  return 1;
}

