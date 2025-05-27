#include "wypozyczalnia.h"
#include <iostream>
#include <memory>
#include <limits>

using namespace std;

 int main(){
    Wypozyczalnia wyp;
    cout << "Dostepne pojazdy:\n";
    wyp.pokazDostepne();

    int wybor;
    cout << "Podaj numer pojazdu aby zobaczyc szczegoly: ";
    cin >> wybor;

    cout << "\nSzczegoly wybranego pojazdu:\n";
    wyp.pokazSzczegoly(wybor);

    return 0;
 }
