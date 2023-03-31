#include <stdio.h>

int main()
{
  int liczba, liczbaWy, dzielnik, dzielnikWy;
  int wynikDzielenia;
  int reszta;

  printf("Podaj liczbe: ");
  scanf("%d", &liczba);
  printf("Podaj dzielnik: ");
  scanf("%d", &dzielnik);

  dzielnikWy = dzielnik;
  liczbaWy = liczba;

  while (1)
  {
    wynikDzielenia = liczba / dzielnik;
    reszta = liczba % dzielnik;
    liczba = dzielnik;
    dzielnik = reszta;

    if (reszta == 0)
    {
      break;
    }
  }

  printf("NWD(%d, %d) = %d\n", liczbaWy, dzielnikWy, liczba);

  return 0;
}