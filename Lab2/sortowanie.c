#include <stdio.h>
#include <math.h>

int main()
{

  for (int i = 1; i <= 99; i++)
  {
    printf("%d\t", i);

    if (i % 10 == 0)
    {
      printf("\n");
    }
  }

  printf("\n");
}
