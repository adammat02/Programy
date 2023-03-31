#include <stdio.h>
#include <stdlib.h>

typedef struct
{
  int wym_x, wym_y, odcieni;
  void *piksele;
} t_obraz;

/* Przykładowa funkcja */
int czytaj(FILE *plik_we, t_obraz *obraz)
{
  /* Wczytanie parametrów obrazu do struktury */
  fscanf(plik_we, "%d", &(obraz->wym_x));
  fscanf(plik_we, "%d", &(obraz->wym_y));
  fscanf(plik_we, "%d", &(obraz->odcieni));

  /* Rezerwuje potrzebną ilość miejsca na tablice i przypisuje ją do struktury t_obraz */
  obraz->piksele = malloc(obraz->wym_x * obraz->wym_y * sizeof(int));

  /* Tworzę zmienną wskaźnikową do tablicy dwuwymiarowej */
  int(*tablica)[obraz->wym_x];

  /* Inicjuje tablice dwuwymiarową */
  tablica = (int(*)[obraz->wym_x])obraz->piksele;

  /* Korzystam z tablicy jak ze zwykłej statycznej */
  for (int i = 0; i < obraz->wym_y; i++)
  {
    for (int j = 0; j < obraz->wym_x; j++)
    {
      fscanf(plik_we, "%d", &(tablica[i][j]));
    }
  }
}
