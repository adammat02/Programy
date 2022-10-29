#include <stdio.h>
#define prog 20

int main()
{
    int temperatura;

    printf("Podaj temperature we Wrocławiu: ");
    scanf("%d", &temperatura);

    if (temperatura >= prog)
    {
        printf("Jest bardzo ladna pogoda!\n");
    }
    else
    {
        printf("Nie jest zbyt cieplo!\n");
    }
}
