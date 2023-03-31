/***************************************************************************************************************
 *                                                                                                             *
 *  Autor: Adam Matusiak                                                                                       *
 *  Data Utworzenia: 11.12.2023                                                                                *
 *  Nazwa programu: Przetwarzanie obrazu 2                                                                     *
 *  Wersja: 1.0v                                                                                               *
 *                                                                                                             *
 *  Charakterystyka:                                                                                           *
 *    Program pobiera obraz w formacie PGM lub PPM i wykonuje na nim operacja przetwarzania. Operacje          *
 *    wybierane sa poprez uzytkownika z poziomu wiersza polecen. Do programu został wykorzystany fragment      *
 *    kodu z pliku opcje.c, ktory zostal dostarczony przez Dr. Muszynskiego.                                   *
 *                                                                                                             *
 *  Charakterystyka danych:                                                                                    *
 *    -Wejsciowych: Obraz w foracie PGM lub PPM, liczby reprezentujace funkcje w menu                          *
 *    -Wyjsciowych: Przetworzony obraz w formacie PGM lub PPM w zaleznosci od wybrane funkcji                  *
 *                                                                                                             *
 *  Obsługa Programu:                                                                                          *
 *    Aby program dzialal nalezy wykonywac polecenia zgodne z komunikatami w terminale. Program posiada        *
 *    obsluge bledow. W folderze z programem nalezy umieszczac pliki z obrazem aby mogly zostac wczytane.      *
 *                                                                                                             *
 ***************************************************************************************************************/

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

int main(int argc, char **argv)
{
  obrazek obraz;         /* Zmienne z parametrami obrazu */
  struktura_opcje opcje; /* Zmienne z opcjami przetwarzania */
  int kod_bledu = 0;

  kod_bledu = przetwarzaj_opcje(argc, argv, &opcje);

  if (kod_bledu != 0)
  {
    printf("Blad nr %d\n", kod_bledu);
  }
  if (kod_bledu == 0)
  {

    /* Wczytanie obrazu do edycji */
    czytaj(&opcje, &obraz);
    fclose(opcje.plik_we);

    if (opcje.P3doP2 == 1 && obraz.nr_magiczny == 3) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      P3doP2(&obraz);
    }

    if (opcje.konwertowanie == 1 && obraz.nr_magiczny == 3) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      konwersja_kolor(&opcje, &obraz);
    }
    if (opcje.konwertowanie == 1 && obraz.nr_magiczny == 2)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.rozciaganie_histogramu == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      rozciaganie_histogramu(&obraz);
    }
    if (opcje.rozciaganie_histogramu == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.korekcja_gamma == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      korekcja_gamma(&opcje, &obraz);
    }
    if (opcje.korekcja_gamma == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.progowanie == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      progowanie(&opcje, &obraz);
    }
    if (opcje.progowanie == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.rozmycie_poziome == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      rozmycie_poziome(&obraz);
    }
    if (opcje.rozmycie_poziome == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.negatyw == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      negatyw(&obraz);
    }
    if (opcje.negatyw == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.konturowanie == 1 && obraz.nr_magiczny == 2) /* Sprawdzanie czy przetwarzanie jest zgodne z typem obrazu */
    {
      kontur(&obraz);
    }
    if (opcje.konturowanie == 1 && obraz.nr_magiczny == 3)
    {
      fprintf(stderr, "Blad: zle przetwarzanie\n");
      return B_ZLEPRZETWARZANIE;
    }

    if (opcje.wyswietlenie == 1)
    { /* Wyswietlenie i zapisanie obrazu */
      if (opcje.plik_wy == stdout)
      {
        if (obraz.nr_magiczny == 2)
        {
          system("touch temp_magiczny2.pgm");
          opcje.nazwa_nowego = "temp_magiczny2.pgm";
          opcje.plik_wy = fopen(opcje.nazwa_nowego, "w");
          zapisz(&opcje, &obraz);
          fclose(opcje.plik_wy);
          wyswietl(&opcje);
          opcje.plik_wy = stdout;
          zapisz(&opcje, &obraz);
          system("rm temp_magiczny2.pgm");
        }
        if (obraz.nr_magiczny == 3)
        {
          system("touch temp_magiczny3.ppm");
          opcje.nazwa_nowego = "temp_magiczny3.ppm";
          opcje.plik_wy = fopen(opcje.nazwa_nowego, "w");
          zapisz(&opcje, &obraz);
          fclose(opcje.plik_wy);
          wyswietl(&opcje);
          opcje.plik_wy = stdout;
          zapisz(&opcje, &obraz);
          system("rm temp_magiczny3.ppm");
        }
      }
      else
      {
        zapisz(&opcje, &obraz);
        fclose(opcje.plik_wy);
        wyswietl(&opcje);
      }
    }
    if (opcje.wyswietlenie == 0)
    { /* Zapisanie obrazu */
      zapisz(&opcje, &obraz);
      fclose(opcje.plik_wy);
    }
  }

  /* Zwalniam pamiec tablicy dynamicznej */
  for (int i = 0; i < obraz.wym_y; i++)
  {
    free(obraz.piksele[i]);
  }
  free(obraz.piksele);

  return 0;
} /*koniec if (kodbledu==0)*/
