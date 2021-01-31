#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_HEIGHT 50;
#define MAX_CODE_LENGTH 100;

typedef struct node {
  int value;
  struct node* next;
} node;

node* head = NULL;

bool push(int value) {
  node* newnode = malloc(sizeof(node));
  if (newnode == NULL)
     return false;
  newnode->value = value;
  newnode->next = head;
  head = newnode;
  
  return true;
}
int pop() {
  if (head == NULL)
    return -1;
  
  int result = head->value;
  node* tmp = head;
  head = head->next;
  free(tmp);
  
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

