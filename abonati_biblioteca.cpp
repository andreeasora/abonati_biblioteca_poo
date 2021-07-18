#include <iostream>
#include <stdlib.h> ///permite executia functiei system(...)
#include <time.h> ///folosita pentru aflarea datei curente
using namespace std;
class Persoana
{
   protected: ///date membre protected pentru ca avem mostenire
       string nume;
       string cnp;
       static int n; ///variabila statica pentru a numara cate obiecte avem declarate
   public:
       Persoana();
       Persoana(string, string);
       Persoana(const Persoana&);
       virtual ~Persoana(); ///destructor virtual-late binding
       virtual void citire(istream &in); ///citire virtuala-late binding
       virtual void afisare(ostream &out); ///afisare virtuala-late binding
       friend istream& operator>>(istream&, Persoana&); ///supraincarcare citire
       friend ostream& operator<<(ostream&, Persoana&); ///supraincarcare afisare
       Persoana& operator=(const Persoana&); ///supraincarcare egal
       static void NumarObiecte() ///metoda statica pentru afisarea numarului de obiecte
       {
           cout << "Numar obiecte: " << n;
       }
};

int Persoana::n; ///declaram variabila statica

Persoana::Persoana() ///constructor fara parametrii
{
    nume = "";
    cnp = "";
    n++;
}

Persoana::Persoana(string Nume, string Cnp) ///constructor cu parametrii
{
    nume = Nume;
    cnp = Cnp;
    n++;
}

Persoana::Persoana(const Persoana &p) ///constructor de copiere
{
    nume = p.nume;
    cnp = p.cnp;
    n = p.n;
}

Persoana::~Persoana() ///destructor
{
    nume = "";
    cnp = "";
    n--;
}

void Persoana::citire(istream &in)
{
    cout << "CNP: ";
    string z;
    in >> z;
    int ok = 1;
    if (z.length() != 13)
        {
          cout << "Eroare, CNP-ul unei persoane trebuie sa aiba 13 cifre!" << endl;
          exit(EXIT_FAILURE);
        }
    else
    {
      for (unsigned int i = 0; i < z.length(); i++)
          if (z[i]<'0' || z[i]>'9')
               ok=0;
      if (ok==0)
      {
        cout << "Eroare, CNP-ul unei persoane trebuie sa contina doar cifre!" << endl;
        exit(EXIT_FAILURE);
      }
      else
         cnp=z;
    }
    cout << "Nume: ";
    in.get();
    string x;
    getline(in,x);
    nume = x;
}

void Persoana::afisare(ostream &out)
{
    out << "Nume: " << nume << "\n";
    out << "CNP: " << cnp << "\n";
}

istream& operator>>(istream& in, Persoana& p)
{
    p.citire(in);
    return in;
}

ostream& operator<<(ostream& out, Persoana& p)
{
    p.afisare(out);
    return out;
}

Persoana& Persoana::operator=(const Persoana &p)
{
    nume = p.nume;
    cnp = p.cnp;
    n = p.n;
    return *this;
}

class Abonat:public Persoana
{
    private: ///date membre private pentru ca nu mai derivam din clasa Abonat
       int nrMaxCarti;
       int nrCartiImprumutate;
       int pretAbonament;
    public:
       Abonat();
       Abonat(string, string, int, int, int);
       Abonat(const Abonat&, const Persoana&);
       ~Abonat();
       void citire(istream &in);
       void afisare(ostream &out);
       void varsta();
       Abonat& operator=(const Abonat&);
};

Abonat::Abonat():Persoana() ///apelam constructorul din baza
{
    nrMaxCarti = 0;
    nrCartiImprumutate = 0;
    pretAbonament = 0;
}

Abonat::Abonat(string Nume, string Cnp, int nrmaximcarti, int nrcartiimprumutate, int pret):Persoana(Nume,Cnp) ///apelam constructorul din baza
{
    nrMaxCarti = nrmaximcarti;
    nrCartiImprumutate = nrcartiimprumutate;
    pretAbonament = pret;
}

Abonat::Abonat(const Abonat &a, const Persoana &p):Persoana(p) ///apelam constructorul de copiere din baza
{
    nrMaxCarti = a.nrMaxCarti;
    nrCartiImprumutate = a.nrCartiImprumutate;
    pretAbonament = a.pretAbonament;
}

Abonat::~Abonat()
{
    nrMaxCarti = 0;
    nrCartiImprumutate = 0;
    pretAbonament = 0;
}

void Abonat::citire(istream &in)
{
    Persoana::citire(in); ///apelam citirea din baza
    cout << "Introduceti pretul abonamentului: "; ///citim restul de informatii
    in >> pretAbonament;
    cout << "Introduceti numarul maxim de carti: ";
    in >> nrMaxCarti;
    if (nrMaxCarti > pretAbonament)
        {
            cout << "Invalid, numarul maxim de carti trebuie sa fie mai mic decat pretul abonamentului! \n";
            exit(EXIT_FAILURE);
        }
    else{ cout << "Introduceti numarul de carti imprumutate: ";
          in >> nrCartiImprumutate;
          if (nrCartiImprumutate > nrMaxCarti)
           {
             cout << "Invalid, numarul de carti imprumutate trebuie sa fie mai mic decat numarul maxim de carti! \n";
             exit(EXIT_FAILURE);
           }
         }
}

void Abonat::afisare(ostream &out)
{
    Persoana::afisare(out); ///apelam afisarea din baza
    out << "Numarul maxim de carti: "; ///afisam restul de informatii
    out << nrMaxCarti << "\n";
    out << "Numarul de carti imprumutate: ";
    out << nrCartiImprumutate << "\n";
    out << "Pretul abonamentului: ";
    out << pretAbonament << "\n";
    out << "Persoana are varsta de ";
    varsta();
    out << " ani! \n";
}

void Abonat::varsta()
{
    time_t now = time(0); ///aflam data curenta
    string dt = ctime(&now); ///dt = "Fri Apr 09 11:45:10 2021" -- exemplu de output
    int an_curent = 0, luna_curenta, zi_curenta = 0;
    string luna;
    luna = dt.substr(4,3);
    if (luna == "Jan")  ///initializam luna curenta in functie de data returnata
        luna_curenta = 1;
    else if (luna == "Feb")
          luna_curenta = 2;
         else if (luna == "Mar")
                luna_curenta = 3;
               else if (luna == "Apr")
                     luna_curenta = 4;
                    else if (luna == "May")
                           luna_curenta = 5;
                         else if (luna == "Jun")
                              luna_curenta = 6;
                              else if (luna == "Jul")
                                   luna_curenta = 7;
                                   else if (luna == "Aug")
                                       luna_curenta = 8;
                                        else if (luna == "Sep")
                                             luna_curenta = 9;
                                             else if(luna == "Oct")
                                                  luna_curenta = 10;
                                                else if (luna == "Nov")
                                                     luna_curenta = 11;
                                                    else luna_curenta = 12;
    an_curent = an_curent*10 + (dt[22] - '0'); ///convertim in int anul curent
    an_curent = an_curent*10 + (dt[23] - '0');
    zi_curenta = zi_curenta*10 + (dt[8] - '0'); ///convertim in int ziua curenta
    zi_curenta = zi_curenta*10 + (dt[9] - '0');
    int an_nastere, luna_nastere, zi_nastere;
    an_nastere = cnp[1] - '0'; ///convertim in int anul nasterii
    an_nastere = an_nastere*10 + (cnp[2] - '0');
    luna_nastere = cnp[3] - '0'; ///convertim in int luna nasterii
    luna_nastere = luna_nastere*10 + (cnp[4] - '0');
    zi_nastere = cnp[5] - '0'; ///convertim in int ziua nasterii
    zi_nastere = zi_nastere*10 + (cnp[6] - '0');
    if (luna_nastere == luna_curenta) ///daca e nascut in luna curenta, ne intereseaza si comparatia cu ziua nasterii/ziua curenta
    {
        if (an_nastere > an_curent && zi_nastere <= zi_curenta)
            cout << an_curent + (100 - an_nastere);
        else if (an_nastere > an_curent && zi_nastere > zi_curenta)
              cout << an_curent + (100 - an_nastere) - 1;
        if (an_nastere < an_curent && zi_nastere <= zi_curenta)
            cout << an_curent - an_nastere;
        else if (an_nastere < an_curent && zi_nastere > zi_curenta)
              cout << an_curent - an_nastere - 1;
        if (an_nastere == an_curent)
            cout << 0;
    }
    else
    {
    if (an_nastere > an_curent && luna_nastere < luna_curenta) ///daca anul nasterii e mai mare decat anul curent => e nascut inainte de 2000
       cout << an_curent + (100 - an_nastere);
    else if (an_nastere > an_curent  && luna_nastere > luna_curenta)
           cout << an_curent + (100 - an_nastere) - 1;
         else if (an_nastere < an_curent && luna_nastere < luna_curenta) ///daca anul nasterii e mai mic decat anul curent => e nascut dupa 2000
                cout << an_curent - an_nastere;
              else
                cout << an_curent - an_nastere - 1;
    if (an_nastere == an_curent)
        cout << 0;
    }
}

Abonat& Abonat::operator=(const Abonat &ab)
{
    Persoana::operator = (ab);
    nrMaxCarti = ab.nrMaxCarti;
    nrCartiImprumutate = ab.nrCartiImprumutate;
    pretAbonament = ab.pretAbonament;
    return *this;
}

class dosar ///vom retine informatiile celor n abonati
{
    private: ///date membre private
       Abonat **p;
       int nr;
    public:
       dosar();
       dosar(Abonat*, int);
       dosar(const dosar&);
       ~dosar();
       void afiseaza(ostream &out);
       friend ostream& operator<<(ostream&, dosar&);
       dosar& operator=(const dosar&);
};

dosar::dosar()
{
    p = NULL;
    nr = 0;
}

dosar::dosar(Abonat *v, int Nr)
{
    nr = Nr;
    p = new Abonat*[nr];
    for(int i = 0; i < nr; i++)
    {
        p[i] = new Abonat(v[i]);
    }
}

dosar::dosar(const dosar &D)
{
    p = D.p;
    nr = D.nr;
}

dosar::~dosar()
{
    if(p != NULL)
    {
        for(int i = 0; i < nr; i++)
        {
            if(p[i] != NULL)
                delete p[i];
        }
        delete p;
    }
    p = NULL;
    nr = 0;
}

void dosar::afiseaza(ostream &out)
{
    for (int i = 0; i < nr; i++)
        if (p[i] != NULL)
          out << *p[i] << endl;
}

ostream& operator<<(ostream &out, dosar &d)
{
    d.afiseaza(out);
    return out;
}

dosar& dosar::operator=(const dosar &D)
{
    p = D.p;
    nr = D.nr;
    return *this;
}

void menu_output()
{
    cout << "Nume: Sora Andreea-Ioana/ Grupa: 134/ Proiect 2 POO - Tema 11 - Abonati la biblioteca \n";
    cout << "-----------------------MENIU----------------------";
    cout << "\n";
    cout << "1. Citire n abonati"; cout << "\n";
    cout << "2. Afisare n abonati"; cout << "\n";
    cout << "3. Afisare abonat cu indicele i"; cout << "\n";
    cout << "4. Adauga in dosar"; cout << "\n";
    cout << "5. Afisati numarul de obiecte"; cout << "\n";
    cout << "0. Iesire."; cout << "\n";
}

void menu()
{
    int option;
    option = 0;
    int n, i, ok = 0;
    menu_output();
    cout << "\nIntroduceti n (numarul de persoane): ";
    cin >> n;
    if (n <= 0)
    {
       cout << "Invalid, n trebuie sa fie mai mare decat 0!";
       cout << "\nIntroduceti un nou n: ";
       cin >> n;
    }
    Persoana **v; ///upcast
    v = new Persoana*[n]; ///aloc memorie pentru n obiecte de tip Persoana, apoi pentru fiecare obiect il etichetez cu tipul "Abonat"
    do
    {
        if (ok == 1)
            menu_output();
        cout << "Introduceti numarul actiunii: ";
        cin >> option;
        if (ok == 0 && option != 1)
        {
            cout << "Invalid, pentru inceput trebuie sa cititi cei n abonati!\n";
            option = 1;
        }
        if (option == 1)
        {
          for (i = 0; i < n; i++)
            {
              v[i] = new Abonat; ///upcast
              cin >> *v[i];
              cout << endl;
            }
        }
        if (option == 2)
        {
             for (i = 0; i < n; i++)
                cout << *v[i] << endl; ///afisam abonatii
        }
        if (option == 3)
        {
            cout << "Introduceti indicele i: ";
            cin >> i;
            if (i>=n || i<0)
                {
                  cout << "Invalid, indicele trebuie sa fie mai mic decat " << n << " si mai mare sau egal decat 0!\n";
                  cout << "Alegeti un nou indice!\n";
                  cout << "Introduceti noul indice i: ";
                  cin >> i;
                }
            cout << *v[i] << endl; ///afisam abonatul cu indice i
        }
        if (option == 4)
        {
           cout << "\n";
           Abonat *v2 = new Abonat[n];
           for (i = 0; i < n; i++)
              { ///downcasting pentru a converti pointerii obiectelor de tip Persoana la obiecte de tip Abonat
               Abonat *a = dynamic_cast <Abonat*> (v[i]); ///dynamic cast
               v2[i] = *a;
               }
           dosar d(v2, n); ///adaugam in dosar informatiile celor n abonati
           cout << "Informatiile au fost adaugate cu succes in dosar! \n";
           cout << "Dosarul este: \n";
           cout << "\n";
           cout << d; ///afisam dosarul
        }
        if (option == 5)
        {
            Persoana::NumarObiecte(); ///afisam numarul de obiecte
        }
        if (option<0 || option>5)
        {
            cout << "Selectie invalida";
        }
        cout << "\n";
        ok = 1;
        system("pause");
        system("cls");
    }
    while(option != 0);
}

int main()
{
    menu();
    cout << "O zi buna!";
    return 0;
}
