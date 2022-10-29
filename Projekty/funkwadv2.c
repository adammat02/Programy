#include <stdio.h>
#include <math.h>

int main()
{
    float a, b, c, d, x, x1, x2;

    printf("Wpisz parametr a: ");
    scanf("%f", &a);
    printf("Wpisz parametr b: ");
    scanf("%f", &b);
    printf("Wpisz parametr c: ");
    scanf("%f", &c);
    if (a == 0)
    {
        printf("chuju zmien a");
    }
    else
    {
        d = pow(b, 2) - 4 * a * c;
        if (d < 0)
        {
            if (a > 0)
            {
                printf("Funkcja nie przyjmuje ujemnych wartosci :c\n");
            }
            else
            {
                printf("Wszystkie argumnety przyjmuja wartosci ujemne\n");
            }
        }
        else if (d > 0)
        {
            x1 = (-b - sqrt(d)) / (2 * a);
            x2 = (-b + sqrt(d)) / (2 * a);
            if (a > 0)
            {
                printf("Fukcja przyjmuje wartosci ujemne od -& do %f oraz od %f do &\n", x1, x2);
            }
            else
            {
                printf("Funkcja przyjmuje wartosci ujemne od %f do %f\n", x1, x2);
            }
        }
        else
        {
            p = -b / (2 * a);
            if (a > 0)
            {
                printf("Funkcja nie przyjmuje wartosci ujemnych :c\n");
            }
            else
            {
                printf("Wszystkie argumnenty przyjmuja wartosci ujemne oprocz x=%f\n", x);
            }
        }
    }

    return 0;
}
