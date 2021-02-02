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

#define MAX_STACK_HEIGHT 50
#define MAX_CODE_LENGTH 100
#define EMPTY (-1)
#define STACK_EMPTY INT_MIN

int stack[MAX_STACK_HEIGHT];
int top = -1;
// push function pushes an int value into a stack
bool push(int value) {
  if(top >= MAX_STACK_HEIGHT - 1)
    return false;
  top++;
  stack[top] = value;
  
  return true;
}
// pops the top value from a stack and returns that value
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

  int halt = 1;

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
  printf("Initial values:\t\t0\t%d\t%d\n", BP, SP);

  for (int PC = 0; PC < counter; PC++)
  {
    int userInput = 0;
    int counter = PC;
    //printf("%d\t", PC);

    char *opr;

    int L = instruction[PC][1], M = instruction[PC][2];

    switch(instruction[PC][0])
    {
      case 1:
        //printf("LIT %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        opr = "LIT";
        SP ++;
        push(M);

        break;
      case 2:

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
            break;
          case 2:
            opr = "ADD";
            break;
          case 3:
            opr = "SUB";
            break;
          case 4:
            opr = "MUL";
            break;
          case 5:
            opr = "DIV";
            break;
          case 6:
            opr = "ODD";
            break;
          case 7:
            opr = "MOD";
            break;
          case 8:
            opr = "EQL";
            break;
          case 9:
            opr = "NEQ";
            break;
          case 10:
            opr = "LSS";
            break;
          case 11:
            opr = "LEQ";
            break;
          case 12:
            opr = "GTR";
            break;
          case 13:
            opr = "GEQ";
            break;
          default:
            opr = "ERR";
            break;
        }

        //printf("%s %d %d \t%d \t%d \t%d", opr, L, M, PC + 1, BP, SP);

        break;
      case 3:
        opr = "LOD";
        SP++;
        stack[SP] = stack[base(stack, L, BP) + M];

        //printf("LOD %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      case 4:
        opr = "STO";
        stack[base(stack, L, BP) + M] = stack[SP];
        SP--;

        //printf("STO %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      case 5:
        //printf("CAL %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        opr = "CAL";

        stack[SP + 1] = base(stack, L, BP);
        stack[SP + 2] = BP;
        stack[SP + 3] = PC + 1;
        stack[SP + 4] = stack[SP];

        BP = SP + 1;
        PC = M - 1;

        break;
      case 6:

        opr = "INC";

        // sp <- sp + M
        SP += M;

        //printf("INC %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);

        break;
      case 7:

        //printf("JMP %d %d \t%d \t%d \t%d", L, M, M, BP, SP);

        opr = "JMP";

        // pc <- M, adjusted for arrays being indexed at 0
        PC = M - 1;

        break;
      case 8:

        // pc <- M iff top of stack == 0
        if (SP <= 0)
          PC = M - 1;

        opr = "JPC";
        //printf("JPC %d %d \t%d \t%d \t%d", L, M, PC, BP, SP);

        break;
      case 9:

        opr = "SYS";

        switch (M)
        {
          case 1:
            printf("Top of Stack Value: %d\n", pop(stack));
            break;
          case 2:
            printf("Please Enter an Integer: ");
            scanf("%d", &userInput);

            SP++;
            push(userInput);

            break;
          case 3:
            halt = 0;
            break;
          default:
            break;
        }

        //printf("SYS %d %d \t%d \t%d \t%d", L, M, PC + 1, BP, SP);
        break;
      default:
        break;
    }

    printf("%d\t%s %d %d \t%d \t%d \t%d", counter, opr, L, M, PC + 1, BP, SP);

    if (SP > -1)
    {
      printf("\t");

      for (int i = 0; i <= SP; i++)
      {
        if (i == BP && BP != 0)
          printf("| ");

        printf("%d ", stack[i]);
      }
    }

    printf("\n");

    if (halt == 0)
      break;

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
