#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#define N 50

using namespace std;
class Wyswietl_miejs {
	virtual void Wyswietl_miejscowosc() = 0;
};
class Wyswietl_uzyt {
	virtual void Wyswietl_Dane() = 0;
	virtual void Wyswietl_Nazwe() = 0;
};
class Przerywnik{
	virtual void przerywnik() = 0;
};

class Uzytkownik:Wyswietl_uzyt{
protected:
	
	void przerywnik() {
		cout << "\n--------------------------\n";
	}
public:
	friend class Przerywnik;
	int pesel;
	string name;
	int demo;
	string prefix;
	Uzytkownik(int pesel_uzytkownika, string nazwa_uzytkownika) {
		this->pesel = pesel_uzytkownika;
		this->name = nazwa_uzytkownika;
		this->demo = 1;
		this->prefix = "demo";
	}

	void Wyswietl_Dane() {
		cout << prefix<< " id: " << pesel << " imie nazwisko: " << name;
		przerywnik();
	}
	void Wyswietl_Nazwe() {
		cout <<"DEMO nazwisko: " << name;
		przerywnik();
	}
	~Uzytkownik() { cout << "usunieto uzytkownika"; }
};
class Klient:public Uzytkownik,Przerywnik{
protected:

	void przerywnik() {
		cout << "\n--------------------------\n";
	}
public:

	string password;
	int balance = 0;
	Klient(int pesel, string name,string haslo_uzytkownika) :Uzytkownik(pesel, name) {
		this->password = haslo_uzytkownika;
		this->prefix = "klient";
	}
	
	int Wplac_Srodki(int count) {
		return balance += count;
	}
	void Pokaz_Srodki() {
		cout << "Dostepne srodki uzytkownika " <<name<< ": " << balance;
		przerywnik();
	}
	void Wyslij_Srodki(Klient *odbiorca, int sended_money) {
		if (sended_money > balance) {
			cout << "Brak wystarczajacej ilosci pieniedzy";
			przerywnik();
		}
		this->balance -= sended_money;
		odbiorca->balance += sended_money;
	}
	int Wyplac_Srodki(int count) {
		if (count > balance) {
			cout << "Brak wystarczajacej ilosci pieniedzy";
			przerywnik();
			return balance;
		}
		return balance -= count;
	}
	void Wyswietl_Dane() {
		Uzytkownik::Wyswietl_Dane();
	}
	
	~Klient() { "Usunieto klienta";}
};

class Kredyt {
public:
	int value;
	int time;
	float instalment;
	Kredyt(int Wielkosc_kredytu, int czas_w_miesiacach) {
		this->value = Wielkosc_kredytu;
		this->time = czas_w_miesiacach;
		this->instalment = (value/time)*1.1;
	}
	void Przydziel_Kredyt(Klient* odbiorca_kredytu, int kwota, int czas) {
		float rata;
		rata = kwota / czas;
		odbiorca_kredytu->balance += kwota;
		cout << "\nPrzyznano kredyt na kwote: " << kwota << " Czas na splate: " << czas << " miesiecy Rata: " << rata << endl;
	}
	~Kredyt() { cout << "usunieto kredyt"; }
};

class Admin: public Klient{
	
public:
	friend class Kredyt;
	Kredyt* nowykredyt;
	Admin(int pesel, string name_administratora, string haslo_administratora) :Klient(pesel, name_administratora, haslo_administratora) {
		this->prefix = "Admin";
		this->password = haslo_administratora;
	}
	void Dodaj_pieniadze(Klient* nazwa_klienta, int ilosc_pieniedzy) {
		this->balance = ilosc_pieniedzy + 1;
		Klient::Wyslij_Srodki(nazwa_klienta, ilosc_pieniedzy);
	}
	void Daj_kredyt(Klient* odbiorca_kredytu, int kwota, int czas_splaty) {
		
		nowykredyt->Przydziel_Kredyt(odbiorca_kredytu,kwota,czas_splaty);
		 
	}
	~Admin() { cout << "usunieto admina"; }
	
};


class Dyrektor :public Admin{
public:
	friend class Placowka;
	Dyrektor(int pesel,string name_dyrektora, string haslo_dyrektora):Admin(pesel,name_dyrektora,haslo_dyrektora) {
		this->prefix = "Dyrektor";
	
	}
	void Zwolnij_admina(Admin * administrator) {
		delete(administrator);
		cout << "Zwolniono pracownika";
		przerywnik();
	}
	
	~Dyrektor() { cout << "usunieto dyrektora"; }
};

class Wlasciciel:public Dyrektor{
public:
	Wlasciciel(int pesel, string nazwa_wlasciciela, string haslo_wlasciciela) :Dyrektor(pesel, nazwa_wlasciciela, haslo_wlasciciela) {
		this->prefix = "Wlasciciel";
	}
	void Zwolnij_dyrektora(Dyrektor* dyrektor) {
		delete(dyrektor);
		cout << "Zwolniono pracownika";
		przerywnik();
	}
	~Wlasciciel() { cout << "usunieto Wlasciciela"; }
};


class Oddzial {
public:
	friend class Placowka;
	string nazwa_oddzialu;
	Oddzial(string nazwa_oddzialu) {
		this->nazwa_oddzialu = nazwa_oddzialu;
	}
	
};
class Placowka {
	string nazwa_miejscowosci;
	int kod_pocz;
public:
	friend class Oddzial;
	friend class Admin;
	Oddzial** Przypisane_oddzialy=new Oddzial*[N]{0};
	Admin** Przypisani_admini = new Admin * [N] {0};
	Placowka(string nazwa_miejscowosci, int kod_pocz) {
		this->nazwa_miejscowosci = nazwa_miejscowosci;
		this->kod_pocz = kod_pocz;

	}
	void Wyswietl_placowke() {
		cout << "\nmiejscowosc i kod pocztowy " << this->nazwa_miejscowosci << " " << this->kod_pocz << endl;
	}
	void Przypisz_oddzial(Oddzial* oddzial) {
		int i = 0;
		while (!Przypisane_oddzialy[i] == 0) i++;
			Przypisane_oddzialy[i]=oddzial;
	}
	void Wyswietl_podlegle_oddzialy() {
		int i = 0;
		cout << "Przypisane oddzialy: " << endl;
		while (Przypisane_oddzialy[i]!= 0) {
			cout << Przypisane_oddzialy[i]->nazwa_oddzialu << endl;
			i++;
			
		}
		
	}
	void Przypisz_Admina(Admin* nowyAdmin) {
		int i = 0;
		while (!Przypisani_admini[i] == 0) i++;
		Przypisani_admini[i] = nowyAdmin;
	}

	void Wyswietl_podleglych_pracownikow() {
		int i = 0;
		cout << "Przypisani pracownicy: " << endl;
		while (Przypisani_admini[i] != 0) {
			Przypisani_admini[i]->Wyswietl_Dane();
			i++;

		}
	}

};
class Pracownik :Uzytkownik {
	public:
	Pracownik(int pesel) :Uzytkownik(pesel,name) {
		this->pesel = pesel;
		this->name = name;
		this->prefix = "pracownik";
	}
	void dodaj_pracownika(Oddzial* oddzial) {

	}
};


int main() {
	Uzytkownik *maciej = new Uzytkownik(1,"Maciej Kowalski");
	maciej->Wyswietl_Dane();
	maciej->Wyswietl_Nazwe();
	Klient* franek = new Klient(2,"Franek","asdd");
	Klient* zbyszek = new Klient(3, "Zbyszek", "dsss");
	Admin *leszek = new Admin(7, "leszek", "as");
	Dyrektor* krzysiek = new Dyrektor(12332, "krzysiek", "asdd");
	Wlasciciel* kacper = new Wlasciciel(1233, "kacper", "asddd");
	Placowka* krasny = new Placowka("krasnystaw", 22300);
	Oddzial* mali = new Oddzial("Mali klienci");
	Oddzial* sredni = new Oddzial("sredni klienci");
	Oddzial* duzi = new Oddzial("duzi klienci");
	franek->Wplac_Srodki(500);
	franek->Pokaz_Srodki();
	zbyszek->Wplac_Srodki(700);
	franek->Wyslij_Srodki(zbyszek, 200);
	zbyszek->Pokaz_Srodki();
	franek->Pokaz_Srodki();
	zbyszek->Wyplac_Srodki(1200);
	leszek->Dodaj_pieniadze(franek, 800);
	franek->Pokaz_Srodki();
	leszek->Daj_kredyt(franek, 7000, 10);
	franek->Pokaz_Srodki();
	leszek->Wyswietl_Dane();
	krasny->Przypisz_oddzial(mali);
	krasny->Przypisz_oddzial(sredni);
	krasny->Przypisz_oddzial(duzi);
	krasny->Wyswietl_podlegle_oddzialy();
	krasny->Przypisz_Admina(leszek);
	krasny->Wyswietl_podleglych_pracownikow();
	krzysiek->Zwolnij_admina(leszek);
	kacper->Zwolnij_dyrektora(krzysiek);
	return 0;
}