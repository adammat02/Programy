#include <stdio.h>
#include <stdlib.h>


typedef struct stack
{
  int data;
  struct stack *next;
} stack;

void init(struct stack **head);
int isempty(struct stack *head);
void push(struct stack **head, int data);
void pop(struct stack **head, int *data);
void clear(struct stack **head);
void duplicate(struct stack **head);
void reverse(struct stack **head);
void full_print(struct stack *head);
void top_print(struct stack *head);
int count(struct stack *head);