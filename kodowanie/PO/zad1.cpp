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


void display_student(Student stu)
{
    cout << "imie i nazwisko: " << stu.imie << " " << stu.nazwisko << endl;
    cout << "Nr albumu: " << stu.nr_albumu << endl;
    cout << "Data urodzenia: " << stu.data_urodzenia << endl;
}


Student read_student()
{
    Student stu;
    cout << "Imie: ";
    cin >> stu.imie;
    cout << "Nazwisko: ";
    cin >> stu.nazwisko;
    cout << "Nr Albumu: ";
    cin >> stu.nr_albumu;
    cout << "Data urodzenia: ";
    cin >> stu.data_urodzenia;
    cout << endl;

    return stu;
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


int load_students(BazaStudentow &uczelnia, fstream &plik)
{
    string indeks;
    plik.open("Baza.txt", ios::in);
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


int save_students(BazaStudentow &uczelnia, fstream &plik)
{
    plik.open("Baza.txt", ios::out);
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



int main()
{

    cout << "ETAP 1" << endl;
    Student adam, michal;

    adam.imie = "Adam";
    adam.nazwisko = "Matusiak";
    adam.nr_albumu = 275460;
    adam.data_urodzenia = "03.05.2002";

    michal.imie = "Michal";
    michal.nazwisko = "Szleszkowski";
    michal.nr_albumu = 275478;
    michal.data_urodzenia = "13.08.2003";

    display_student(adam);
    cout << endl;
    display_student(michal);
    cout << endl;

    Student nowy_student = read_student();
    display_student(nowy_student);
    cout << endl;

    cout << "ETAP 2:" << endl;

    Student piotr,
        agnieszka, daria, aniela, milosz, magda;

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

    vector<Student> st1 = {adam, michal, piotr, agnieszka, daria};
    vector<Student> st2 = {aniela, milosz, magda};

    cout << "Zawartosc pierwszej tablicy: " << endl
         << endl;
    display_all_students(st1);

    cout << "Zawrtosc drugiej tablicy: " << endl
         << endl;
    display_all_students(st2);

    return 0;
}