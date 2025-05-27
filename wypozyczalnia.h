#pragma once
#include <string>
#include <vector>
#include <memory>     // jeśli użyjesz std::shared_ptr lub std::unique_ptr
#include <iostream> 

class Pojazd {
    protected:
        int rok;
        std::string nrRejestracyjny;
        std::string marka;
        std::string model;
        int przebieg;
        bool dostepnosc;
    public:
        Pojazd(int rok,std::string nrRej,std::string marka,std::string mod,int przebieg,bool dostepnosc) {
            this->rok=rok;
            this->nrRejestracyjny=nrRej;
            this->marka=marka;
            this->model=mod;
            this->przebieg=przebieg;
            this->dostepnosc=dostepnosc;
        }
    void wyswietlInformacje() const; //zrobione
    bool czyDostepny() const; //zrobione
    void ustawDostepnosc(bool nowyStan);//zrobione
    void przebiegZwrot(int km);

    int getRok() const;
    std::string getNrRejestracyjny() const;
    std::string getMarka() const;
    std::string getModel() const;
    int getPrzebieg() const;
    bool getDostepnosc() const;
};

/*std::vector   
pojazdy.push_back(p);      // dodaj pojazd
pojazdy.at(i)              // dostep do i-tego pojazdu z kontrola granic
pojazdy[i]                 // dostep do i-tego pojazdu bez kontroli
pojazdy.size()             // liczba pojazdow
pojazdy.clear()            // usun wszystko*/
class Wypozyczalnia{
    private:
        std::vector<Pojazd> pojazdy;
    
    public:
        Wypozyczalnia();
        void dodajPojazd(const Pojazd& p);//zrobione
        void pokazDostepne() const;//zrobione
        void pokazSzczegoly(int index) const;//zrobione
        void zarezerwuj(int index);//zrobione
        void anulujRezerwacje(int index);
        void zakonczWypozyczenie(int index);
};