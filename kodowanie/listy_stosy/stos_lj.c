#include <stdio.h>
#include <stdlib.h>

typedef struct stos
{
  int dana;
  struct stos *nast;
} t_stos;

void init(t_stos *stos)
{
  stos = (t_stos *)malloc(sizeof(t_stos));
  stos = NULL;
}

int push(struct stos **stos, int *dana)
{
  int push;
  struct stos *tmp = (t_stos *)malloc(sizeof(t_stos));
  if (tmp == NULL)
  {
    push = 0;
    return push;
  }
  tmp->dana = *dana;
  tmp->nast = *stos;
  *stos = tmp;
  push = 1;
  return push;
}

int pop(t_stos **stos, int *dana)
{
  int pop;
  if (stos == NULL)
  {
    pop = 0;
    return pop;
  }
  *dana = (*stos)->dana;
  t_stos *tmp = *stos;
  *stos = (*stos)->nast;
  free(tmp);
  pop = 1;
  return pop;
}

int isempty(t_stos *stos)
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
