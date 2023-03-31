#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
#include "modul.h"

#define W_OK 0                /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1 /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4
#define B_BRAKOPCJI -5
#define B_ZLEPRZETWARZANIE -6
#define B_ZLYPLIK -7
#define DL_LINII 1024

/****************************************************************************
 * Funkcja rozpoznaje opcje wywolania programu zapisane w tablicy argv      *
 * i zapisuje je w strukturze opcje                                         *
 * Skladnia opcji wywolania programu                                        *
 * program{[-i nazwa][-o nazwa][-p liczba][-g liczba][-m kolor]             *
 * [-n][-k][-h][-rx][-d]}                                                   *
 *                                                                          *
 * \param[in] argc -l iczba argumentow wywolania wraz z nazwa programu      *
 * \param[in] argv - tablica argumentow wywolania                           *
 * \param[in] opcje - wskaznik na strukture z wywolanymi opcjami            *
 * \param[out] opcje - struktura w ktorej zostana zapisane operacje         *
 * \return - informacja o mozliwym bledzie                                  *
 ****************************************************************************/

int przetwarzaj_opcje(int argc, char **argv, struktura_opcje *opcje)
{

  int i, prog;
  float gamma;
  char *nazwa_pliku_we, *nazwa_pliku_wy;
  int odczyt = 0, zapis = 0;

  /*zerowanie opcji*/
  opcje->plik_we = NULL;
  opcje->plik_wy = NULL;
  opcje->negatyw = 0;
  opcje->konturowanie = 0;
  opcje->progowanie = 0;
  opcje->wyswietlenie = 0;
  opcje->rozciaganie_histogramu = 0;
  opcje->korekcja_gamma = 0;
  opcje->rozmycie_poziome = 0;
  opcje->P3doP2 = 0;
  opcje->czerwono = 0;
  opcje->niebiesko = 0;
  opcje->zielono = 0;

  opcje->plik_wy = stdout; /* na wypadek gdy nie podano opcji "-o" */

  for (i = 1; i < argc; i++)
  {
    if (argv[i][0] != '-') /* blad: to nie jest opcja - brak znaku "-" */
      return B_NIEPOPRAWNAOPCJA;
    switch (argv[i][1])
    {
    case 'i':
    { /* opcja z nazwa pliku wejsciowego */
      odczyt = 1;
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_we = argv[i];
        if (strcmp(nazwa_pliku_we, "-") == 0) /* gdy nazwa jest "-"        */
          opcje->plik_we = stdin;             /* ustwiamy wejscie na stdin */
        else                                  /* otwieramy wskazany plik   */
          opcje->plik_we = fopen(nazwa_pliku_we, "r");
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'o':
    { /* opcja z nazwa pliku wyjsciowego */
      zapis = 1;
      if (++i < argc)
      { /* wczytujemy kolejny argument jako nazwe pliku */
        nazwa_pliku_wy = argv[i];
        opcje->nazwa_nowego = nazwa_pliku_wy;
        if (strcmp(nazwa_pliku_wy, "-") == 0) /* gdy nazwa jest "-"         */
          opcje->plik_wy = stdout;            /* ustwiamy wyjscie na stdout */
        else                                  /* otwieramy wskazany plik    */
          opcje->plik_wy = fopen(nazwa_pliku_wy, "w");
      }
      else
        return B_BRAKNAZWY; /* blad: brak nazwy pliku */
      break;
    }
    case 'p':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc progu */
        if (sscanf(argv[i], "%d", &prog) == 1)
        {
          if (prog < 0 || prog > 100)
          {
            printf("Zla wartosc progu. Poprawny prog 0-100\n");
            return B_BRAKWARTOSCI;
          }
          opcje->progowanie = 1;
          opcje->w_progu = prog;
        }
        else
          return B_BRAKWARTOSCI; /* blad: niepoprawna wartosc */
      }
      else
        return B_BRAKWARTOSCI; /* blad: brak wartosci */
      break;
    }
    case 'g':
    {
      if (++i < argc)
      { /* wczytujemy kolejny argument jako wartosc gamma */
        if (sscanf(argv[i], "%f", &gamma) == 1)
        {
          if (gamma < 0)
          {
            printf("Zla wartosc gamma. Poprawna gamma > 0\n");
            return B_BRAKWARTOSCI;
          }
          opcje->korekcja_gamma = 1;
          opcje->w_gamma = gamma;
        }
        else
          return B_BRAKWARTOSCI; /* blad: niepoprawna wartosc */
      }
      else
        return B_BRAKWARTOSCI; /* blad: brak wartosci */
      break;
    }
    case 'n':
    { /* mamy wykonac negatyw */
      opcje->negatyw = 1;
      break;
    }
    case 'k':
    { /* mamy wykonac konturowanie */
      opcje->konturowanie = 1;
      break;
    }
    case 'h':
    { /* mamy wykonac rozciaganie histogramu */
      opcje->rozciaganie_histogramu = 1;
      break;
    }
    case 'r':
    { /* mamy wykonac rozciaganie poziome */
      if (argv[i][2] != 'x')
      {
        return B_NIEPOPRAWNAOPCJA;
      }
      opcje->rozmycie_poziome = 1;
      break;
    }
    case 'd':
    { /* mamy wyswietlic obraz */
      opcje->wyswietlenie = 1;
      break;
    }
    case 'm':
    { /* mamy wykonac konwersje obrazu */
      if (++i < argc)
      { /* wczytujemy kolejny argument jako kolor do obrobki */
        switch (argv[i][0])
        {
        case 'r':
        {
          opcje->konwertowanie = 1;
          opcje->czerwono = 1;
          break;
        }
        case 'g':
        {
          opcje->konwertowanie = 1;
          opcje->zielono = 1;
          break;
        }
        case 'b':
        {
          opcje->konwertowanie = 1;
          opcje->niebiesko = 1;
          break;
        }
        case 's':
        {
          opcje->P3doP2 = 1;
          break;
        }
        default:
          return B_NIEPOPRAWNAOPCJA; /* blad: niepoprawny argument funkcji  */
          break;
        }
      }
      break;
    }
    default: /* nierozpoznana opcja */
      return B_NIEPOPRAWNAOPCJA;
    } /* koniec switch */
  }   /* koniec for */

  if (odczyt != 1) /* zabezpieczenie gdy nie podamy "i" jako argument */
  {
    fprintf(stderr, "Blad: Nie podano opcji odczytania pliku\n");
    return B_BRAKOPCJI;
  }
  if (zapis != 1) /* zabezpieczenie gdy nie podamy "o" jako argument */
  {
    fprintf(stderr, "Blad: Nie podano opcji zapisania pliku\n");
    return B_BRAKOPCJI;
  }

  if (opcje->plik_we != NULL) /* ok: wej. strumien danych zainicjowany */
    return W_OK;
  else
    return B_BRAKPLIKU; /* blad:  nie otwarto pliku wejsciowego  */
}

/************************************************************************************
 * Funkcja wczytuje obraz PGM lub PPM z pliku do tablicy                            *
 *                                                                                  *
 * \param[in] plik_we uchwyt do pliku z obrazem w formacie                          *
 * \param[out] nr_magiczny - zmienna, pamietajaca format pliku                      *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz                 *
 * \param[out] wym_x - szerokosc obrazka                                            *
 * \param[out] wym_y - wysokosc obrazka                                             *
 * \param[out] szarosci - liczba odcieni szarosci                                   *
 * \return informacja o mozliwym bledzie                                            *
 ************************************************************************************/

int czytaj(struktura_opcje *opcje, obrazek *obraz)
{
  char buf[DL_LINII]; /* bufor pomocniczy do czytania naglowka i komentarzy */
  int znak;           /* zmienna pomocnicza do czytania komentarzy */
  int koniec = 0;     /* czy napotkano koniec danych w pliku */

  /*Sprawdzenie czy podano prawid�owy uchwyt pliku */
  if (opcje->plik_we == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do odczytania pliku\n");
    return B_BRAKPLIKU;
  }

  /* Sprawdzenie "numeru magicznego" - powinien byl P2 lub P3 */
  if (fgets(buf, DL_LINII, opcje->plik_we) == NULL) /* Wczytanie pierwszej linii pliku do bufora */
    koniec = 1;                                     /* Nie udalo sie? Koniec danych! */

  if ((buf[0] != 'P') || ((buf[1] != '2') && (buf[1] != '3')) || koniec)
  { /* Czy jest magiczne "P2" lub "P3"? */
    fprintf(stderr, "Blad: To nie jest plik PGM ani PPM\n");
    return B_ZLYPLIK;
  }
  else
  { /* zapisanie numeru magicznego */
    if (buf[1] == '2')
    {
      obraz->nr_magiczny = 2;
    }
    if (buf[1] == '3')
    {
      obraz->nr_magiczny = 3;
    }
  }

  /* Pominiecie komentarzy */
  do
  {
    if ((znak = fgetc(opcje->plik_we)) == '#')
    {                                                   /* Czy linia rozpoczyna sie od znaku '#'? */
      if (fgets(buf, DL_LINII, opcje->plik_we) == NULL) /* Przeczytaj ja do bufora                */
        koniec = 1;                                     /* Zapamietaj ewentualny koniec danych */
    }
    else
    {
      ungetc(znak, opcje->plik_we); /* Gdy przeczytany znak z poczatku linii */
    }                               /* nie jest '#' zwroc go                 */
  } while (znak == '#' && !koniec); /* Powtarzaj dopoki sa linie komentarza */
                                    /* i nie nastapil koniec danych         */

  /* Pobranie wymiarow obrazu i liczby odcieni szarosci */
  if (fscanf(opcje->plik_we, "%d %d %d", &(obraz->wym_x), &(obraz->wym_y), &(obraz->szarosci)) != 3)
  {
    fprintf(stderr, "Blad: Brak wymiarow obrazu lub liczby stopni szarosci\n");
    return B_ZLYPLIK;
  }

  /* Dostosowuje wymiar tablicy dla obrazka P2 */
  if (obraz->nr_magiczny == 2)
  {
    /* Alokowanie miejsca dla tablicy przechowywujacej obraz */
    obraz->piksele = (int **)malloc(obraz->wym_y * sizeof(int *));
    for (int i = 0; i < obraz->wym_y; i++)
    {
      obraz->piksele[i] = (int *)malloc(obraz->wym_x * sizeof(int));
    }

    /* Pobranie obrazu i zapisanie w tablicy obrazu P2*/
    for (int i = 0; i < obraz->wym_y; i++)
    {
      for (int j = 0; j < obraz->wym_x; j++)
      {

        if (fscanf(opcje->plik_we, "%d", &(obraz->piksele[i][j])) != 1)
        {
          fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
          return B_ZLYPLIK;
        }
      }
    }
  }

  /* Dostosowuje wymiar tablicy dla obrazka P3 */
  if (obraz->nr_magiczny == 3)
  {
    /* Alokowanie miejsca dla tablicy przechowywujacej obraz */
    obraz->piksele = (int **)malloc(obraz->wym_y * sizeof(int *));
    for (int i = 0; i < obraz->wym_y; i++)
    {
      obraz->piksele[i] = (int *)malloc(obraz->wym_x * 3 * sizeof(int));
    }

    /* Pobranie obrazu i zapisanie w tablicy obrazu P2*/
    for (int i = 0; i < obraz->wym_y; i++)
    {
      for (int j = 0; j < 3 * obraz->wym_x; j++)
      {

        if (fscanf(opcje->plik_we, "%d", &(obraz->piksele[i][j])) != 1)
        {
          fprintf(stderr, "Blad: Niewlasciwe wymiary obrazu\n");
          return B_ZLYPLIK;
        }
      }
    }
  }
  return W_OK; /* Czytanie zakonczone sukcesem    */
}

/************************************************************************************
 * Funkcja zapisuje obraz PGM lub PPM do pliku z tablicy                            *
 *                                                                                  *
 * \param[out] plik_wy - uchwyt do pliku w ktorym zostanie zapisany obraz           *
 * \param[in] nr_magiczny - zmienna, pamietajaca format pliku                       *
 * \param[in] piksele - tablica, z ktorej zostanie odczytany obraz                  *
 * \param[in] wym_x - szerokosc obrazka                                             *
 * \param[in] wym_y - wysokosc obrazka                                              *
 * \param[in] szarosci - liczba odcieni szarosci                                    *
 * \return informacja o mozliwym bledzie                                            *
 ************************************************************************************/

int zapisz(struktura_opcje *opcje, obrazek *obraz)
{

  /*Sprawdzenie czy podano prawidlowy uchwyt pliku */
  if (opcje->plik_wy == NULL)
  {
    fprintf(stderr, "Blad: Nie podano uchwytu do zapisania pliku\n");
    return B_BRAKPLIKU;
  }

  /*Zapianie w pliku parametrow zgodnych z formatem */
  if (obraz->nr_magiczny == 2)
  {
    fprintf(opcje->plik_wy, "P2\n");
  }
  if (obraz->nr_magiczny == 3)
  {
    fprintf(opcje->plik_wy, "P3\n");
  }
  fprintf(opcje->plik_wy, "%d %d\n", obraz->wym_x, obraz->wym_y);
  fprintf(opcje->plik_wy, "%d\n", obraz->szarosci);

  if (obraz->nr_magiczny == 2)
  {
    /*Odczytanie obrazu z tablicy i zapisanie go do pliku */
    for (int i = 0; i < obraz->wym_y; i++)
    {
      for (int j = 0; j < obraz->wym_x; j++)
      {
        fprintf(opcje->plik_wy, "%d\t", obraz->piksele[i][j]);
      }
    }
  }

  if (obraz->nr_magiczny == 3)
  {
    /*Odczytanie obrazu z tablicy i zapisanie go do pliku */
    for (int i = 0; i < obraz->wym_y; i++)
    {
      for (int j = 0; j < 3 * obraz->wym_x; j++)
      {
        fprintf(opcje->plik_wy, "%d\t", obraz->piksele[i][j]);
      }
    }
  }

  return W_OK; /*Zwroc wartosc zapisanych pikseli    */
}

/************************************************************************************
 * Funkcja wykonuje operacje negatywu na tabliy z zapisanym obrazem PGM             *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz w negatywie     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 * \param[in]  szarosci - liczba odcieni szarosci                                   *
 ************************************************************************************/

void negatyw(obrazek *obraz)
{
  /*Zapisywanie w tablicy obrazu z negatywem */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      obraz->piksele[i][j] = obraz->szarosci - obraz->piksele[i][j];
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje operacje konturowania na tabliy z zapisanym obrazem PGM         *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 ************************************************************************************/

void kontur(obrazek *obraz)
{
  /*Zapisanie w tablicy obrazu z konturowaniem*/
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      if (((i + 1) < obraz->wym_y) && ((j + 1) < obraz->wym_x))
      {
        int w1 = abs(obraz->piksele[i + 1][j] - obraz->piksele[i][j]);
        int w2 = abs(obraz->piksele[i][j + 1] - obraz->piksele[i][j]);
        obraz->piksele[i][j] = w1 + w2;
      }
      else
      {
        obraz->piksele[i][j] = 0;
      }
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje rozciaganie histogramu na tabliy z zapisanym obrazem PGM        *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 * \param[in]  szarosci - liczba odcieni szarosci                                   *
 ************************************************************************************/

void rozciaganie_histogramu(obrazek *obraz)
{
  int szaroscMax = 0;               /*Zmienna zawierajaca maksymalna wartosc szarosci */
  int szaroscMin = obraz->szarosci; /*Zmienna zawierajaca minimalna wartosc szarosci  */

  /*Wyszukiwanie maksymalnej i minimalnej szarosci */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      if (obraz->piksele[i][j] < szaroscMin)
      {
        szaroscMin = obraz->piksele[i][j];
      }
      if (obraz->piksele[i][j] > szaroscMax)
      {
        szaroscMax = obraz->piksele[i][j];
      }
    }
  }

  /*Zapisanie w tablicy obrazu z rozciagnietym histogramem */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      obraz->piksele[i][j] = (obraz->piksele[i][j] - szaroscMin) * obraz->szarosci / (szaroscMax - szaroscMin);
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje korekcje gamma na tabliy z zapisanym obrazem PGM                *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  w_gamma - parametr z wartoscia gamma                                 *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 * \param[in]  szarosci - liczba odcieni szarosci                                   *
 ************************************************************************************/

void korekcja_gamma(struktura_opcje *opcje, obrazek *obraz)
{

  /*Zapisanie do tablicy obrazu z korekta gamma */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      obraz->piksele[i][j] = pow(obraz->piksele[i][j], (1 / opcje->w_gamma)) / pow(obraz->szarosci, ((1 - opcje->w_gamma) / opcje->w_gamma));
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje rozmycie poziome na tabliy z zapisanym obrazem PGM              *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 ************************************************************************************/

void rozmycie_poziome(obrazek *obraz)
{
  /*Zapisanie do tablicy obrazu z rozmyciem poziomym */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      if ((j - 1 >= 0) && (j + 1 <= obraz->wym_x))
      {
        obraz->piksele[i][j] = (obraz->piksele[i][j - 1] + obraz->piksele[i][j] + obraz->piksele[i][j + 1]) / 3;
      }
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje operacje progowaniana tabliy z zapisanym obrazem PGM            *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  w_progu - parametr z wartoscia progu                                 *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 * \param[in]  szarosci - liczba odcieni szarosci                                   *
 ************************************************************************************/

void progowanie(struktura_opcje *opcje, obrazek *obraz)
{
  int prog = 0;

  /*Wyliczenie progu */
  prog = (obraz->szarosci * opcje->w_progu) / 100;

  /*Zapisanie do tablicy obrazu z wykonanym progowaniem */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      if (obraz->piksele[i][j] <= prog)
      {
        obraz->piksele[i][j] = 0;
      }
      else
      {
        obraz->piksele[i][j] = obraz->szarosci;
      }
    }
  }
}

/************************************************************************************
 * Funkcja wykonuje operacje konwertowania obrazu z formatu PPM do PGM              *
 *                                                                                  *
 * \param[out] piksele - tablica, do ktorej zostanie zapisany obraz po operacji     *
 * \param[out]  nr_magiczny - zmienna, pamietajaca nowy format pliku                *
 * \param[in]  piksele - tablica, z ktorej zostanie pobrany obraz zrodlowy          *
 * \param[in]  nr_magiczny - zmienna, pamietajaca stary format pliku                *
 * \param[in]  wym_x - szerokosc obrazka                                            *
 * \param[in]  wym_y - wysokosc obrazka                                             *
 ************************************************************************************/

void P3doP2(obrazek *obraz)
{
  int a = 0;

  obraz->nr_magiczny = 2; /* Zamiana nr magicznego na .pgm */

  /* Scalanie parametrow r, g, b, poprzez usrednienie */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      obraz->piksele[i][j] = ((obraz->piksele[i][a] + obraz->piksele[i][a + 1] + obraz->piksele[i][a + 2]) / 3);
      a = a + 3;
    }
    a = 0;
  }
  a = 0;
}

void konwersja_kolor(struktura_opcje *opcje, obrazek *obraz)
{
  int r, g, b;
  r = opcje->czerwono;
  g = opcje->zielono;
  b = opcje->niebiesko;

  /* Petla, ktora zostawia tylko wybrane skladowe koloru */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < 3 * obraz->wym_x; j += 3)
    {
      obraz->piksele[i][j] = r * obraz->piksele[i][j];

      obraz->piksele[i][j + 1] = g * obraz->piksele[i][j + 1];

      obraz->piksele[i][j + 2] = b * obraz->piksele[i][j + 2];
    }
  }
}

/************************************************************************************
 * Funkcja wyswietla obraz w pliku o zadanej nazwie, za pomoca programu "display"   *
 *                                                                                  *
 * \param[in] nazwa_nowego obrazu PGM lub PPM ktory ma byc wyswietlony              *
 ************************************************************************************/

void wyswietl(struktura_opcje *opcje)
{
  char polecenie[DL_LINII];

  /* Tworzenie polecenia, ktore wyswietli obraz za pomoca komendy display */
  strcpy(polecenie, "display ");
  strcat(polecenie, opcje->nazwa_nowego);
  strcat(polecenie, " &");
  system(polecenie);
}