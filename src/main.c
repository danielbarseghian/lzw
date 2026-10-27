#include "main.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
  initialize_list(&dictionary);
  FILE *fptr;

  fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }  
}

void initialize_list(DictEntry *dict)
{
  // store each 256 values of one byte in the dictionnary
  for (int i = 0; i < INIT_SIZE; i++)
  {
    dict[i].sequence = (unsigned char) i;
    dict[i].code = i;
  }
}

