#include <stdio.h>

int main()
{
    int a;
    int b;
    while (a != 99)
    {
        printf("Podaj %d. wartosc parametru: ", ++b);
        scanf("%d", &a);

        if (a >= -5 && a <= 5)
        {
            printf("Aktualna wartosc parametru: %d\n", a);
        }
        else if (a != 99)
        {
            printf("Bledna wartosc parametru!\n");
        }
    }
}