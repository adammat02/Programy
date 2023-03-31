#define W_OK 0                /* wartosc oznaczajaca brak bledow */
#define B_NIEPOPRAWNAOPCJA -1 /* kody bledow rozpoznawania opcji */
#define B_BRAKNAZWY -2
#define B_BRAKWARTOSCI -3
#define B_BRAKPLIKU -4
#define B_BRAKOPCJI -5
#define B_ZLEPRZETWARZANIE -6
#define B_ZLYPLIK -7
#define DL_LINII 1024

typedef struct
{ /* struktura do przechowania parametro obrazu */
  int nr_magiczny;
  int wym_x;
  int wym_y;
  int szarosci;
  int **piksele;
} obrazek;

typedef struct
{
  FILE *plik_we, *plik_wy;                                                                                       /* uchwyty do pliku wej. i wyj. */
  int negatyw, progowanie, konturowanie, rozciaganie_histogramu, korekcja_gamma, rozmycie_poziome, wyswietlenie; /* opcje przetwarzania */
  int P3doP2, konwertowanie, czerwono, niebiesko, zielono;                                                       /* opcje do konwersji kolorow */
  int w_progu;                                                                                                   /* prog do progowania */
  float w_gamma;                                                                                                 /* gamma do korekcji gamma */
  char *nazwa_nowego;                                                                                            /* bufor nazwy pliku zapisu */
} struktura_opcje;

int przetwarzaj_opcje(int argc, char **argv, struktura_opcje *opcje);

int czytaj(struktura_opcje *opcje, obrazek *obraz);

int zapisz(struktura_opcje *opcje, obrazek *obraz);

void negatyw(obrazek *obraz);

void kontur(obrazek *obraz);

void rozciaganie_histogramu(obrazek *obraz);

void korekcja_gamma(struktura_opcje *opcje, obrazek *obraz);

void rozmycie_poziome(obrazek *obraz);

void progowanie(struktura_opcje *opcje, obrazek *obraz);

void P3doP2(obrazek *obraz);

void konwersja_kolor(struktura_opcje *opcje, obrazek *obraz);

void wyswietl(struktura_opcje *opcje);
