/***************************************************************************************************************
 *                                                                                                             *
 *  Autor: Adam Matusiak                                                                                       *
 *  Data Utworzenia: 30.11.2022                                                                                *
 *  Nazwa programu: Przetwarzanie obrazu 1                                                                     *
 *  Wersja: 1.0v                                                                                               *
 *                                                                                                             *
 *  Charakterystyka:                                                                                           *
 *    Program pobiera obraz w formacie PGM i wykonuje na nim operacja przetwarzania. Operacje wybierane        *
 *    sa poprez uzytkownika z poziomu menu.                                                                    *
 *                                                                                                             *
 *  Charakterystyka danych:                                                                                    *
 *    -Wejsciowych: Obraz w foracie PGM o maksymalnym rozmiarze MAX, liczby reprezentujace funkcje w menu      *
 *    -Wyjsciowych: Przetworzony obraz w formacie PGM w zaleznosci od wybrane funkcji                          *
 *                                                                                                             *
 *  Obsługa Programu:                                                                                          *
 *    Aby program dzialal nalezy wykonywac polecenia zgodne z komunikatami w terminale. Program posiada        *
 *    obsluge bledow. W folderze z programem nalezy umieszczac pliki z obrazem PGM aby mogly zostac wczytane.  *
 *                                                                                                             *
 ***************************************************************************************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

#define MAX 1024      /* Maksymalny rozmiar wczytywanego obrazu */
#define DL_LINII 1024 /* Dlugosc buforow pomocniczych */

/************************************************************************************
 * Funkcja wczytuje obraz PGM z pliku do tablicy                                    *
 *                                                                                  *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie PGM                      *
 * \param[out] obraz tablica, do ktorej zostanie zapisany obraz                     *
 * \param[out] wymx szerokosc obrazka                                               *
 * \param[out] wymy wysokosc obrazka                                                *
 * \param[out] szarosci liczba odcieni szarosci                                     *
 * \return liczba wczytanych pikseli                                                *
 ************************************************************************************/

int czytaj(FILE *plik_we, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do odczytania pliku\n");
    return 0;
  }

  /* Sprawdzenie "numeru magicznego" - powinien byl P2 */
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
  /* Pobranie obrazu i zapisanie w tablicy obraz*/
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {

      if (fscanf(plik_we, "%d", &(obraz[i][j])) != 1)
      {
        fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
        return (0);
      }
    }
  }
  return *wymx * *wymy; /* Czytanie zakonczone sukcesem    */
                        /* Zwroc liczbe wczytanych pikseli */
}

/************************************************************************************
 * Funkcja zapisuje obraz PGM do pliku z tablicy                                    *
 *                                                                                  *
 * \param[out] plik_wy uchwyt do pliku w ktorym zostanie zapisany obraz PGM         *
 * \param[in] obraz tablica, z ktorej zostanie odczytany obraz                      *
 * \param[in] wymx szerokosc obrazu                                                 *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 * \return liczba zapisanych pikseli                                                *
 ************************************************************************************/

int zapisz(FILE *plik_wy, int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{

  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (plik_wy == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do zapisania pliku\n");
    return (0);
  }

  /*Zapianie w pliku parametrow zgodnych z formatem PGM */
  fprintf(plik_wy, "P2\n");
  fprintf(plik_wy, "%d %d\n", *wymx, *wymy);
  fprintf(plik_wy, "%d\n", *szarosci);

  /*Odczytanie obrazu z tablicy i zapisanie go do pliku */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      fprintf(plik_wy, "%d\t", obraz[i][j]);
    }
  }
  return *wymx * *wymx; /*Zwroc wartosc zapisanych pikseli    */
                        /*jesli zapisanie zakonczone sukcesem */
}

/************************************************************************************
 * Funkcja wykonuje operacje negatywu na tabliy z zapisanym obrazem PGM             *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonana operacja negatywu          *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void negatyw(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  /*Zapisywanie w tablicy obrazu z negatywem */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      obraz[i][j] = *szarosci - obraz[i][j];
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje operacje konturowania na tabliy z zapisanym obrazem PGM         *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonana operacja konturowania      *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void kontur(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  /*Zapisanie w tablicy obrazu z konturowaniem*/
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      int w1 = abs(obraz[i + 1][j] - obraz[i][j]);
      int w2 = abs(obraz[i][j + 1] - obraz[i][j]);
      obraz[i][j] = w1 + w2;
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje rozciaganie histogramu na tabliy z zapisanym obrazem PGM        *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonane rozciaganie histogramu     *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void rozciaganie_histogramu(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  int szaroscMax = 0;         /*Zmienna zawierajaca maksymalna wartosc szarosci */
  int szaroscMin = *szarosci; /*Zmienna zawierajaca minimalna wartosc szarosci  */

  /*Wyszukiwanie maksymalnej i minimalnej szarosci */
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

  /*Zapisanie w tablicy obrazu z rozciagnietym histogramem */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      obraz[i][j] = (obraz[i][j] - szaroscMin) * *szarosci / (szaroscMax - szaroscMin);
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje korekcje gamma na tabliy z zapisanym obrazem PGM                *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonana korekcja gamma             *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void korekcja_gamma(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  float gamma = 0;

  printf("Podaj wspolczynnik gamma w zakresie > 0: ");
  scanf("%f", &gamma);

  /*Sprawdzenie czy podano poprawna wartosc parametru gamma */
  if (gamma <= 0)
  {
    while (gamma <= 0)
    {
      printf("Wartosc gamma poza zakresem\n");
      printf("Podaj wspolczynnik gamma w zakresie > 0: ");
      scanf("%f", &gamma);
    }
  }

  /*Zapisanie do tablicy obrazu z korekta gamma */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      obraz[i][j] = pow(obraz[i][j], (1 / gamma)) / pow(*szarosci, ((1 - gamma) / gamma));
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje rozmycie poziome na tabliy z zapisanym obrazem PGM              *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonane rozmycie poziome           *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void rozmycie_poziome(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  int promien = 0;

  /*Odczyt promienia z jakim ma byc rozmyty obraz */
  printf("Podaj promien rozmycia w zakresie 1-3: ");
  scanf("%d", &promien);

  /*Sprawdzenie czy promien jest w poprawnym zakresie */
  if ((promien < 1) || (promien > 3))
  {
    while ((promien < 1) || (promien > 3))
    {
      printf("Wartosc gamma poza zakresem\n");
      printf("Podaj wspolczynnik gamma w zakresie > 0: ");
      scanf("%d", &promien);
    }
  }

  /*Zapisanie do tablicy obrazu z rozmyciem poziomym */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      if ((j - promien >= 0) && (j + promien <= *wymx))
      {
        /*Wykonanie rozmycia w zaleznosci od wybranego promienia */
        switch (promien)
        {
        case 1:
          obraz[i][j] = (obraz[i][j - 1] + obraz[i][j] + obraz[i][j + 1]) / 3;
          break;
        case 2:
          obraz[i][j] = (obraz[i][j - 2] + obraz[i][j - 1] + obraz[i][j] + obraz[i][j + 1] + obraz[i][j + 2]) / 5;
          break;
        case 3:
          obraz[i][j] = (obraz[i][j - 3] + obraz[i][j - 2] + obraz[i][j - 1] + obraz[i][j] + obraz[i][j + 1] + obraz[i][j + 2] + obraz[i][j + 3]) / 7;
          break;
        }
      }
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje operacje progowaniana tabliy z zapisanym obrazem PGM            *
 *                                                                                  *
 * \param[out] obraz tablica, w ktorej zostanie wykonane progowanie                 *
 * \param[in] wymx szerokosc obrazka                                                *
 * \param[in] wymy wysokosc obrazka                                                 *
 * \param[in] szarosci liczba odcieni szarosci                                      *
 ************************************************************************************/

void progowanie(int obraz[MAX][MAX], int *wymx, int *wymy, int *szarosci)
{
  int wartosc = 0;
  int prog = 0;

  /*Wczytanie wartosci progu */
  printf("Podaj wartosc Progu w zakresie 0-100 procent: ");
  scanf("%d", &wartosc);

  /*Sprawdzenie czy wartosc jest w poprawnym zakresie */
  if ((wartosc < 0) || (wartosc > 100))
  {
    while ((wartosc < 0) || (wartosc > 100))
    {
      printf("Wartosc progu poza zakresem\n");
      printf("Podaj wartosc Progu w zakresie 0-100 procent: ");
      scanf("%d", &wartosc);
    }
  }

  /*Wyliczenie progu */
  prog = (*szarosci * wartosc) / 100;

  /*Zapisanie do tablicy obrazu z wykonanym progowaniem */
  for (int i = 0; i < *wymy; i++)
  {
    for (int j = 0; j < *wymx; j++)
    {
      if (obraz[i][j] <= prog)
      {
        obraz[i][j] = 0;
      }
      else
      {
        obraz[i][j] = *szarosci;
      }
    }
  }
}

/************************************************************************************
 * Funkcja wyswietlajaca obraz PGM                                                  *
 *                                                                                  *
 * \param[in] n_pliku nazwa obrazu PGM ktory ma byc wyswietlony                     *
 ************************************************************************************/

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
  int obraz[MAX][MAX];      /*Tablica w ktorej bedzie przechowywany obraz PGM */
  int wymx, wymy, szarosci; /*Parametry obrazu*/
  int odczytano = 0;
  int zapisano = 0;

  FILE *plik_we;
  FILE *plik_wy;

  char nazwa[100];          /*Nazwa pliku do odczytu */
  char nowaNazwa[DL_LINII]; /*Nazwa w ktorym zostanie zapisany obraz */
  char wybor[2] = "";

  /*Wczytanie nazwy pliku do otwarcia */
  system("clear");
  printf("Podaj nazwe pliku z obrazem PGM: ");
  scanf("%s", nazwa);

  /*Odczytanie pliku z obrazem PGM */
  plik_we = fopen(nazwa, "r");
  odczytano = czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);

  /*Sprawdzenie czy otrzymano prawidlowy plik */
  if (odczytano != 0)
  {
    fclose(plik_we);
  }

  /*Ponowne wczytanie pliku jesli poprzedni plik byl nie prawidlowy */
  if (odczytano == 0)
  {
    while (odczytano == 0)
    {
      /*Wczytanie nazwy pliku do otwarcia */
      printf("Podaj nazwe pliku z obrazm PGM: ");
      scanf("%s", nazwa);

      /*Odczytanie pliku z obrazem PGM */
      plik_we = fopen(nazwa, "r");
      odczytano = czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);

      /*Sprawdzenie czy otrzymano prawidlowy plik */
      if (odczytano != 0)
      {
        fclose(plik_we);
      }
    }
  }

  while (wybor[0] != '9')
  {
    /*Wyswietlenie menu */
    printf("\nProste menu: \n");
    printf("\t1 -- Wczytaj nowy plik\n");
    printf("\t2 -- Pokaz orginalny plik\n");
    printf("\t3 -- Negatyw\n");
    printf("\t4 -- Konturowanie\n");
    printf("\t5 -- Rozciaganie histogramu\n");
    printf("\t6 -- Korekcja gamma\n");
    printf("\t7 -- Rozmycie poziome\n");
    printf("\t8 -- Progowanie\n");
    printf("\t9 -- Zakoncz dzialanie\n");
    printf("Twoj wybor: ");

    scanf("%1s", wybor);

    /*Konstrukcja menu */
    switch (wybor[0])
    {
    case '1':
      system("clear");
      printf("\nWybrano Wczytanie nowego pliku\n");

      printf("Podaj nazwe pliku z obrazem PGM: ");
      scanf("%s", nazwa);

      /*Odczytanie pliku z obrazem PGM */
      plik_we = fopen(nazwa, "r");
      odczytano = czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);

      /*Sprawdzenie czy otrzymano prawidlowy plik */
      if (odczytano != 0)
      {
        fclose(plik_we);
      }

      /*Ponowne wczytanie pliku jesli poprzedni plik byl nie prawidlowy */
      if (odczytano == 0)
      {
        while (odczytano == 0)
        {
          /*Wczytanie nazwy pliku do otwarcia */
          printf("Podaj nazwe pliku z obrazm PGM: ");
          scanf("%s", nazwa);

          /*Odczytanie pliku z obrazem PGM */
          plik_we = fopen(nazwa, "r");
          odczytano = czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);

          /*Sprawdzenie czy otrzymano prawidlowy plik */
          if (odczytano != 0)
          {
            fclose(plik_we);
          }
        }
      }
      break;

    case '2':
      system("clear");
      printf("\nWybrano Pokazanie orginalnego pliku\n");

      wyswietl(nazwa);

      break;

    case '3':
      system("clear");
      printf("\nWybrano Negatyw\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "negatyw_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        negatyw(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '4':
      system("clear");
      printf("\nwybrano Konturowanie\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "kontur_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        kontur(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '5':
      system("clear");
      printf("\nWybrano Rozciaganie histogramu\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "roz_his_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        rozciaganie_histogramu(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '6':
      system("clear");
      printf("Wybrano korekcje gamma\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "kor_gam_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        korekcja_gamma(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '7':
      system("clear");
      printf("Wybrano rozmycie poziome\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "roz_poz_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        rozmycie_poziome(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '8':
      system("clear");
      printf("Wybrano progowanie\n");

      /*Odczytywanie plikuxz obrazem */
      plik_we = fopen(nazwa, "r");
      czytaj(plik_we, obraz, &wymx, &wymy, &szarosci);
      fclose(plik_we);

      /*Stworzenie nazwy nowego pliku*/
      strcpy(nowaNazwa, "prog_");
      strcat(nowaNazwa, nazwa);

      /*Otworzeie pliku do zapisu */
      plik_wy = fopen(nowaNazwa, "w");

      /*Wykonanie operacji jesli podano poprawny plik */
      if (plik_wy != NULL)
      {
        progowanie(obraz, &wymx, &wymy, &szarosci);
      }
      zapisano = zapisz(plik_wy, obraz, &wymx, &wymy, &szarosci);
      if (zapisano != 0)
      {
        fclose(plik_wy);
        wyswietl(nowaNazwa);
      }

      break;

    case '9':
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
