#include "main.h"
#include "stdio.h"
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

DictEntry dictionnary[MAX_SIZE];
int dictLen = 255;

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("please use --help\n");
    return 1;
  }

  initializeList();

  FILE *fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  int sbuff = 0, ebuff = 0;

  const int MAXLEN = 1024;
  char buff[MAXLEN];
  char *currCode = NULL;

  while(fgets(buff, MAXLEN, fptr) != NULL)
  {
    printf("buff: %s\n", buff);
    int buffSize = strlen(buff);

    // While buff didnt reach buffSize
    while (ebuff != buffSize)
    {
     // buff + 1 everytime there is something new
     sbuff = buildCodes(buff, sbuff, ebuff, &currCode);
     ebuff = sbuff;
    }
  }
  printf("return\n");
}

// will return 1 or 0 depending on succed or not
int buildCodes(char *buff, int sbuff, int ebuff, char **currCode)
{
   // calculate the size of the buff 
  int size = ebuff - sbuff;

  // its only one character
  if (size == 0)
    size = 1;

  // allocate the memory
  char *s = malloc(sizeof(char) * size + 1);

  // put the value between sbuff and ebuff in s 
  for (int i = sbuff, j = 0; i < ebuff; i++, i++) 
    s[j] = buff[i];

  bool found = false;

  // find the code
  for (int i = 0; i < dictLen; i++)
  {
    if (strcmp(s, dictionnary[i].sequence) == 0)
    {
      found = true;

      // get the number of digits in the code
      int n = snprintf(NULL, 0, "%d", dictionnary[dictLen].code);

      // malloc the number of digits + 1 (for \0)
      *currCode = malloc(sizeof(char) * n + 1);

      // copy the code
      snprintf(*currCode,n , "%d", dictionnary[i].code);

      // add the \0
      *currCode[n + 1] = '\0';

      // try to find a new one
      buildCodes(buff, sbuff, ebuff + 1, currCode);
    }
  }

  if (!found)
  {
    // use currCode
    printf("code: %s\n", *currCode);
    return 0;
  }

  return 1;
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
  // store each 256 values of one byte in the dictionnary
  for (int i = 0; i < INIT_SIZE; i++)
  {
    dictionnary[i].sequence = malloc(sizeof dictionnary[i].sequence + 1);
    if (dictionnary[i].sequence == NULL)
    {
      printf("malloc failed\n");
      return;
    }

    dictionnary[i].sequence[0] = (char) i;
    dictionnary[i].sequence[1] = '\0';
    dictionnary[i].code = i;
  }
}

