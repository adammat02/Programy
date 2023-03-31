#include <stdio.h>

int main()
{
  char tekst[] = "Siema eniu tu twoj ziomek z hiszpani";
  char slowo[] = "eniu";
  int pozycja = 0;

  for (int i = 0; i < sizeof(tekst) - 1; i++)
  {
    int liczba = 0;
    if (tekst[i] == slowo[0])
    {
      pozycja = i;
      for (int k = 0; k < sizeof(slowo) - 1; k++)
      {
        if (slowo[k] == tekst[pozycja + k])
        {
          liczba++;
        }
      }
      if (liczba == sizeof(slowo) - 1)
      {
        break;
      }
      else
      {
        pozycja = -1;
      }
    }
  }
  printf("%d\n", pozycja);
}