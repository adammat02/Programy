/***************************************************************************************************************
 *                                                                                                             *
 *  Autor: Adam Matusiak                                                                                       *
 *  Data Utworzenia: 25.01.2023                                                                                *
 *  Nazwa programu: Kalkultor RPN                                                                              *
 *  Wersja: 1.0v                                                                                               *
 *                                                                                                             *
 *  Charakterystyka:                                                                                           *
 *    Program peln funkcje kalkulatora RPN. Program wykorzystuje funkcje operowania stosem.                    *
 *    Funkcje te zostaly stworzone przeze mnie na potrzebe wykonania zadan z listy 6 PPROG.                    *
 *                                                                                                             *
 *  Charakterystyka danych:                                                                                    *
 *    Program przyjmuje argumenty w postaci liczb oraz opcji ktore wykonuja operacje na liczbach               *
 *                                                                                                             *
 *                                                                                                             *
 ***************************************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_TOKEN 255

typedef struct stos
{
    int dana;
    struct stos *nast;
} t_stos;

void push(struct stos **stos, int dana)
{
    t_stos *tmp = (t_stos *)malloc(sizeof(t_stos));
    if (tmp == NULL)
    {
        exit(1);
    }
    tmp->dana = dana;
    tmp->nast = *stos;
    *stos = tmp;
}

void pop(t_stos **stos, int *dana)
{
    if (*stos == NULL)
    {
        printf("Blad: brak elementu do sciogniecia\n");
        exit(1);
    }
    if ((*stos)->nast == NULL)
    {   
        *dana = (*stos)->dana;
        free(*stos);
        *stos = NULL;
    }
    else
    {
        *dana = (*stos)->dana;
        t_stos *tmp = *stos;
        *stos = (*stos)->nast;
        free(tmp);
    }
}

void clear(t_stos **stos)
{

    t_stos *curr = *stos;

    while (curr != NULL)
    {
        t_stos *tmp = curr;
        curr = curr->nast;
        free(tmp);
    }
    *stos = NULL;
}

void duplicate(t_stos **stos)
{
    int val;
    val = (*stos)->dana;
    push(stos, val);
}

void reverse(t_stos **stos)
{
    int a, b;
    a = (*stos)->dana;
    b = (*stos)->nast->dana;
    (*stos)->dana = b;
    (*stos)->nast->dana = a;
}

void full_print(t_stos *stos)
{
    t_stos *curr = stos;
    printf("Zawartosc stosu: ");
    while (curr != NULL)
    {
        printf("%d ", curr->dana);
        curr = curr->nast;
    }
    printf("\n");
}

void top_print(t_stos *stos)
{
    if (stos == NULL)
    {
        printf("Brak wartosci na stosie\n");
    }
    else
    {
        printf("Wartosc na gorze stosu: %d\n", stos->dana);
    }
}

int main()
{
    t_stos *stos = (t_stos *)malloc(sizeof(t_stos));
    stos = NULL;

    char token[MAX_TOKEN];
    int value, a = 0, b = 0, tmp;


    scanf("%s", token); /* pobierz pierwszy znak */

    while (strcmp("q", token) != 0) /* jesli na wejsciu jest q to wyjdz z petli */
    {
        if (sscanf(token, "%d", &value) == 1) /* jesli token jest liczba to wepchnij na stos  */
        {
            push(&stos, value);
        }
        else /* jesli token to opcja, wkonaj */
        {
            switch (token[0])
            {

            case '+': /* opcja dodawania */
                if (stos->nast == NULL)
                {
                    printf("Operacja dodawania mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    pop(&stos, &a);
                    pop(&stos, &b);
                    push(&stos, (b + a));
                }
                break;

            case '-': /* opcja odejmowania */
                if (stos->nast == NULL)
                {
                    printf("Operacja odejmowania mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    pop(&stos, &a);
                    pop(&stos, &b);
                    push(&stos, (b - a));
                }
                break;

            case '*': /* opcja mnozenia */
                if (stos->nast == NULL)
                {
                    printf("Operacja mnozenia mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    pop(&stos, &a);
                    pop(&stos, &b);
                    push(&stos, (b * a));
                }
                break;

            case '/': /* opcja dzielenia */
                if (stos->nast == NULL)
                {
                    printf("Operacja dzielenia mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    pop(&stos, &a);
                    pop(&stos, &b);
                    push(&stos, (b / a));
                }
                break;

            case 'P': /* opcja sciagniecia liczby ze szczytu stosu */
                pop(&stos, &tmp);
                break;

            case 'c': /* opcja wyczyszczenia stosu */
                clear(&stos);
                break;

            case 'r': /* opcja zamiany dwoch ostatnich liczb */
                if (stos->nast == NULL)
                {
                    printf("Operacja reverse mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    reverse(&stos);
                }
                break;

            case 'd': /* opcja duplikowania liczby na gorze stosu */
                if (stos->nast == NULL)
                {
                    printf("Operacja duplicate mozliwa gdy sa conajmniej dwie liczby\n");
                }
                else
                {
                    duplicate(&stos);
                }
                break;

            case 'p': /* opcja wypisania liczby z gory stosu */
                top_print(stos);
                break;

            case 'f': /* opcja wypisania calego stosu */
                full_print(stos);
                break;

            default: /* komunikat w razie wpisania blednej opcji */
                printf("Niepoprawna opcja\n");
                break;
            }
        }

        scanf("%s", token); /* pobierz kolejny znak */
    }
    printf("\n");
}