#include <stdio.h>
#include <stdlib.h>

void main()
{
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  char reader = 'a';

  printf("The input is:\n\n");

  while (!feof(input))
  {
    fscanf(input, "%c", &reader);

    printf("%c", reader);
  }

  printf("\n\nOutput:\n\n");
  
  char OP, L, M;
  
  
  fclose(input);
  fclose(output);
}
