#include <stdio.h>

int wypelnij(int, int);
int wypisz(int, int);
int zmienZnak(int, int);

int tablica[10][10];

int main()
{
  wypelnij(3, 7);
  printf("Zawartosc orginalna: \n");
  wypisz(3, 7);
  zmienZnak(3, 7);
  printf("Zawartosc po zmianie znaku: \n");
  wypisz(3, 7);

  return 0;
}

int wypelnij(int a, int b)
{
  for (int wiersz = 0; wiersz < a; wiersz++)
  {
    for (int kolumna = 0; kolumna < b; kolumna++)
    {
      tablica[wiersz][kolumna] = wiersz * kolumna;
    }
  }
}

int wypisz(int a, int b)
{
  for (int wiersz = 0; wiersz < a; wiersz++)
  {
    for (int kolumna = 0; kolumna < b; kolumna++)
    {
      printf("\t%d", tablica[wiersz][kolumna]);
    }
    printf("\n");
  }
}

int zmienZnak(int a, int b)
{
  for (int wiersz = 0; wiersz < a; wiersz++)
  {
    for (int kolumna = 0; kolumna < b; kolumna++)
    {
      tablica[wiersz][kolumna] = -tablica[wiersz][kolumna];
    }
  }
}
