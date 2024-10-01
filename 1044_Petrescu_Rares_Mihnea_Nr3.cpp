/*Se consideră o aplicație informatică pentru gestiunea domeniului Comanda cu atributele :
nume comanda(char*), id comanda(nemodificabil), tip comanda(daca este persona fizica, valoare poate true / false), numar produse, tip plata(CARD / CASH).

Definiți o clasă în limbajul C++, care va fi utilizată în cadrul acestei aplicații.
Atributele clasei sunt definite corespunzator. (1p)
Implementați următoarele metode :
-constructor default + constructorul cu urmatorii parametri : nume comanda si tip comanda(2p)
- o pereche(set / get) pentru o dată membră la alegere; includeți și validare la modificarea valorilor(1p)
- constructor de copiere(0, 5p)
- operatorul = (0, 5p)
- operatorul care permite citirea de la tastatura a unei comenzi(1p)
- un operator care sa verifice comanda mai mare(1p)
- un operator care sa adune valoarea 1 la numarul de produse existente(a se indica tipul operatorului folosit) (1p)
- o metoda care sa permita afisarea unei comenzi definita in afara clasei + o metoda care returneaza numarul de comenzi instantiate in main. (2p)

Cerințe de predare :
1. Încărcați un singur fișier sursă care include implementarea clasei și a funcției main().În funcția main() se testează toate apelurile metodelor implementate în clasă.Excitiile netestate nu se puncteaza.
2. Includeți comentarii în funcția main() pentru a indica apelurile testate(-1p în caz contrar).
4. Cel putin un obiect este alocat dinamic(-1p in caz contrar).
3. Aplicatia nu genereaza memory leaks(-1p in caz contrar).*/

#include<iostream>
#include<string>
#pragma warning(disable:4996);
using namespace std;
enum class plata { CARD, CASH };
class Comanda {
	char* nume_comanda;
	const int id_comanda;
	bool tip_comanda;
	int numar_produse;
	static int contor_rezervare;
	plata tip_plata;
public:
	Comanda() :id_comanda(contor_rezervare++)
	{
		this->nume_comanda = new char[strlen("necunoscut") + 1];
		strcpy_s(this->nume_comanda, strlen("necunoscut") + 1, "necunoscut");
		this -> tip_comanda = true;
		this->numar_produse = 3;
		this->tip_plata = plata::CARD;
	}
	Comanda(const char* nume_comanda, bool tip_comanda):id_comanda(contor_rezervare++)
	{
		this->nume_comanda = new char[strlen(nume_comanda) + 1];
		strcpy_s(this->nume_comanda, strlen(nume_comanda) + 1, nume_comanda);
		this->tip_comanda = tip_comanda;
		this->numar_produse = 5;
		this->tip_plata = plata::CARD;
	}
	Comanda(const Comanda& c) :id_comanda(contor_rezervare)
	{
		this->nume_comanda = new char[strlen(c.nume_comanda) + 1];
		strcpy_s(this->nume_comanda, strlen(c.nume_comanda) + 1, c.nume_comanda);
		this->tip_comanda = c.tip_comanda;
		this->numar_produse = c.tip_comanda;
		this->tip_plata = c.tip_plata;
	}

	~Comanda()
	{
		delete[] this->nume_comanda;
		contor_rezervare--;
	}
	void setNumarProduse(int val)
	{
		if (val > 0)
		{
			this->numar_produse = val;
		}
		else
			throw "Nu exista produse";
	}
	int getNumarProduse()
	{
		if (this->numar_produse > 0)
			return this->numar_produse;
		else
			throw "Nu exista produse";
	}
	friend static int getNumarComenzi();
	Comanda operator=(const Comanda& c)
	{
		if (this->nume_comanda != nullptr)
			delete[] this->nume_comanda;
		this->nume_comanda = new char[strlen(c.nume_comanda) + 1];
		strcpy_s(this->nume_comanda, strlen(c.nume_comanda) + 1, c.nume_comanda);
		this->tip_comanda = c.tip_comanda;
		this->numar_produse = c.tip_comanda;
		this->tip_plata = c.tip_plata;
		return *this;
	}
	// operator++ preincrementare
	Comanda operator++()
	{
		int aux = this->numar_produse;
		aux++;
		this->numar_produse=aux;
		return *this;
	}
	bool operator>(Comanda c)
	{
		return this->getNumarProduse() > c.getNumarProduse();
	}

	friend istream& operator>> (istream& CIN, Comanda c);
	friend void afisare(Comanda c);
};
int Comanda::contor_rezervare = 1;
istream& operator>>(istream& CIN, Comanda c)
{
	CIN >> c.numar_produse;
	CIN >> c.tip_comanda;
	return CIN;
}
static int getNumarComenzi()
{
	return Comanda::contor_rezervare-1;
}
void afisare(Comanda c)
{
	cout << "Comanda cu id-ul " << c.id_comanda<<", numele "<<c.nume_comanda<<endl;
	if (c.tip_comanda == true)
	{
		cout << "exista in sistem/ " << c.tip_comanda<<endl;
	}
	cout << "si contine " << c.numar_produse << " produse." << endl;
	if (c.tip_plata == plata::CARD)
	{
		cout << "Produsele s-au platit cu cardul.";
	}
	else
		if (c.tip_plata == plata::CASH)
		{
			cout << " Produsele s-au platit cash.";
		}
		else
			throw "Nu s-a facut plata";
}
int main()
	{
	//construcotr default
	Comanda c1;
	c1.setNumarProduse(6);
	cout << c1.getNumarProduse() << endl;
	// operator += preincrementare;
	++c1;
	//metoda afisare
	afisare(c1);
	//constructor de copiere
	Comanda c2 = c1;
	// verificare operator bool
	if (c2 > c1)
	{
		cout << "c2 are mai multe produse";
	}
	else
		cout << "c1 are mai multe produse";
	cout << endl;
	Comanda c4;
	//operator =
	c4 = c1;
	//constructor cu parametrii
	Comanda* c3 = new Comanda("Ilioara", true);
	//folosire  supraincarcare operator >>
	cin >> c2;
	//apelare metoda care afiseaza numarul de comenzi efectuare
	cout << getNumarComenzi();
	delete c3;
	}
