#include <stdio.h>

#define KONIEC 99
#define GRUPA 99
#define WMAX 10
#define WMIN -10
#define PMAX 14
#define PMIN 8

int main()
{
  int wartosc = 0;
  int wartoscPoprzednia = 0;
  int liczbaPrzeciec = 0;
  int liczbaGrupy = 0;

  while (1)
  {
    scanf("%d", &wartosc);

    if (wartosc == KONIEC)
    {
      break;
    }

    if (wartosc >= WMIN && wartosc <= WMAX)
    {
      liczbaGrupy++;

      if (wartoscPoprzednia * wartosc < 0)
      {
        liczbaPrzeciec++;
      }

      if (wartosc != 0)
      {
        wartoscPoprzednia = wartosc;
      }
    }
    else
    {
      liczbaGrupy++;
    }

    if (liczbaGrupy == GRUPA)
    {
      if (liczbaPrzeciec >= PMIN && liczbaPrzeciec <= PMAX)
      {
        printf("Puls poprawny i wynosi: %d\n", liczbaPrzeciec);
      }
      else
      {
        printf("Puls niepoprawny i wynosi %d\n", liczbaPrzeciec);
      }

      wartosc = 0;
      wartoscPoprzednia = 0;
      liczbaPrzeciec = 0;
      liczbaGrupy = 0;
    }
  }
  return 0;
}