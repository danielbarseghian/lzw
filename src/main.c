#include "main.h"
#include "stdio.h"

int main(int argc, char *argv[])
{
  // store each 256 values of one byte in the dictionnary
  for (int i = 0; i < 256; i++) 
    dictionnary[i] = (unsigned char) i;

  FILE *fptr;

  fptr = fopen(argv[1], "rb");
  if (fptr == NULL)
  {
    printf("Coudnt open %s, please make sure that the name is correct\n", argv[1]);
    return 1;
  }
  

}

