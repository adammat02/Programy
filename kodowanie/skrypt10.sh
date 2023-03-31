#!/bin/bash

# Sprawdzenie czy zostały podane argumenty z nazwą katalogu i rozmiarem 
if [ "$#" != "2" ]; then
  echo "Nie prawidlowa ilosc argumentow"
  exit 1
fi

# Zdefiniowanie zmiennych
dir=$1
rozmiar=$2

# Stworzenie katalogu tymczasowego
mkdir archiwum

# Sprawdzam czy w katalogu sa pliki png
if find "$dir" -name "*.png" | grep -iq "$dir";
then
 # Szukanie wszystkich plikow png w katalogu
 for plik in $dir/*.[pP][nN][gG];
 do
   #Kopiowanie, zmiana nazwy, zmiana rozmiaru i przeniesienie do katalogu
   nnazwa="`echo ${plik%.*}_kopia.png | tr '[:blank:]' '[_]'`"
   cp "$plik" "$nnazwa"
   convert "$nnazwa" -resize "$rozmiar" "$nnazwa"
   mv "$nnazwa" archiwum 
 done
else
 echo "Brak plików png w katalogu" 
fi 

# Sprawdzam czy w pliku są pliki jpeg
if find "$dir" -name "*.jpeg" | grep -iq "$dir";
then
 # Szukanie wszystkich plikow png w katalogu
 for plik in $dir/*.[jJ][pP][eE][gG];
 do
   #Kopiowanie, zmiana nazwy, zmiana rozmiaru i przeniesienie do katalogu
   nnazwa="`echo ${plik%.*}_kopia.jpeg | tr '[:blank:]' '[_]'`"
   cp "$plik" "$nnazwa"
   convert "$nnazwa" -resize "$rozmiar" "$nnazwa"
   mv "$nnazwa" archiwum 
 done
else
 echo "Brak plików jpeg w katalogu"
fi

# Tworzenie archiwum z katalogu oraz usunięcie katalogu tymczasowego
tar -czf zdjęcia.tar.gz archiwum
rm -r archiwum



