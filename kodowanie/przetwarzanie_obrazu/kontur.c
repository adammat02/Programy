#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX 512       /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */

void czytaj(FILE *plik_we, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */
  int i, j;

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do pliku\n");
  }

  /* Sprawdzenie "numeru magicznego" - powinien by� P2 */
  if (fgets(buf, DL_LINII, plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                              /* Nie udalo sie? Koniec danych! */

  if ((buf[0] != 'P') || (buf[1] != '2') || koniec)
  { /* Czy jest magiczne "P2"? */
    fprintf(stderr, "Blad: To nie jest plik PGM\n");
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
  }
  /* Pobranie obrazu i zapisanie w tablicy obraz_pgm*/
  for (i = 0; i < *wymy; i++)
  {
    for (j = 0; j < *wymx; j++)
    {

      if (fscanf(plik_we, "%d", &(obraz[i][j])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
      }
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
  int wymx, wymy, odcieni;

  int odczytano = 0;
  FILE *plik_we;
  FILE *plik_wy;
  char nazwa[100];

  /* Wczytanie zawartosci wskazanego pliku do pamieci */
  printf("Podaj nazwe pliku:\n");
  scanf("%s", nazwa);
  plik_we = fopen(nazwa, "r");

  if (plik_we != NULL)
  { /* co spowoduje zakomentowanie tego warunku */
    czytaj(plik_we, obraz, &wymx, &wymy, &odcieni);
    fclose(plik_we);
  }

  plik_wy = fopen("kontur.pgm", "w");
  kontur(plik_wy, obraz, &wymx, &wymy, &odcieni);
  fclose(plik_wy);

  wyswietl("kontur.pgm");
}