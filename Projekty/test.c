#include <stdio.h>

#define warunekStopu 99
#define progGrupy 99
#define upDana 10
#define downDana -10
#define upPuls 14
#define downPuls 8

int czyNalezy();

int main()
{
  int dana[progGrupy];
  int danaStopu;

  while (danaStopu != warunekStopu)
  {
    int puls = 0;

    for (int i = 0; i < progGrupy; i++)
    {
      scanf("%d", &dana[i]);

      if (dana[i] == warunekStopu)
      {
        danaStopu = dana[i];
        break;
      }

      if (czyNalezy(downDana, upDana, dana[i]) == 0)
      {
        dana[i] = dana[i - 1];
      }
      printf("%d\n", dana[i]);
    }

    if (danaStopu == warunekStopu)
    {
      break;
    }

    for (int i = 1; i < progGrupy; i++)
    {
      while (dana[i - 1] == 0)
      {
        i++;
      }
      int pierwszaDana = dana[i - 1];

      while (dana[i] == 0)
      {
        i++;
      }
      int drugaDana = dana[i];

      if (pierwszaDana * drugaDana < 0)
      {
        puls++;
      }
    }

    if (czyNalezy(downPuls, upPuls, puls) == 1)
    {
      printf("Puls prawidlowy i wynosi %d\n", puls);
    }
    else
    {
      printf("Puls nie prawidlowy i wynosi %d\n", puls);
    }
  }
}

int czyNalezy(int low, int high, int data)
{
  int result;
  if (data >= low && data <= high)
  {
    result = 1;
  }
  else
  {
    result = 0;
  }
  return result;
}