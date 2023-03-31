#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Student
{
  string imie;
  string nazwisko;
  int nr_albumu;
  string data_urodzenia;
};

struct BazaStudentow
{
  string nazwa_uczelni;
  vector<Student> studenci;
};

void display_student(Student st)
{
  cout << "imie i nazwisko: " << st.imie << " " << st.nazwisko << endl;
  cout << "Nr albumu: " << st.nr_albumu << endl;
  cout << "Data urodzenia: " << st.data_urodzenia << endl;
}

Student read_student()
{
  Student st;
  cout << "Imie: ";
  cin >> st.imie;
  cout << "Nazwisko: ";
  cin >> st.nazwisko;
  cout << "Nr Albumu: ";
  cin >> st.nr_albumu;
  cout << "Data urodzenia: ";
  cin >> st.data_urodzenia;
  cout << endl;

  return st;
}

void display_all_students(vector<Student> st)
{
  for (int i = 0; i < st.size(); i++)
  {
    display_student(st[i]);
    cout << endl;
  }
}

void add_student(BazaStudentow &uczelnia, Student &st)
{
  uczelnia.studenci.push_back(st);
}

int find_student(BazaStudentow &uczelnia, int indeks)
{
  for (int i = 0; i < uczelnia.studenci.size(); i++)
  {
    if (indeks == uczelnia.studenci[i].nr_albumu)
    {
      return i + 1;
    }
  }

  return -1;
}

int remove_student(BazaStudentow &uczelnia, Student &st)
{
  vector<Student>::iterator it = uczelnia.studenci.begin();
  for (int i = 0; st.nr_albumu != uczelnia.studenci[i].nr_albumu; i++)
  {
    if (i > uczelnia.studenci.size())
    {
      cout << "Brak studenta w bazie do usuniecia" << endl;
      return -1;
    }
    it++;
  }
  uczelnia.studenci.erase(it);
  return 0;
}

int save_students(BazaStudentow &uczelnia, fstream &plik)
{
  plik.open("BazaZapis.txt", ios::out);
  if (!plik.good())
  {
    cout << "Blad zapisu do pliku" << endl;
    return -1;
  }

  for (int i = 0; i < uczelnia.studenci.size(); i++)
  {
    plik << uczelnia.studenci[i].imie << " " << uczelnia.studenci[i].nazwisko << " " << uczelnia.studenci[i].nr_albumu << " " << uczelnia.studenci[i].data_urodzenia << endl;
  }
  plik.close();

  return 0;
}

int load_students(BazaStudentow &uczelnia, fstream &plik)
{
  string indeks;
  plik.open("BazaWczyt.txt", ios::in);
  if (!plik.good())
  {
    cout << "Blad wczytywania z pliku" << endl;
    return -1;
  }

  for (int i = 0; !plik.eof(); i++)
  {
    Student st;

    plik >> st.imie;
    plik >> st.nazwisko;
    plik >> indeks;
    st.nr_albumu = stoi(indeks);
    plik >> st.data_urodzenia;

    uczelnia.studenci.push_back(st);
  }

  plik.close();

  return 0;
}

int main()
{
  Student adam, michal, piotr, agnieszka, daria, aniela, milosz, magda;
  BazaStudentow pwr, uwr;
  fstream plik;

  adam.imie = "Adam";
  adam.nazwisko = "Matusiak";
  adam.nr_albumu = 275460;
  adam.data_urodzenia = "03.05.2002";

  michal.imie = "Michal";
  michal.nazwisko = "Szleszkowski";
  michal.nr_albumu = 275478;
  michal.data_urodzenia = "13.08.2003";

  piotr.imie = "Piotr";
  piotr.nazwisko = "Kowalczyk";
  piotr.nr_albumu = 274678;
  piotr.data_urodzenia = "12.10.2002";

  agnieszka.imie = "Agnieszka";
  agnieszka.nazwisko = "Piertala";
  agnieszka.nr_albumu = 260978;
  agnieszka.data_urodzenia = "01.01.2003";

  daria.imie = "Daria";
  daria.nazwisko = "Jopek";
  daria.nr_albumu = 124653;
  daria.data_urodzenia = "05.07.2001";

  aniela.imie = "Aniela";
  aniela.nazwisko = "Misielska";
  aniela.nr_albumu = 275789;
  aniela.data_urodzenia = "13.12.2002";

  milosz.imie = "Milosz";
  milosz.nazwisko = "Strekowski";
  milosz.nr_albumu = 245231;
  milosz.data_urodzenia = "17.10.2003";

  magda.imie = "Magda";
  magda.nazwisko = "Korzuch";
  magda.nr_albumu = 276789;
  magda.data_urodzenia = "14.09.2002";

  pwr.nazwa_uczelni = "PWr";
  uwr.nazwa_uczelni = "UWr";

  load_students(pwr, plik);

  display_all_students(pwr.studenci);

  return 0;
}