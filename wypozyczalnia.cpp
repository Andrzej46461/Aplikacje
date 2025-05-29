#include "wypozyczalnia.h"
#include <iomanip>     // jeśli będziesz używać setw(), setfill()
#include <cstdlib>     // np. rand(), srand()
#include <ctime>       // time()
#include <random>      // lepsze losowanie
#include <memory>     


using namespace std;


void Pojazd::wyswietlInformacje() const{//uzyte
    cout<<"Rok: " << rok << ", Numer Rejestracyjny: " << nrRejestracyjny << ", Marka: " << marka << ", Model: " << model << ", Przebieg: " << przebieg << ", Dostepnosc: " << (dostepnosc ? "Dostepny" : "Niedostepny") << endl;
}
bool Pojazd::czyDostepny() const{//uzyte
    return dostepnosc;
}

int Pojazd::getRok() const {//uzyte
    return rok;
}

string Pojazd::getNrRejestracyjny() const {//uzyte
    return nrRejestracyjny;
}

string Pojazd::getMarka() const {//uzyte
    return marka;
}

string Pojazd::getModel() const {//uzyte
    return model;
}

int Pojazd::getPrzebieg() const {//uzyte
    return przebieg;
}

void Pojazd::ustawDostepnosc(bool nowyStan) {//uzyte
    dostepnosc = nowyStan;
}


Wypozyczalnia::Wypozyczalnia() { //uzyte

    pojazdy.push_back(std::make_shared<Pojazd>(2004, "ZS167PC", "Audi", "A4", 400000, true));
    pojazdy.push_back(std::make_shared<Pojazd>(2015, "DW12345", "BMW", "320i", 120000, true));
    pojazdy.push_back(std::make_shared<Pojazd>(2020, "KR56789", "Toyota", "Corolla", 80000, true));

    //linia premium

    pojazdy.push_back(std::make_shared<PojazdPremium>(2022, "WW0001", "Mercedes", "S klasa", 12000, true));
    pojazdy.push_back(std::make_shared<PojazdPremium>(2023, "PO777", "Porsche", "Panamera", 10000, true));

    //linia sport 

    pojazdy.push_back(std::make_shared<PojazdSportowy>(2024, "ZS26AWJ", "Porsche", "911 GT3 RS", 1300, true));
    pojazdy.push_back(std::make_shared<PojazdSportowy>(2024, "GA651WZ", "Ferrari", "F80", 300, true));
}

void Wypozyczalnia::dodajPojazd(std::shared_ptr<Pojazd> p){ //uzyte
    pojazdy.push_back(p);
}

void Wypozyczalnia::pokazDostepne() const{ //uzyte
    
    for(int i=0; i < pojazdy.size(); ++i){
        if (pojazdy[i]->czyDostepny()){
            cout << "ID - [" << i << "], "
                 << "Rok: " << pojazdy[i]->getRok() 
                 << ", Numer Rejestracyjny: " << pojazdy[i]->getNrRejestracyjny() 
                 << ", Marka: " << pojazdy[i]->getMarka() 
                 << endl;
        }
    }
}

void Wypozyczalnia::pokazSzczegoly(int id) const{ //uzyte
    if (id >= 0 && id < pojazdy.size()){
        pojazdy[id]->wyswietlInformacje();
    } else {
        cout << "Nieprawidlowy numer pojazdu!" << endl;
    }

}

void Wypozyczalnia::zarezerwuj(int index) { //uzyte
    if (index <0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojzadu!" << endl;
        return;
    }

    if(pojazdy[index]->czyDostepny()) {
        pojazdy[index]->ustawDostepnosc(false);
        if(std::dynamic_pointer_cast<PojazdPremium>(pojazdy[index])){
            cout <<"\nDziekujemy za skorzystanie z linii samochodow PREMIUM, usiadz wygodnie i rozkoszuj sie wyzszym poziomem komfortu.\n" << endl;
        } else if(std::dynamic_pointer_cast<PojazdSportowy>(pojazdy[index])){
            cout <<"\nKorzystasz z linii SPORT, zapnij pasy i poczuj moc.\n" << endl;
        }
        cout << "Pojazd: " << pojazdy[index]->getMarka() << " " << pojazdy[index]->getNrRejestracyjny() << " zostal zarezerwowany." << endl;
    } else {
        cout << "Pojazd: " << pojazdy[index]->getMarka() << " " <<pojazdy[index]->getNrRejestracyjny() << " jest juz niedostepny" << endl;
    }

}

void Wypozyczalnia::anulujRezerwacje(int index) { //uzyte
    if (index < 0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojazdu!" << endl;
        return;
    }

    if(!pojazdy[index]->czyDostepny()) {
        pojazdy[index]->ustawDostepnosc(true);
        cout << "Rezerwacja: " << pojazdy[index]->getMarka() << " " <<pojazdy[index]->getNrRejestracyjny() << "została anulowana." << endl;
    } else {
        cout << "Blad, pojazd: " << pojazdy[index]->getMarka() << " " <<pojazdy[index]->getNrRejestracyjny() << "jest aktualnie niezarezerwowany"<< endl;
    }
}

void Pojazd::przebiegZwrot(int km){ //uzyte
    if (km > 0) {
        przebieg += km;
    } else {
        std::cout << "Bledna liczba kilometrow." << endl;
    }
}

void Wypozyczalnia::zakonczWypozyczenie(int index) { //uzyte
    if(index < 0 || index >= pojazdy.size()) {
        cout << "Nieprawidlowy indeks pojazdu!" << endl;
        return;
    }

    if(!pojazdy[index]->czyDostepny()){
        int km;

        cout << "Ile kilometrow przejechano podczas wypozyczenia?";
        cin >> km;

        pojazdy[index]->przebiegZwrot(km);
        pojazdy[index]->ustawDostepnosc(true);

        cout << "Wypozyczenie pojazdu " << pojazdy[index]->getMarka() << " " <<pojazdy[index]->getNrRejestracyjny() << " zostalo zakonczone. Przebieg zaktualizowany.\n Dziekuje." << endl; 
    } else {
        cout << "Ten pojazd nie jest aktualnie wypozyczony." << endl;
    }

}

PojazdPremium::PojazdPremium(int rok, string nrRej, string marka, string model, int przebieg, bool dostepnosc)
    :Pojazd(rok, nrRej, marka, model, przebieg, dostepnosc) {}

    void PojazdPremium::wyswietlInformacje() const{
        cout << "[PREMIUM]";
        Pojazd::wyswietlInformacje();
    }

PojazdSportowy::PojazdSportowy(int rok,string nrRej, string marka, string model, int przebieg, bool dostepnosc)
    :Pojazd(rok, nrRej, marka, model, przebieg, dostepnosc) {}

    void PojazdSportowy::wyswietlInformacje() const{
        cout << "[SPORT]";
        Pojazd::wyswietlInformacje();
    }

void Wypozyczalnia::usunPojazd(int index) {
    if (index <0 || index >= pojazdy.size()){
        cout << "Nieprawidlowy indeks pojazdu!" << endl;
        return;
    }
    cout << "Pojazd " << pojazdy[index]->getMarka() << " " << pojazdy[index]->getNrRejestracyjny() << " zostal usuniety." << endl;
    pojazdy.erase(pojazdy.begin() + index);
}

void KontrolaPrzebiegu::wykonajKontrole(const Pojazd& pojazd) const {
    if (pojazd.getPrzebieg() > 300000) {
        cout << "!!! Pojazd o numerze rejestracyjnym: " << pojazd.getNrRejestracyjny() << " ma wysoki przebieg!\n";
    }
}

void KontrolaDostepnosci::wykonajKontrole(const Pojazd& pojazd) const {
    if (!pojazd.czyDostepny()) {
        cout << "Pojazd " << pojazd.getNrRejestracyjny() << "jest nieostepny.\n";
    }
}

const vector<shared_ptr<Pojazd>>& Wypozyczalnia::getPojazdy() const {
    return pojazdy;
}