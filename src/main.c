#include "main.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

DictEntry dictionnary[MAX_SIZE];
int dictLen = 256;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("please use --help\n");
    return 1;
  }

  initializeList();

  FILE *fptr = fopen(argv[1], "r");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  int sbuff = 0, ebuff = 1;
  const int MAXLEN = 1024;
  char buff[MAXLEN];
  char *currCode = NULL;

  while(fgets(buff, MAXLEN, fptr) != NULL)
  {
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

int buildCodes(char *buff, int sbuff, int *ebuff, char **currCode)
{
  int size = *ebuff - sbuff;
  uint8_t *s = 0x0; 

  for (int i = sbuff, j = 0; i < *ebuff; i++, j++)
    s[j] = buff[i];
  s[size] = '\0';

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

  if (!found)
  {
    printf("%s, ", *currCode);
    createNewCode(s);
    free(s);
    return 0;
  }

  free(s);
  return 1;
}

void createNewCode(char *s)
{
  if (dictLen >= MAX_SIZE)
    return;

  dictionnary[dictLen].sequence = malloc(strlen(s) + 1);
  if (dictionnary[dictLen].sequence == NULL)
    return;

  strcpy(dictionnary[dictLen].sequence, s);
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

void initializeList()
{
  for (int i = 0; i < INIT_SIZE; i++)
  {
    dictionnary[i].sequence = 0x0; 

    dictionnary[i].sequence = (char) i;
    dictionnary[i].code = i;
  }
}
