#include <stdio.h>

int silnia(int a)
{
  int wynik = 1;
  if (a == 0)
  {
    return 1;
  }
  if (a == 1)
  {
    return a;
  }
  for (int i = 0; i < a; i++)
  {
    wynik *= (a - i);
  }
  return wynik;
}

int main()
{

  int wiersze, wynik;

  printf("Podaj ilosc wierszy: ");
  scanf("%d", &wiersze);

  for (int k = 0; k <= wiersze; ++k)
  {

    wynik = silnia(wiersze) / (silnia(wiersze - k) * silnia(k));
    printf("%d ", wynik);
  }
  printf("\n");
}