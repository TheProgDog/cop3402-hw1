#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

int stack[MAX_STACK_HEIGHT];
int top = -1;

bool push(int value) {
  if(top >= MAX_STACK_HEIGHT - 1)
    return false;
  top++;
  stack[top] = value;
  
  return true;
}

int pop() {
  if (top == EMPTY)
    return STACK_EMPTY;
  
  int result = stack[top];
  top--;
  
  return result;
}

void main(int argc, char *argv[])
{
  FILE *input = fopen(argv[1], "r");
  FILE *output = fopen("output.txt", "w");

  int reader = 0;
  char OP, L, M;
  char dlim[] = " ";
  int instruction[MAX_CODE_LENGTH][3];

  int counter = 0, BP = 0, SP = -1;

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
    int L = instruction[PC][1], M = instruction[PC][2];

    switch(instruction[PC][0])
    {
      case 1:
        printf("%d\tLIT %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);
        break;
      case 2:
        printf("%d\tOPR %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);

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
            PC = stack[SP + 3] - 1;
            break;
          case 1:
            opr = "NEG";
            stack[SP] = -1 * stack[SP];
            break;
          case 2:
            opr = "ADD";
            SP -= 1;
            stack[SP] = stack[SP] + stack[SP + 1];
            break;
          case 3:
            opr = "SUB";
            SP -= 1;
            stack[SP] = stack[SP] - stack[SP + 1];
            break;
          case 4:
            opr = "MUL";
            SP -= 1;
            stack[SP] = stack[SP] * stack[SP + 1];
            break;
          case 5:
            opr = "DIV";
            SP -= 1;
            stack[SP] = stack[SP] / stack[SP + 1];
            break;
          case 6:
            opr = "ODD";
            stack[SP] = stack[SP] % 2;
            break;
          case 7:
            opr = "MOD";
            SP -= 1;
            stack[SP] = stack[SP] % stack[SP + 1];
            break;
          case 8:
            opr = "EQL";
            SP -= 1;
            stack[SP] = stack[SP] == stack[SP + 1];
            break;
          case 9:
            opr = "NEQ";
            SP -= 1;
            stack[SP] = stack[SP] != stack[SP + 1];
            break;
          case 10:
            opr = "LSS";
            SP -= 1;
            stack[SP] = stack[SP] < stack[SP + 1];
            break;
          case 11:
            opr = "LEQ";
            SP -= 1;
            stack[SP] = stack[SP] <= stack[SP + 1];
            break;
          case 12:
            opr = "GTR";
            SP -= 1;
            stack[SP] = stack[SP] > stack[SP + 1];
            break;
          case 13:
            opr = "GEQ";
            SP -= 1;
            stack[SP] = stack[SP] >= stack[SP + 1];
            break;
          default:
            opr = "ERR";
            break;
        }
        break;
      case 3:
        printf("%d\tLOD %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);
        break;
      case 4:
        printf("%d\tSTO %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);
        break;
      case 5:
        printf("%d\tCAL %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);

        BP = SP + 1;
        PC = M;
        
        break;
      case 6:
        printf("%d\tINC %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);
        break;
      case 7:
        // pc <- M, adjusted for arrays being indexed at 0
        printf("%d\tJMP %d %d \t%d \t%d \t%d\n", PC, L, M, M, BP, SP);

        PC = M - 1;

        break;
      case 8:
        printf("%d\tJPC %d %d \t%d \t%d \t%d\n", PC, L, M, M, BP, SP);

        // pc <- M iff top of stack == 0

        break;
      case 9:

        if (M == 2)
        {
          int userInput = 0;

          printf("Please Enter an Integer: ");
          scanf("%d", &userInput);

          // Do stuff with userInput -- add it to the top of the stack when stack is implemented
        }

        printf("%d\tSYS %d %d \t%d \t%d \t%d\n", PC, L, M, PC + 1, BP, SP);
        break;
      default:
        break;
    }

  }


  fclose(input);
  fclose(output);
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
