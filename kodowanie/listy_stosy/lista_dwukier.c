#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
  int dana;
  struct elem *nast;
  struct elem *popr;

} t_elem;

t_elem *inicjuj()
{
  t_elem *poczatek = (t_elem *)malloc(sizeof(t_elem));
  poczatek = NULL;
  return poczatek;
}

t_elem *tworz(int dana)
{
  t_elem *elem = (t_elem *)malloc(sizeof(t_elem));
  elem->dana = dana;
  elem->nast = NULL;
  elem->popr = NULL;
  return elem;
}

t_elem *wskaznik_elementu(t_elem *poczatek, int nr)
{
  t_elem *tmp = poczatek;
  for (int i = 1; i < nr; i++)
  {
    tmp = tmp->nast;
  }
  if (nr <= 0 || tmp == NULL)
  {
    tmp = NULL;
  }
  return tmp;
}

t_elem *dodaj_poczatek1(t_elem *poczatek, int dana)
{
  t_elem *tmp = (t_elem *)malloc(sizeof(t_elem));
  tmp->dana = dana;
  tmp->nast = poczatek;
  tmp->popr = NULL;
  if (poczatek != NULL)
  {
    poczatek->popr = tmp;
  }
  poczatek = tmp;
  return poczatek;
}

t_elem *dodaj_poczatek2(t_elem *poczatek, t_elem *elem)
{
  elem->popr = NULL;
  elem->nast = poczatek;
  if (poczatek != NULL)
  {
    poczatek->popr = elem;
  }
  poczatek = elem;
  return poczatek;
}

t_elem *dodaj_koniec1(t_elem *poczatek, int dana)
{
  t_elem *tmp = (t_elem *)malloc(sizeof(t_elem));
  tmp->dana = dana;
  tmp->nast = NULL;
  tmp->popr = NULL;
  if (poczatek == NULL)
  {
    poczatek = tmp;
  }
  else
  {
    t_elem *curr = poczatek;
    while (curr->nast != NULL)
    {
      curr = curr->nast;
    }
    curr->nast = tmp;
    tmp->popr = curr;
  }
  return poczatek;
}

t_elem *dodaj_koniec2(t_elem *poczatek, t_elem *elem)
{
  if (poczatek == NULL)
  {
    poczatek = elem;
  }
  else
  {
    t_elem *curr = poczatek;
    while (curr->nast != NULL)
    {
      curr = curr->nast;
    }
    curr->nast = elem;
    elem->popr = curr;
  }
  return poczatek;
}

t_elem *dodaj1(t_elem *poczatek, t_elem *poprzedni, int dana)
{
  if (poprzedni == NULL)
  {
    fprintf(stderr, "Blad: Poprzedni element nie istnieje\n");
    exit(1);
  }
  t_elem *tmp = (t_elem *)malloc(sizeof(t_elem));
  tmp->dana = dana;
  tmp->popr = poprzedni;
  tmp->nast = poprzedni->nast;
  poprzedni->nast = tmp;
  tmp->nast->popr = tmp;
  return poczatek;
}

t_elem *dodaj2(t_elem *poczatek, t_elem *poprzedni, t_elem *elem)
{
  if (poprzedni == NULL)
  {
    fprintf(stderr, "Blad: Poprzedni element nie istnieje\n");
    exit(1);
  }
  elem->popr = poprzedni;
  elem->nast = poprzedni->nast;
  poprzedni->nast = elem;
  elem->nast->popr = elem;
  return poczatek;
}

t_elem *usun_poczatek(t_elem *poczatek)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  if (poczatek->nast == NULL)
  {
    free(poczatek);
    return NULL;
  }
  poczatek = poczatek->nast;
  free(poczatek->popr);
  poczatek->popr = NULL;
  return poczatek;
}

t_elem *usun_koniec(t_elem *poczatek)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  if (poczatek->nast == NULL)
  {
    free(poczatek);
    return NULL;
  }
  t_elem *tmp = poczatek;
  while (tmp->nast != NULL)
  {
    tmp = tmp->nast;
  }
  tmp->popr->nast = NULL;
  free(tmp);
  return poczatek;
}

t_elem *usun_zza(t_elem *poczatek, t_elem *elem)
{
  if (elem->nast == NULL)
  {
    fprintf(stderr, "Blad: Podany element jest ostatni\n");
    exit(1);
  }
  elem->nast = elem->nast->nast;
  free(elem->nast->popr);
  elem->nast->popr = elem;
  return poczatek;
}

t_elem *usun(t_elem *poczatek, t_elem *elem)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  elem->popr->nast = elem->nast;
  elem->nast->popr = elem->popr;
  free(elem);
  return poczatek;
}

void full_print(t_elem *poczatek)
{
  t_elem *curr;
  curr = poczatek;

  while (curr != NULL)
  {
    printf("%d ", curr->dana);
    curr = curr->nast;
  }
  printf("\n");
}

int main()
{
  t_elem *lista = inicjuj();

  lista = dodaj_koniec2(lista, tworz(7));
  lista = dodaj_koniec2(lista, tworz(65));
  lista = dodaj_koniec2(lista, tworz(445));
  lista = dodaj_koniec2(lista, tworz(-34));

  lista = usun(lista, wskaznik_elementu(lista, 2));

  full_print(lista);
}