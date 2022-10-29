#include <stdio.h>
#include <math.h>

int a, b, c, MAX, POSR, MIN;

int main()
{

    printf("Algorytm szeregujacy wartosci od najmniejszej do najwiekszej\n");
    printf("Podaj trzy rozne liczby calkowite\n");
    printf("Pierwsza liczba: ");
    scanf("%d", &a);
    printf("Druga liczba: ");
    scanf("%d", &b);
    printf("Trzecia liczba: ");
    scanf("%d", &c);

    if (a > b && a > c)
    {
        MAX = a;
        if (b > c)
        {
            POSR = b;
            MIN = c;
        }
        else
        {
            POSR = c;
            MIN = b;
        }
    }
    if (b > a && b > c)
    {
        MAX = b;
        if (a > c)
        {
            POSR = a;
            MIN = c;
        }
        else
        {
            POSR = c;
            MIN = a;
        }
    }
    if (c > b && c > a)
    {
        MAX = c;
        if (b > a)
        {
            POSR = b;
            MIN = a;
        }
        else
        {
            POSR = a;
            MIN = b;
        }
    }
    if (a == b || a == c || b == c)
    {
        printf("Bledne dane wejsciowe!!!");
    }
    else
    {
        printf("Kolejnosc rosnaca: \n");
        printf("%d > %d > %d", MAX, POSR, MIN);
    }
}
