#include <stdio.h>
#include <stdlib.h>

typedef struct elem
{
  int dana;
  struct elem *nast;
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
  poczatek = tmp;
  return poczatek;
}

t_elem *dodaj_poczatek2(t_elem *poczatek, t_elem *elem)
{
  elem->nast = poczatek;
  poczatek = elem;
  return poczatek;
}

t_elem *dodaj_koniec1(t_elem *poczatek, int dana)
{
  t_elem *tmp = (t_elem *)malloc(sizeof(t_elem));
  tmp->dana = dana;
  tmp->nast = NULL;
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
  tmp->nast = poprzedni->nast;
  poprzedni->nast = tmp;
  return poczatek;
}

t_elem *dodaj2(t_elem *poczatek, t_elem *poprzedni, t_elem *elem)
{
  if (poprzedni == NULL)
  {
    fprintf(stderr, "Blad: Poprzedni element nie istnieje\n");
    exit(1);
  }
  elem->nast = poprzedni->nast;
  poprzedni->nast = elem;
  return poczatek;
}

t_elem *usun_poczatek(t_elem *poczatek)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  t_elem *tmp = poczatek;
  poczatek = poczatek->nast;
  free(tmp);
  return poczatek;
}

t_elem *usun_koniec(t_elem *poczatek)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  t_elem *tmp = poczatek;
  while (tmp->nast->nast != NULL)
  {
    tmp = tmp->nast;
  }
  free(tmp->nast);
  tmp->nast = NULL;
  return poczatek;
}

t_elem *usun_zza(t_elem *poczatek, t_elem *elem)
{
  if (elem->nast == NULL)
  {
    fprintf(stderr, "Blad: Podany element jest ostatni\n");
    exit(1);
  }
  t_elem *tmp = elem->nast;
  elem->nast = tmp->nast;
  free(tmp);
  return poczatek;
}

t_elem *usun(t_elem *poczatek, t_elem *elem)
{
  if (poczatek == NULL)
  {
    return poczatek;
  }
  if (elem == poczatek)
  {
    t_elem *tmp = poczatek;
    poczatek = poczatek->nast;
    free(tmp);
    return poczatek;
  }
  t_elem *tmp = poczatek;
  while (tmp->nast != elem)
  {
    tmp = tmp->nast;
  }
  tmp->nast = elem->nast;
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

  lista = dodaj_poczatek1(lista, 3);
  lista = dodaj_poczatek1(lista, 36);
  lista = dodaj_poczatek1(lista, 67);
  lista = usun_zza(lista, wskaznik_elementu(lista, 1));

  full_print(lista);
}