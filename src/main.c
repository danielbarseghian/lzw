#include "main.h"
#include <string.h>
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

  read16(fptr, &s);

  int sbuff = 0, ebuff = 1;
  const int MAXLEN = 1024;
  char buff[MAXLEN];
  char *currCode = NULL;

  while(fgets(buff, MAXLEN, fptr) != NULL)
  {
    // printf("%s\n", buff);
    int buffSize = strlen(buff);

    while (sbuff < buffSize && ebuff <= buffSize)
    {
      int res = buildCodes(buff, sbuff, &ebuff, &currCode);
      
      // if we reach the end 
      if (res == 1 && ebuff == buffSize) 
          break; 
      

      sbuff = ebuff - 1; 
      ebuff = sbuff + 1;
    }
  }
  
  if (currCode != NULL) {
      free(currCode);
  }
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

  if (lower == EOF || upper == EOF)
    return 1;

  printf("read: %u\n", (upper<<8) | lower);

  return 1;
}
int buildCodes(char *buff, int sbuff, int *ebuff, char **currCode)
{
  int size = *ebuff - sbuff;
  uint16_t *s = 0x0; 

  bool found = false;

  for (int i = 0; i < dictLen; i++)
  {
    if (s == dictionnary[i].sequence)
    {
      found = true;
      
      int n = snprintf(NULL, 0, "%d", dictionnary[i].code);
     
      if (*currCode != NULL)
        free(*currCode);
      
      *currCode = malloc(sizeof(char) * n + 1);
      snprintf(*currCode, n + 1 , "%d", dictionnary[i].code);

      if (*ebuff < (int)strlen(buff)) {
          (*ebuff)++;
          int result = buildCodes(buff, sbuff, ebuff, currCode);
          free(s);
          return result;
      }
      break;
    }
  }

 // if (!found)
  //{
    // printf("%s, ", *currCode);
    // createNewCode(s);
  //  free(s);
  return 0;
 // }

  free(s);
  return 1;
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

