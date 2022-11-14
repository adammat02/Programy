#include <stdio.h>

int main()
{
  char wybor[2] = " ";
  while (wybor[0] != '4')
  {
    printf("Proste menu: \n");
    printf("\t1 -- Pozycja pierwsza\n");
    printf("\t2 -- Pozycja druga\n");
    printf("\t3 -- Pozycja trzecia\n");
    printf("\t4 -- Zakoncz dzialanie\n");
    printf("Twoj wybor: ");

    scanf("%1s", wybor);

    switch (wybor[0])
    {
    case '1':
      printf("Wybrano pozycje pierwsza\n");
      break;
    case '2':
      printf("Wybrano pozycje druga\n");
      break;
    case '3':
      printf("wybrano pozycje trzecia\n");
      break;
    case '4':
      printf("Koniec programu\n");
      break;
    default:
      printf("Brak obslugi dla wejscia\n");
      break;
    }
  }
}