#include "wypozyczalnia.h"
#include <iostream>
#include <memory>
#include <limits>
#include <fstream>
#include <sstream>

using namespace std;

   struct Uzytkownik {
      string login;
      string haslo;
      string rola;
   };

   Uzytkownik zaloguj() {
      ifstream plik("uzytkownicy.txt");
      if(!plik.is_open()) {
         cout << "Nie mozna otworzyc pliku uzytkownicy.txt\n";
         return {"", "", "brak"};
      }

      string loginInput, hasloInput;
      cout << "Login: ";
      cin >> loginInput;
      cout << "Haslo: ";
      cin >> hasloInput;

      string linia;
      while (getline(plik, linia)){
         stringstream ss(linia);
         string login, haslo, rola;
         getline(ss, login, ';');
         getline(ss, haslo, ';');
         getline(ss, rola, ';');

         if (login == loginInput && haslo == hasloInput) {
            return {login, haslo, rola};
         }
      }
      cout << "bledne dane logowania.\n";
      return {"", "", "brak"};
   }

      void menuUzytkownika(Wypozyczalnia& wyp) {
         int wybor;
         do {
         cout << "\n==== MENU ====\n";
         cout << "1. Pokaz dostepne pojazdy\n";
         cout << "2. Pokaz szczegoly pojazdu\n";
         cout << "3. Zarezerwuj pojazd\n";
         cout << "4. Anuluj rezerwacje\n";
         cout << "5. Zakoncz rezerwacje\n";
         cout << "0. Wyjscie\n";
         cout << "\nTwoj wybor: ";
         cin >> wybor;

         switch(wybor){
            case 1:
               wyp.pokazDostepne();
               break;
            case 2: {
               int id; 
               cout << "Podaj ID pojazdu: ";
               cin >> id;
               wyp.pokazSzczegoly(id);
               break;
            }
            case 3: {
               int id;
               cout << "Podaj ID pojazdu do rezerwacji: ";
               cin >> id;
               wyp.zarezerwuj(id);
               break;
            }
            case 4: {
               int id;
               cout << "Podaj ID pojazdu do anulowania rezerwacji: ";
               cin >> id;
               wyp.anulujRezerwacje(id);
               break;
            }
            case 5: {
               int id;
               cout << "Podaj ID pojazdu do zakonczenia wypozyczenia: ";
               cin >> id;
               wyp.zakonczWypozyczenie(id);
               break;
            }
            case 0: 
               cout << "Do zobaczenia!" << endl;
               break;
            default:
               cout << "Nieprawidlowy wybor!" <<endl;
            }
      } while (wybor != 0);

      
   }

   void menuAdmina(Wypozyczalnia& wyp) {
      int wybor;
         do {
         cout << "\n==== MENU ADMINA ====\n";
         cout << "1. Pokaz dostepne pojazdy\n";
         cout << "2. Pokaz szczegoly pojazdu\n";
         cout << "3. Zarezerwuj pojazd\n";
         cout << "4. Anuluj rezerwacje\n";
         cout << "5. Zakoncz rezerwacje\n";
         cout << "6. Dodaj pojazd\n";
         cout << "7. Usun pojazd\n";
         cout << "8. Pokaz szczegoly - przeciazony operator\n";
         cout << "0. Wyjscie\n";
         cout << "\nTwoj wybor: ";
         cin >> wybor;
         int dni;
         int id;
         switch(wybor){
            case 1:
               wyp.pokazDostepne();
               break;
            case 2: {
               int id; 
               cout << "Podaj ID pojazdu: ";
               cin >> id;
               wyp.pokazSzczegoly(id);
               break;
            }
            case 3: {
               int id;
               cout << "Podaj ID pojazdu do rezerwacji: ";
               cin >> id;
               cout << "Na ile dni: ";
               cin >> dni;
               wyp.zarezerwuj(id);
               break;
            }
            case 4: {
               int id;
               cout << "Podaj ID pojazdu do anulowania rezerwacji: ";
               cin >> id;
               wyp.anulujRezerwacje(id);
               break;
            }
            case 5: {
               int id;
               cout << "Podaj ID pojazdu do zakonczenia wypozyczenia: ";
               cin >> id;
               wyp.zakonczWypozyczenie(id);
               wyp.getPojazdy().at(id)->naliczOplate(dni);
               break;
            }
            case 6: {
               int rok,przebieg;
               string nrRej, marka, model;
               cout << "Dodawanie nowego pojazdu:\n";
               cout << "Rok: "; cin >> rok;
               cout << "Numer rejestracyjny: "; cin >> nrRej;
               cout << "Marka: "; cin >> marka;
               cout << "Model: "; cin >> model;
               cout << "Przebieg: "; cin >> przebieg;

               Pojazd* pNowy = new Pojazd(rok, nrRej, marka, model, przebieg, true);
               wyp.dodajPojazd(shared_ptr<Pojazd>(pNowy));
               cout << "Dodano nowy pojazd!\n";
               break;
            }
            case 7: {
               cout << "ID pojazdu do usuniecia: ";
               cin >> id;
               wyp.usunPojazd(id);
               break;
            }
            case 8:
            cout << "Podaj ID pojazdu: ";
            cin >> id;
            cout << *wyp.getPojazdy()[id] << std::endl;//przeciazony operator
            break;
            case 0: 
               cout << "Do zobaczenia!" << endl;
               break;
            default:
               cout << "Nieprawidlowy wybor!" <<endl;
            }
      } while (wybor != 0);

   }

   void testKontrole(const vector<shared_ptr<Pojazd>>& pojazdy){
      const int ile = 2;
      KontrolaSystemowa** kontrole = new KontrolaSystemowa*[ile];

      kontrole[0] = new KontrolaPrzebiegu();
      kontrole[1] = new KontrolaDostepnosci();

      cout << "\n Wyniki kontroli systemowej \n";

      for (const auto& p: pojazdy) {
         for (int i = 0; i < ile; ++i) {
            kontrole[i]->wykonajKontrole(*p);
         }
      }

      for (int i = 0; i < ile; ++i)
         delete kontrole[i];

      delete[] kontrole;
   }

 int main(){
   Uzytkownik u = zaloguj();
   if(u.rola == "brak") return 1;

   Wypozyczalnia wyp;

   if (u.rola == "admin") {
      testKontrole(wyp.getPojazdy());
      menuAdmina(wyp);
   } else {
      menuUzytkownika(wyp);
   }
   
   
    return 0;
 }