#include <stdio.h>
#include <stdlib.h>

void main()
{
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  int reader = 0;
  char OP, L, M;
  char dlim[] = " ";
  int instruction[100][3];

  printf("The input is:\n\n");
  int counter = 0;

  while (!feof(input))
  {
    // This loop the entire line and increases the counter afterwards
    for (int i = 0; i < 3; i++)
    {
      fscanf(input, "%d", &instruction[counter][i]);
    }

    printf("%d %d %d\n", instruction[counter][0], instruction[counter][1], instruction[counter][2]);

    counter++;
  }

  printf("\n\nOutput:\n\n");

  for (int i = 0; i < counter; i++)
  {
    switch(instruction[i][0])
    {
      case 1:
        printf("LIT ");
        break;
      case 2:
        printf("OPR ");
        break;
      case 3:
        printf("LOD ");
        break;
      case 4:
        printf("STO ");
        break;
      case 5:
        printf("CAL ");
        break;
      case 6:
        printf("INC ");
        break;
      case 7:
        printf("JMP ");
        break;
      case 8:
        printf("JPC ");
        break;
      case 9:
        printf("SYS ");
        break;
      default:
        break;
    }

    printf("%d %d\n", instruction[i][1], instruction[i][2]);
  }


  fclose(input);
  fclose(output);
}
