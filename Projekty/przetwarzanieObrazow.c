#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 1024      /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */

int czytaj(FILE *plik_we, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */
  int i, j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
    return (0);
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ((buf[0] != 'P') || (buf[1] != '2') || koniec)
  { /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
    return (0);
  }

  /* Pominiecie komentarzy */
  do
  {
    if ((znak = fgetc(plik_we)) == '#')
    {                                            /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, plik_we) == NULL) /* Przeczytaj ja do bufora                */
        koniec = 1;                              /* Zapamietaj ewentualny koniec danych */
    }
    else
    {
      ungetc(znak, plik_we);        /* Gdy przeczytany znak z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(plik_we, "%d %d %d", wymx, wymy, szarosci) != 3)
  {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return (0);
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i = 0; i < *wymy; i++)
  {
    for (j = 0; j < *wymx; j++)
    {

      if (fscanf(plik_we, "%d", &(obraz[i][j])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
        return (0);
      }
    }
  }
}

void negatyw(FILE *plik_wy, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{

  fprintf(plik_wy, "P2\n");
  fprintf(plik_wy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wy, "%d\n", *szarosci);

  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      obraz[i][j] = *szarosci - obraz[i][j];
      fprintf(plik_wy, "%d\t", obraz[i][j]);
    }
  }
}

void kontur(FILE *plik_wy, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{

  fprintf(plik_wy, "P2\n");
  fprintf(plik_wy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wy, "%d\n", *szarosci);

  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      int w1 = abs(obraz[i + 1][j] - obraz[i][j]);
      int w2 = abs(obraz[i][j + 1] - obraz[i][j]);
      obraz[i][j] = w1 + w2;

      fprintf(plik_wy, "%d\t", obraz[i][j]);
    }
  }
}

void rozciaganie_histogramu(FILE *plik_wy, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  int szaroscMax = 0;
  int szaroscMin = *szarosci;

  fprintf(plik_wy, "P2\n");
  fprintf(plik_wy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wy, "%d\n", *szarosci);

  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      if (obraz[i][j] < szaroscMin)
      {
        szaroscMin = obraz[i][j];
      }
      if (obraz[i][j] > szaroscMax)
      {
        szaroscMax = obraz[i][j];
      }
    }
  }

  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      obraz[i][j] = (obraz[i][j] - szaroscMin) * *szarosci / (szaroscMax - szaroscMin);
      fprintf(plik_wy, "%d\t", obraz[i][j]);
    }
  }
}

void wyswietl(char *n_pliku)
{
  char polecenie[DL_LINII]; /* bufor pomocniczy do zestawienia polecenia */

  strcpy(polecenie, "display "); /* konstrukcja polecenia postaci */
  strcat(polecenie, n_pliku);    /* display "nazwa_pliku" &       */
  strcat(polecenie, " &");
  printf("%s\n", polecenie); /* wydruk kontrolny polecenia */
  system(polecenie);         /* wykonanie polecenia        */
}

int main()
{
  int obraz[MAX][MAX];
  int wymx, wymy, szarosci;

  FILE *plik_we;
  FILE *plik_wy;
  char nazwa[100];
  char wybor[2] = " ";

  printf("Podaj nazwe pliku: ");
  scanf("%s", nazwa);

  plik_we = fopen(nazwa, "r");
  czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
  fclose(plik_we);

  while (wybor[0] != '6')
  {

    printf("\nProste menu: \n");
    printf("\t1 -- Wczytaj nowy plik\n");
    printf("\t2 -- Pokarz orginalny plik\n");
    printf("\t3 -- Negatyw\n");
    printf("\t4 -- Konturowanie\n");
    printf("\t5 -- Rozciaganie histogramu\n");
    printf("\t6 -- Zakoncz dzialanie\n");
    printf("Twoj wybor: ");

    scanf("%1s", wybor);

    switch (wybor[0])
    {
    case '1':
      system("clear");
      printf("\nWybrano Wczytanie nowego pliku\n");
      printf("Podaj nazwe pliku:\n");
      scanf("%s", nazwa);

      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      break;

    case '2':
      system("clear");
      printf("\nWybrano Pokazanie orginalnego pliku\n");

      wyswietl(nazwa);

      break;

    case '3':
      system("clear");
      printf("\nWybrano Negatyw\n");

      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      plik_wy = fopen("negatyw.pgm", "w");
      negatyw(plik_wy, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_wy);
      wyswietl("negatyw.pgm");

      break;

    case '4':
      system("clear");
      printf("\nwybrano Konturowanie\n");

      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      plik_wy = fopen("kontur.pgm", "w");
      kontur(plik_wy, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_wy);
      wyswietl("kontur.pgm");

      break;

    case '5':
      system("clear");
      printf("\nWybrano Rozciaganie histogramu\n");

      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      plik_wy = fopen("rozciaganie_histogramu.pgm", "w");
      rozciaganie_histogramu(plik_wy, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_wy);
      wyswietl("rozciaganie_histogramu.pgm");

      break;

    case '6':
      system("clear");
      printf("\nKoniec programu\n");

      break;

    default:
      system("clear");
      printf("\nBrak obslugi dla wejscia\n");

      break;
    }
  }
}