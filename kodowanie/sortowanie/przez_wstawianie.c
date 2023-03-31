#include <stdio.h>

void sort_pr_wst(int *tab, int rozmiar)
{
  int tmp, i;
  for (int j = 1; j < rozmiar; j++)
  {
    tmp = tab[j];
    i = j - 1;

    while (i >= 0 && tab[i] > tmp)
    {
      tab[i + 1] = tab[i];
      --i;
    }
    tab[i + 1] = tmp;
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
  sort_pr_wst(tabela, 9);
  wypisz_tab(tabela, 9);

  return 0;
}