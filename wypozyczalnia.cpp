#include "wypozyczalnia.h"
#include <iomanip>     // jeśli będziesz używać setw(), setfill()
#include <cstdlib>     // np. rand(), srand()
#include <ctime>       // time()
#include <random>      // lepsze losowanie


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

void Pojazd::ustawDostepnosc(bool nowyStan) {
    dostepnosc = nowyStan;
}


Wypozyczalnia::Wypozyczalnia() {

    pojazdy.push_back(Pojazd(2004, "ZS167PC", "Audi", "A4", 400000, true));
    pojazdy.push_back(Pojazd(2015, "DW12345", "BMW", "320i", 120000, true));
    pojazdy.push_back(Pojazd(2020, "KR56789", "Toyota", "Corolla", 80000, true));
}

void Wypozyczalnia::dodajPojazd(const Pojazd& p){
    pojazdy.push_back(p);
}

void Wypozyczalnia::pokazDostepne() const{ //uzyte
    
    for(int i=0; i < pojazdy.size(); ++i){
        if (pojazdy[i].czyDostepny()){
            cout << "ID - [" << i << "], "
                 << "Rok: " << pojazdy[i].getRok() 
                 << ", Numer Rejestracyjny: " << pojazdy[i].getNrRejestracyjny() 
                 << ", Marka: " << pojazdy[i].getMarka() 
                 << endl;
        }
    }
}

void Wypozyczalnia::pokazSzczegoly(int id) const{ //uzyte
    if (id >= 0 && id < pojazdy.size()){
        pojazdy[id].wyswietlInformacje();
    } else {
        cout << "Nieprawidlowy numer pojazdu!" << endl;
    }

}

void Wypozyczalnia::zarezerwuj(int index) {
    if (index <0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojzadu!" << endl;
        return;
    }

    if(pojazdy[index].czyDostepny()) {
        pojazdy[index].ustawDostepnosc(false);
        cout << "Pojazd: " << pojazdy[index].getNrRejestracyjny() << " zostal zarezerwowany." << endl;
    } else {
        cout << "Pojazd: " << pojazdy[index].getNrRejestracyjny() << " jest juz niedostepny" << endl;
    }

}

void Wypozyczalnia::anulujRezerwacje(int index) {
    if (index < 0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojazdu!" << endl;
        return;
    }

    if(!pojazdy[index].czyDostepny()) {
        pojazdy[index].ustawDostepnosc(true);
        cout << "Rezerwacja: " << pojazdy[index].getNrRejestracyjny() << "została anulowana." << endl;
    } else {
        cout << "Blad, pojazd: " <<pojazdy[index].getNrRejestracyjny() << "jest aktualnie niezarezerwowany"<< endl;
    }
}

void Pojazd::przebiegZwrot(int km){
    if (km > 0) {
        przebieg += km;
    } else {
        std::cout << "Bledna liczba kilometrow." << endl;
    }
}

void Wypozyczalnia::zakonczWypozyczenie(int index) {
    if(index < 0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojazdu!" << endl;
        return;
    }

    if(!pojazdy[index].czyDostepny()){
        int km;

        cout << "Ile kilometrow przejechano podczas wypozyczenia?";
        cin >> km;

        pojazdy[index].przebiegZwrot(km);
        pojazdy[index].ustawDostepnosc(true);

        cout << "Wypozyczenie pojazdu " << pojazdy[index].getNrRejestracyjny() << " zostalo zakonczone. Przebieg zaktualizowany.\n Dziekuje." << endl; 
    } else {
        cout << "Ten pojazd nie jest aktualnie wypozyczony." << endl;
    }

}