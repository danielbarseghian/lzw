#include "main.h"
#include "stdio.h"
#include <stdlib.h>

DictEntry dictionnary[MAX_SIZE];

int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    printf("please use --help\n");
    return 1;
  }

  initialize_list(dictionnary);

  FILE *fptr;

  fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }

  for (int i = 0; i < INIT_SIZE; i++)
  {
    printf("%s is %i\n", dictionnary[i].sequence, dictionnary[i].code);
  }
}

void initialize_list(DictEntry dict[])
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

