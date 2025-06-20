#pragma once
#include <string>
#include <vector>
#include <memory>     // std::shared_ptr 
#include <iostream> 

class Pojazd {
    protected:
        int rok;
        std::string nrRejestracyjny;
        std::string marka;
        std::string model;
        int przebieg;
        bool dostepnosc;
        int dni;
    public:
        Pojazd(int rok,std::string nrRej,std::string marka,std::string mod,int przebieg,bool dostepnosc) {
            this->rok=rok;
            this->nrRejestracyjny=nrRej;
            this->marka=marka;
            this->model=mod;
            this->przebieg=przebieg;
            this->dostepnosc=dostepnosc;
        }
    //void wyswietlInformacje() const; //teraz uzywam virtual void wyswietlInformacje()...
    bool czyDostepny() const; 
    void ustawDostepnosc(bool nowyStan);
    void przebiegZwrot(int km);
    virtual void wyswietlInformacje() const;
    virtual void naliczOplate(int dni) const;



    int getRok() const;
    std::string getNrRejestracyjny() const;
    std::string getMarka() const;
    std::string getModel() const;
    int getPrzebieg() const;
};

std::ostream& operator<<(std::ostream& os, const Pojazd& p); //przeciazenie operatora


/*std::vector   
pojazdy.push_back(p);      // dodaj pojazd
pojazdy.at(i)              // dostep do i-tego pojazdu z kontrola granic
pojazdy[i]                 // dostep do i-tego pojazdu bez kontroli
pojazdy.size()             // liczba pojazdow
pojazdy.clear()            // usun wszystko*/
class Wypozyczalnia{
    private:
        std::vector<std::shared_ptr<Pojazd>> pojazdy; 
    
    public:
        Wypozyczalnia();
        void dodajPojazd(std::shared_ptr<Pojazd> p);
        void pokazDostepne() const;
        void pokazSzczegoly(int index) const;
        void zarezerwuj(int index);
        void anulujRezerwacje(int index);
        void zakonczWypozyczenie(int index);
        void usunPojazd(int index);
        
        

        const std::vector<std::shared_ptr<Pojazd>>& getPojazdy() const;
};

class PojazdPremium : public Pojazd {
public:
    PojazdPremium(int rok, std::string nrRej, std::string marka, std::string model, int przebieg, bool dostepnosc);

    void wyswietlInformacje() const override;
    void naliczOplate(int dni) const override;

};

class PojazdSportowy : public Pojazd {
public:
    PojazdSportowy(int rok, std::string nrRej, std::string marka, std::string model, int przebieg, bool dostepnosc);
    void wyswietlInformacje() const override;
    void naliczOplate(int dni) const override;
};

class KontrolaSystemowa {
public:
    virtual void wykonajKontrole(const Pojazd& pojazd) const = 0;
    virtual ~KontrolaSystemowa() = default;
};

class KontrolaPrzebiegu : public KontrolaSystemowa {
public:
    void wykonajKontrole(const Pojazd& pojazd) const override;
};

class KontrolaDostepnosci : public KontrolaSystemowa {
public:
    void wykonajKontrole(const Pojazd& pojazd) const override;
};