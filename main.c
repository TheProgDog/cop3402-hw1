#include <stdio.h>
#include <stdlib.h>

void main()
{
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  char reader = 'a';
  char OP, L, M;
  char dlim[] = " ";
  int instruction[100][3];

  printf("The input is:\n\n");
  int i = 0;
  while (!feof(input))
  {
    fscanf(input, "%c", &reader);

    printf("%c", reader);
    instruction[i][0] = atoi(strtok(reader, dlim));
    instruction[i][1] = atoi(strtok(reader, dlim));
    instruction[i][2] = atoi(strtok(reader, dlim));
    i++;
  }

  printf("\n\nOutput:\n\n");
  
  
  
  
  
  fclose(input);
  fclose(output);
}
