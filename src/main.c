#include "main.h"
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

DictEntry dictionnary[MAX_SIZE];
int dictLen = 256;

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

  char *entry = NULL, *final = NULL;

  const int MAXLEN = 1024;
  char buff[MAXLEN];

  while(fgets(buff, MAXLEN, fptr) != NULL)
  {
    // buff + 1 everytime there is something new  
  }

}

bool buildCode(DictEntry *dict, char *entry, char *final)
{
  for (int i = 0; i < dictLen; i++)
  {
    if (strcmp(entry, dict[i]) == 0)
    {

    }
  }
}

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

