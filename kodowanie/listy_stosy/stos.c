#include <stdio.h>
#include <stdlib.h>
#include "stos.h"


void init(struct stack **head)
{
  *head = NULL;
}

int isempty(struct stack *head)
{
  if (head == NULL)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

void push(struct stack **head, int data)
{
  struct stack *tmp = (struct stack *)malloc(sizeof(struct stack));
  if (tmp == NULL)
  {
    exit(-1);
  }
  tmp->data = data;
  tmp->next = *head;
  *head = tmp;
}

void pop(struct stack **head, int *data)
{
  if (isempty(*head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }
  struct stack *tmp = *head;
  *data = (*head)->data;
  *head = (*head)->next;
  free(tmp);
}


void clear(struct stack **head)
{
  if (isempty(*head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }

  struct stack *current = *head;

  while (current != NULL)
  {
    struct stack *tmp = current;
    current = current->next;
    free(tmp);
  }
  *head = NULL;
}


void duplicate(struct stack **head)
{
  if (isempty(*head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }
  int val;
  val = (*head)->data;
  push(head, val);
}

void reverse(struct stack **head)
{
  if (isempty(*head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }
  int a, b;
  a = (*head)->data;
  b = (*head)->next->data;
  (*head)->data = b;
  (*head)->next->data = a;
}

void full_print(struct stack *head)
{
  if (isempty(head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }
  struct stack *current;
  current = head;
  printf("Zawartosc stosu: ");
  while (current->next != NULL)
  {
    printf("%d ", current->data);
    current = current->next;
  }
  printf("\n");
}

void top_print(struct stack *head)
{
  if (isempty(head) == 1)
  {
    printf("Stos jest pusty\n");
    return;
  }
  printf("Wartosc na gorze stosu: %d\n", head->data);
}
int count(struct stack *head)
{
    int count = 1;
    if (head == NULL)
    {
        return 0;
    }
    while (head->next != NULL)
    {
        count++;
        head = head->next;
    }
    return count;
}

