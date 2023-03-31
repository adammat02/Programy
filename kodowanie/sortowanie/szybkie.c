#include <stdio.h>

void zamien(int *a, int *b)
{
  int temp = *a;
  *a = *b;
  *b = temp;
}

void sort_szybkie(int *tab, int min, int max)
{
  if (max <= min)
  {
    return;
  }

  int i = min;
  int j = max;
  int pivot = tab[(i + j) / 2];

  while (1)
  {
    while (tab[i] < pivot)
    {
      i++;
    }

    while (tab[j] > pivot)
    {
      j--;
    }

    if (i <= j)
    {
      zamien(&tab[i], &tab[j]);
      i++;
      j--;
    }
    else
    {
      break;
    }
  }
  if (min < j)
  {
    sort_szybkie(tab, min, j);
  }
  if (i < max)
  {
    sort_szybkie(tab, i, max);
  }
}

void wypisz_tab(int *tab, int rozmiar)
{
  for (int i = 0; i < rozmiar; i++)
  {
    printf(" %d", tab[i]);
  }
  printf("\n");
}

int main()
{
  int tabela[] = {2, 9, 6, -6, 50, 34, 78, -69, 0};

  printf("Nieposortowane: ");
  wypisz_tab(tabela, 9);

  printf("Posortowane: ");
  sort_szybkie(tabela, 0, 8);
  wypisz_tab(tabela, 9);

  return 0;
}