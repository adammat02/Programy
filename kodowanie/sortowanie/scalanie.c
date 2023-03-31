#include <stdio.h>

void scal(int *tab, int lewy, int srodek, int prawy)
{
  int i, j, k;
  int pom[prawy + 1];

  for (i = lewy; i <= prawy; i++)
  {
    pom[i] = tab[i];
  }
  i = lewy;
  j = srodek + 1;
  
  for (k = lewy; k <= prawy; k++)
  {
    if (i <= srodek)
    {
      if (j <= prawy)
      {
        if (pom[j] < pom[i])
        {
          tab[k] = pom[j++];
        }
        else
        {
          tab[k] = pom[i++];
        }
      }
      else
      {
        tab[k] = pom[i++];
      }
    }
    else
    {
      tab[k] = pom[j++];
    }
  }
}

void sort_scal(int *tab, int lewy, int prawy)
{
  if (prawy <= lewy)
  {
    return;
  }
  int srodek = (prawy + lewy) / 2;
  sort_scal(tab, lewy, srodek);
  sort_scal(tab, srodek + 1, prawy);
  scal(tab, lewy, srodek, prawy);
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

  sort_scal(tabela, 0, 8);

  printf("Posortowane: ");
  wypisz_tab(tabela, 9);

  return 0;
}
