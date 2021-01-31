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
void main()
{
  FILE *input = fopen("input.txt", "r");
  FILE *output = fopen("output.txt", "w");

  char reader = 'a';
  char OP, L, M;
  char dlim[] = " ";
  int instruction[MAX_CODE_LENGTH][3];

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

