#include "wypozyczalnia.h"
#include <iomanip>     // jeśli będziesz używać setw(), setfill()
#include <cstdlib>     // np. rand(), srand()
#include <ctime>       // time()
#include <random>      // lepsze losowanie

/*             cout <<"Rok: " << pojazdy[id].getRok() 
             << ", Numer Rejestracyjny: " << pojazdy[id].getNrRejestracyjny() 
             << ", Marka: " << pojazdy[id].getMarka() 
             << ", Model: " << pojazdy[id].getModel()     
             << ", Przebieg: " << pojazdy[id].getPrzebieg() 
*/

using namespace std;


void Pojazd::wyswietlInformacje() const{
    cout<<"Rok: " << rok << ", Numer Rejestracyjny: " << nrRejestracyjny << ", Marka: " << marka << ", Model: " << model << ", Przebieg: " << przebieg << ", Dostepnosc: " << (dostepnosc ? "Dostepny" : "Niedostepny") << endl;
}
bool Pojazd::czyDostepny() const{
    return dostepnosc;
}

int Pojazd::getRok() const {
    return rok;
}

string Pojazd::getNrRejestracyjny() const {
    return nrRejestracyjny;
}

string Pojazd::getMarka() const {
    return marka;
}

string Pojazd::getModel() const {
    return model;
}

int Pojazd::getPrzebieg() const {
    return przebieg;
}


Wypozyczalnia::Wypozyczalnia() {

    pojazdy.push_back(Pojazd(2004, "ZS167PC", "Audi", "A4", 400000, true));
    pojazdy.push_back(Pojazd(2015, "DW12345", "BMW", "320i", 120000, true));
    pojazdy.push_back(Pojazd(2020, "KR56789", "Toyota", "Corolla", 80000, true));
}

void Wypozyczalnia::dodajPojazd(const Pojazd& p){
    pojazdy.push_back(p);
}

void Wypozyczalnia::pokazDostepne() const{
    
    for(int i=0; i < pojazdy.size(); ++i){
        if (pojazdy[i].czyDostepny()){
            cout <<"Rok: " << pojazdy[i].getRok() 
                 << ", Numer Rejestracyjny: " << pojazdy[i].getNrRejestracyjny() 
                 << ", Marka: " << pojazdy[i].getMarka() 
                 << endl;
        }
    }
}

void Wypozyczalnia::pokazSzczegoly(int id) const{
    if (id >= 0 && id < pojazdy.size()){
        pojazdy[id].wyswietlInformacje();
    } else {
        cout << "Nieprawidlowy numer pojazdu!" << endl;
    }

}