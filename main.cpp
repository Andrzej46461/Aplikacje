#include "wypozyczalnia.h"
#include <iostream>
#include <memory>
#include <limits>

using namespace std;

 int main(){
   /* Wypozyczalnia wyp;
    cout << "Dostepne pojazdy:\n";
    wyp.pokazDostepne();

    int wybor;
    cout << "Podaj numer pojazdu aby zobaczyc szczegoly: ";
    cin >> wybor;

    cout << "\nSzczegoly wybranego pojazdu:\n";
    wyp.pokazSzczegoly(wybor);
*/
   Wypozyczalnia wyp;
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

    return 0;
 }
