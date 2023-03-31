#include <stdio.h>
#include <stdlib.h>

/* Struktura przechowywująca informacje o obrazie */
typedef struct
{
  int wym_x, wym_y, szarosci;
  int **piksele;
} t_obraz;

/* Przykładowa funkcja czytająca plik */
int czytaj(FILE *plik_we, t_obraz *obraz)
{
  /* Wczytanie parametrów obrazu do struktury */
  fscanf(plik_we, "%d", &(obraz->wym_x));
  fscanf(plik_we, "%d", &(obraz->wym_y));
  fscanf(plik_we, "%d", &(obraz->szarosci));

  /* Alokaca dynamicznej tablicy dwuwymiarowej*/
  obraz->piksele = malloc(obraz->wym_y * sizeof(int));
  for (int i = 0; i < obraz->wym_y; i++)
  {
    obraz->piksele[i] = malloc(obraz->wym_x * sizeof(int));
  }

  /* Wczytanie wartosci do tablicy */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      fscanf(plik_we, "%d", &(obraz->piksele[i][j]));
    }
  }
}

int main()
{
  t_obraz obrazek;
  FILE *plik_we;

  /* Odczytanie z pliku */
  czytaj(plik_we, &obrazek);

  /* Wypisanie zawartosci tablicy */
  for (int i = 0; i < obrazek.wym_y; i++)
  {
    for (int j = 0; j < obrazek.wym_x; j++)
    {
      printf("%d\t", obrazek.piksele[i][j]);
    }
  }

  /* Zwolnienie pamieci przeznaczonej na tablice tablicy */
  for (int i = 0; i < obrazek.wym_y; i++)
  {
    free(obrazek.piksele[i]);
  }
  free(obrazek.piksele);

  return 0;
}
