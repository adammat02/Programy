#include <stdio.h>

void babelkowe(int *tab, int rozmiar)
{
  int tmp;
  for (int j = 0; j < rozmiar - 1; j++)
  {
    for (int i = 0; i < rozmiar - 1; i++)
    {
      if (tab[i] > tab[i + 1])
      {
        tmp = tab[i];
        tab[i] = tab[i + 1];
        tab[i + 1] = tmp;
      }
    }
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
  babelkowe(tabela, 9);
  wypisz_tab(tabela, 9);

  return 0;
}