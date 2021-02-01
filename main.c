#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

int stack[MAX_STACK_HEIGHT];
int counter = 0, BP = 0, SP = -1;

bool push(int);
int pop();
int base(int[], int, int);

void main(int argc, char *argv[])
{
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen("output.txt", "w");

  int reader = 0;
  char OP, L, M;
  char dlim[] = " ";
  int instruction[MAX_CODE_LENGTH][3];

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

  printf("\t\t\tPC\tBP\tSP\tstack\n");

  for (int PC = 0; PC < counter; PC++)
  {
    printf("%d\t", PC);

    char *opr;

    int L = instruction[PC][1], M = instruction[PC][2];

    switch(instruction[PC][0])
    {
      case 1:
        printf("LIT %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        SP ++;
        push(M);

        break;
      case 2:

        // Do some stuff here with operations based on M:
        // 0 -> RET
        // 1 -> NEG
        // 2 -> ADD
        // 3 -> SUB
        // 4 -> MUL
        // 5 -> DIV
        // 6 -> ODD
        // 7 -> MOD
        // 8 -> EQL
        // 9 -> NEQ
        // 10 -> LSS
        // 11 -> LEQ
        // 12 -> GTR
        // 13 -> GEQ

        switch (M)
        {
          case 0:
            opr = "RTN";
            stack[BP - 1] = stack[SP];
            SP = BP - 1;
            BP = stack[SP + 2];
            PC = stack[SP + 3];
            break;
          default:
            opr = "ERR";
            break;
        }

        printf("%s %d %d \t%d \t%d \t%d", opr, L, M, PC + 1, BP, SP);

        break;
      case 3:
        SP++;
        stack[SP] = stack[base(stack, L, BP) + M];

        printf("LOD %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      case 4:
        stack[base(stack, L, BP) + M] = stack[SP];
        stack[SP]--;

        printf("STO %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      case 5:
        printf("CAL %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        stack[SP + 1] = base(stack, L, BP);
        stack[SP + 2] = BP;
        stack[SP + 3] = PC + 1;
        stack[SP + 4] = stack[SP];

        BP = SP + 1;
        PC = M - 1;

        break;
      case 6:
        // sp <- sp + M
        SP += M;

        for (int i = 0; i < M; i++)
        {
          push(0);
        }

        printf("INC %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        break;
      case 7:
        // pc <- M, adjusted for arrays being indexed at 0
        printf("JMP %d %d \t%d \t%d \t%d", L, M, M, BP, SP);

        PC = M - 1;

        break;
      case 8:

        // pc <- M iff top of stack == 0
        if (SP <= 0)
          PC = M - 1;


        printf("JPC %d %d \t%d \t%d \t%d", L, M, PC, BP, SP);

        break;
      case 9:

        if (M == 2)
        {
          int userInput = 0;

          printf("Please Enter an Integer: ");
          scanf("%d", &userInput);

          SP++;
          push(userInput);
        }

        printf("SYS %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      default:
        break;
    }

    if (SP > -1)
    {
      printf("\t");

      for (int i = 0; i <= SP; i++)
      {
        printf("%d ", stack[i]);

        if (i == BP - 1)
          printf("| ");
      }
    }

    printf("\n");

  }


  fclose(input);
  fclose(output);
}

bool push(int value) {
  if(SP >= MAX_STACK_HEIGHT - 1)
    return false;

  stack[SP] = value;

  return true;
}

int pop() {
  if (SP == EMPTY)
    return STACK_EMPTY;

  int result = stack[SP];
  SP--;

  return result;
}

int base(int stack[], int level, int BP)
{
  int base = BP;
  int counter = level;

  while (counter > 0)
  {
    base = stack[base];
    counter--;
  }

  return base;
}
