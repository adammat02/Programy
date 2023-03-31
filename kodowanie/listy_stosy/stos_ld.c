#include <stdio.h>
#include <stdlib.h>

typedef struct stos
{
  int dana;
  struct stos *nast;
  struct stos *popr;
} t_stos;

void init(t_stos *stos)
{
  stos = (t_stos *)malloc(sizeof(t_stos));
  stos = NULL;
}

int push(t_stos **stos, int *dana)
{
  int push;
  t_stos *tmp = (t_stos *)malloc(sizeof(t_stos));
  if (tmp == NULL)
  {
    push = 0;
    return push;
  }
  tmp->dana = *dana;
  tmp->nast = *stos;
  tmp->popr = NULL;
  if (*stos != NULL)
  {
    (*stos)->popr = tmp;
  }
  *stos = tmp;
  push = 1;
  return push;
}

int pop(t_stos **stos, int *dana)
{
  int pop;
  if (*stos == NULL)
  {
    pop = 0;
    return pop;
  }
  if ((*stos)->nast == NULL)
  {
    free(*stos);
    *stos = NULL;
    pop = 1;
    return pop;
  }
  *stos = (*stos)->nast;
  free((*stos)->popr);
  (*stos)->popr = NULL;
  pop = 1;
  return pop;
}

int empty(t_stos *stos)
{
  int isempty;
  if (stos == NULL)
  {
    isempty = 1;
  }
  else
  {
    isempty = 0;
  }
  return isempty;
}
