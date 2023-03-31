#include <stdio.h>

int main()
{
    int n;
    unsigned long int a = 1, b = 1, c = 0;

    printf("Ile wyrazow ciagu z zakresu 0 - 93 oblicyc: ");
    scanf("%d", &n);

    if (n >= 0 && n <= 93)
    {
        for (int i = 1; i <= n; i++)
        {
            if (i < 3)
            {
                printf("%lu\n", a);
            }
            else
            {
                c = a + b;
                a = b;
                b = c;

                printf("%lu\n", c);
            }
        }
    }
    else
    {
        printf("Podano bledny zakres!\n");
    }
}