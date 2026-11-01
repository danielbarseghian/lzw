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

  initializeList(dictionnary);

  FILE *fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  int sbuff = 0, ebuff = 0;

  const int MAXLEN = 1024;
  char buff[MAXLEN];
  char *final = NULL;

  while(fgets(buff, MAXLEN, fptr) != NULL)
  {
    printf("buff: %s\n", buff);
    int buffSize = strlen(buff);

    // While buff didnt reach buffSize
    while (ebuff != buffSize)
    {
     // buff + 1 everytime there is something new
     sbuff = buildCode(dictionnary, buff, sbuff, ebuff, buffSize, &final);
     ebuff = sbuff;
    }
  }
  printf("return\n");
}

// return ebuff value so we can track where it is ending
int buildCode(DictEntry *dict, char *buff, int sbuff, int ebuff, int buffSize, char **final) 
{
  // make the string
  int SIZE = ebuff - sbuff + 1;
  
  // its one character
  if (SIZE == 0)
    SIZE = 1;
 
  // This is for example "ABC"
  char *str = malloc(sizeof(char) * SIZE + 1);
  
  for (int i = 0; i < SIZE; i++)  
    str[i] = buff[sbuff + i];

  str[SIZE] = '\0';

  printf("%s\n", str);

  bool found = false;

  for (int i = 0; i < dictLen; i++)
  {
    if (strcmp(str, dict[i].sequence) == 0)
    {
      if (ebuff == buffSize)
      {
        int oldSize = strlen(*final);
        int n = snprintf(NULL, 0, "%d", dict[i].code); // number of digits in the code

        // use the current code and malloc or realloc size for final
        allocFinal(final, n + 1);

        snprintf(*final + oldSize,n + 1, "%d", dict[i].code);
        printf("%s\n", *final);
      }

      found = true;
      ebuff++;

      buildCode(dict, buff, sbuff, ebuff, buffSize, final);
    }
  }

  if (!found) 
  {
    printf("creating new for %s with code %i\n", str, dictLen + 1);
    // We need to create a code
    dictLen++;
    dict[dictLen].sequence = malloc(strlen(str) + 1);

    strcpy(dict[dictLen].sequence, str);
    dict[dictLen].code = dictLen;

    int oldSize = 1;

    // malloc for final
    if (final != NULL && *final != NULL)
      oldSize = strlen(*final);

    printf("size %i\n", oldSize);

    int n = snprintf(NULL, 0, "%d", dict[dictLen].code); // number of digits in the code

    // for the \0
    n++;
    printf(" n%i\n", n);

    printf("so its %i\n", oldSize + n);
    // use the current code and malloc or realloc size for final
    allocFinal(&(*final), oldSize + n);
     
    printf("code: %i\n", dict[dictLen].code);
    snprintf(*final + oldSize, n, "%d", dict[dictLen].code);
    printf("finished\n");
    printf("string %s\n", *final);
  }

  free(str);

  printf("out\n");

  return ebuff;
}

// will return 1 or 0 depending on success or not
int buildCodes(char *buff, int sbuff, ebuff, char **final)
{
   // calculate the size of the buff 
  int size = ebuff - sbuff;

  if (size == 0)
    size = 1;

  // allocate the memory
  char *s = malloc(sizeof(char) * size + 1);

  // put the value between sbuff and ebuff in s 
  for (int i = sbuff, j = 0; i < ebuff; i++, i++) 
    s[j] = buff[i];

  // find the code
  for (int i = 0; i < dictLen; i++)
  {
    
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

void initializeList(DictEntry dict[])
{
  // store each 256 values of one byte in the dictionnary
  for (int i = 0; i < INIT_SIZE; i++)
  {
    dict[i].sequence = malloc(sizeof dict[i].sequence + 1);
    if (dict[i].sequence == NULL)
    {
      printf("malloc failed\n");
      return;
    }

    dict[i].sequence[0] = (char) i;
    dict[i].sequence[1] = '\0';
    dict[i].code = i;
  }
}

