#include <iostream>
#include <vector>
#include <list>
#include <array>
#include <string>
#include <map>
#include <sstream>
#include <iomanip>
#include <stdexcept>
#include <stack>
#include <queue>

using namespace std;

//buraya integer'� string yapan bi map koy
//o map ara� t�r� olsun. k�yaslama i�in int, yazd�rmak i�in mapten gelen string kullan�l�r
map<int, string> yukTuruMap = { {1, "Kuru Yuk"}, {2, "Gida"}, {3, "Kimyasal"} };
//kullanimi yukturlerimap[1]; �eklinde. bu bir string d�nd�r�yor

map<string, vector<char>> aracTuruMap = { {"Kamyon", {'K', 'a', 'm', 'y', 'o', 'n'}},
	{"Acik Kasa Kamyonet", {'A', 'c', 'i', 'k', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Kapali Kasa Kamyonet", {'K', 'a', 'p', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Sogutmali Kasa Kamyonet", {'S', 'o', 'g', 'u', 't', 'm', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Tir", {'T', 'i', 'r'}} };


class Yuk {

	//Yuk s�n�f� i�in == operat�r tan�m�
	friend bool operator==(const Yuk& yukcuk, const Yuk& yuk) {

		if (yukcuk.getYukAdi() == yuk.getYukAdi() &&
			yukcuk.getYukAgirligi() == yuk.getYukAgirligi() &&
			yukcuk.getYukHacmi() == yuk.getYukHacmi() &&
			yukcuk.getYukTuru() == yuk.getYukTuru()) {

			return true;
		}

		return false;
	}

	//y�k bilgisi i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const Yuk& yuk) {

		ostringstream str;
		str << "Yuk adi: " << yuk.getYukAdi() << endl;
		str << "Yuk turu: " << yuk.getYukTuru() << endl;
		str << "Yuk hacmi: " << yuk.getYukHacmi() << endl;
		str << "Yuk agirligi: " << yuk.getYukAgirligi() << endl;

		string print = str.str();
		out << print;

		return out;
	}

public:

	//y�k i�in hem default hem normal consturctor
	//ileride vector gibi bir �ey i�inde �a��r�rsam default olsun diye
	Yuk(string ad = "koli", int hacim = 1, int agirlik = 1, int tur = 1) :
		yukAdi(ad), yukHacmi(hacim), yukAgirligi(agirlik), yukTuru(tur) { }

	//y�k ad� i�in getter fonksiyon
	string getYukAdi() const {
		return yukAdi;
	}

	//y�k ad� i�in setter fonksiyon
	void setYukAdi(string& isim) {
		yukAdi = isim;
	}

	//y�k hacmi i�in getter fonksiyon
	int getYukHacmi() const {
		return yukHacmi;
	}

	//y�k hacmi i�in setter fonksiyon
	void setYukHacmi(int hacim) {
		yukHacmi = hacim;
	}

	//y�k a��rl��� i�in getter fonksiyon
	int getYukAgirligi() const {
		return yukAgirligi;
	}

	//y�k a��rl��� i�in setter fonksiyon
	void setYukAdi(int agirlik) {
		yukAgirligi = agirlik;
	}

	//y�k t�r� i�in getter fonksiyon
	string getYukTuru() const {
		return (yukTuruMap[yukTuru]);
	}

	//y�k t�r� i�in setter fonksiyon
	void setYukTuru(int tur) {
		yukTuru = tur;
	}

private:
	string yukAdi;
	int yukTuru;
	int yukHacmi;
	int yukAgirligi;
};


class Plaka {
public:

	//hem default hem conversion constructor
	Plaka(string plate = "34LG1780") {

		//setter fonksiyon gerekli kontrolleri yap�yor
		setPlaka(plate);
	}

	//plaka gerekti�inde bununla �a��r�lacak
	string getPlaka() const {
		return (il + harf + sayi);
	}

	//plaka i�in setter fonksiyon
	void setPlaka(string plate) {

		//uzunl�u 8 mi diye bak�yor, de�ilse exception f�rlat�yor
		if (8 != plate.length()) {
			throw invalid_argument("Plaka 8 karakterli olmali.");
		}

		//il k�sm�n� ay�r�p at�yor
		il = plate.substr(0, 2);
		//kalan k�s�m i�in de�i�ken olu�turuyor
		string tempStr{ plate.substr(2, plate.length()) };
		//tempStr'deki harf uzunlu�unu anlamak i�in dizi olu�turuyor
		bool arr[6] = { 0, 0, 0, 0, 0, 0 };

		//tempStr'deki harflerin konumunu i�aretliyor
		for (auto i{ 0 }; i < 6; ++i) {
			if ((tempStr[i] <= 'z' && tempStr[i] >= 'a') || (tempStr[i] <= 'Z' && tempStr[i] >= 'A')) {
				++arr[i];
			}
		}

		//do�ru karakterlerin harf oldu�unu kontrol etmek i�in gerek de�i�ken 
		auto tempInt{ 1 };
		//de�er toplam�n� tutmak i�in de�i�ken
		auto sum{ 0 };
		//harfli k�sm�n uzunlu�unu tutmak i�in de�i�ken
		auto harfLen{ 0 };

		//ikili sistemde de�erlerini topluyor. bu sayede her bir durum e�siz bir de�er alacak
		for (auto i{ 0 }; i < 6; ++i) {
			sum += tempInt * arr[i];
			tempInt *= 2;
		}

		//toplam 1 ise sadece ilki, 3 ise ilki ve ikincisi, 7 ise ilk ���, 15 ise ilk 4'� harfir
		//di�er de�er durumlar� kurala uymayaca�� i�in exception f�rlat�yor
		switch (sum) {
		case 1:
			harfLen = 1;
			break;
		case 3:
			harfLen = 2;
			break;
		case 7:
			harfLen = 3;
			break;
		case 15:
			harfLen = 4;
			break;
		default:
			throw invalid_argument("Plaka harf uzunlugu 1-4 araliginda degil.");
		}

		//bulunan de�erleri veri �yelerinde kaydediyor
		harf = plate.substr(2, harfLen);
		sayi = plate.substr(2 + harfLen, plate.length() - 2 - harfLen);
	}

	//setter ve getter fonksiyonlar
	//setterlarda kontrol yapma gere�i duymad�m
	string getIl() const {
		return il;
	};

	string getHarf() const {
		return harf;
	}

	string getSayi() const {
		return sayi;
	}

	void setIl(string& other) {
		il = other;
	};

	void setHarf(string& other) {
		harf = other;
	}

	void setSayi(string& other) {
		sayi = other;
	}

private:
	string il;
	string harf;
	string sayi;
	string plaka;
};


class Sofor {
public:

	//hem default hem conversion constructor
	Sofor(string sofor = "Ahmet Karahan") {
		setSofor(sofor);
	}

	//getter fonksiyon
	string getSofor() const {
		return soforAdi + soforSoyadi;
	}

	//sofor i�in setter fonksiyon
	void setSofor(string& sofor) {

		//bosluklarin indexini tutacak bir stack
		//�of�rlerin bir soyad� var diye d���nd�m. iki ismi olabilir
		stack<int> bosluk;

		//bo�lular�n indexinin kaydedilmesi
		for (auto i{ 0 }; i < static_cast<int>(sofor.length()); ++i) {
			if (' ' == sofor[i]) {
				bosluk.push(i);
			}
		}

		//bo�luk ile ayr�l�p ad ve soyad olarak kaydedilmesi
		soforAdi = sofor.substr(0, bosluk.top());
		soforSoyadi = sofor.substr(bosluk.top(), sofor.length() - bosluk.top());
	}

	//setter fonksiyon
	void setSoforAdi(string& isim) {
		soforAdi = isim;
	}

	//setter fonksiyon
	void setSoforSoyadi(string& soyisim) {
		soforSoyadi = soyisim;
	}

	//getter fonksiyon
	string getSoforAdi() const {
		return soforAdi;
	}

	//getter fonksiyon
	string getSoforSoyadi() const {
		return soforSoyadi;
	}

private:
	string soforAdi;
	string soforSoyadi;
};


class Arac {

	//arac bilgisi i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const Arac& arac) {

		//string olarak al�p yazd�r�yor
		out << arac.toStr();

		//ostream referans� d�nd�r�yor 
		return out;
	}

public:

	//constructor. kontroller oldu�u i�in default de�erler koydum
	//kontroller oldu�u i�in initializer list kullanmad�m
	Arac(string aracTuruStr, list<Yuk> liste = {}, string plaka = "34LG1780", string driver = "Ahmet Karahan") {

		//setterlar� �a��r�yor
		setYukListesi(liste);
		aracTuru = aracTuruMap[aracTuruStr];
		setPlaka(plaka);
		setSofor(driver);
	}

	//abstract s�n�f�n destrcutor'�n�n virtual olmas� daha mant�kl�
	virtual ~Arac() = default;

	//aractaki t�m y�kleri tek tek basar
	//<< operat�r� tan�ml� oldu�u i�in bu �ekilde yaz�labiliyor
	void printYukListesi() {

		//d�ng� kullanarak her y�k� yazd�r�yor
		for (Yuk yukcuk : yukListesi) {
			cout << yukcuk << endl;
		}
	}

	//toplam a��rl��� d�nd�ren fonkisyon
	int getAgirlik() const {

		//toplam a��rl��� tutacak de�i�ken
		auto sum{ 0 };

		//t�m y�klerin a��rl�klar�n� de�i�kene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukAgirligi();
		}

		//toplam de�eri d�nd�r�yor
		return sum;
	}

	//toplam hacmi d�nd�ren fonksiyon
	int getHacim() const {

		//toplam hacmi tutacak de�i�ken
		auto sum{ 0 };

		//t�m y�klerin hacimlerini de�i�kene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukHacmi();
		}

		//toplam de�eri d�nd�r�yor
		return sum;
	}

	//ara� t�r� i�in setter
	void setAracTuru(string aracTuruStr) {

		//mapten alip ekliyor
		aracTuru = aracTuruMap[aracTuruStr];
	}

	//ara� t�r� i�in getter
	string getAracTuru() const {

		//ge�ici string olu�turuyor
		string temp;

		//ge�ici stringe elemanlar� tek tek ekliyor
		for (auto i{ 0 }; i < static_cast<int>(aracTuru.size()); ++i) {
			temp += aracTuru[i];
		}

		//ge�ici stringi d�nd�r�yor
		return temp;
	}

	//plaka i�in setter fonksiyon
	void setPlaka(string plaka) {
		plate.setPlaka(plaka);
	}

	//plaka i�in getter fonksiyon
	string getPlaka() const {
		return plate.getPlaka();
	}

	//�of�r ad-soyad� i�in setter fonksiyon
	void setSofor(string sofor) {
		sorumluSofor.setSofor(sofor);
	}

	//�of�r ad-soyad� i�in getter fonksiyon
	string getSofor() const {
		return sorumluSofor.getSofor();
	}

	//�of�r ad� i�in setter fonksiyon
	void setSoforAdi(string isim) {
		sorumluSofor.setSoforAdi(isim);
	}

	//�of�r ad� i�in getter fonksiyon
	string getSoforAdi() const {
		return sorumluSofor.getSoforAdi();
	}

	//�of�r soyad� i�in setter fonksiyon
	void setSoforSoyadi(string soyisim) {
		sorumluSofor.setSoforSoyadi(soyisim);
	}

	//�of�r soyad� i�in getter fonksiyon
	string getSoforSoyadi() const {
		return sorumluSofor.getSoforSoyadi();
	}

	//y�k listesi i�in getter fonksiyon
	list<Yuk> getYukListesi() const {
		return yukListesi;
	}

	//virtual << yapamad���m i�in veriyi buradan alaca��m
	virtual string toStr() const {

		//stringstream olu�turup ekliyor
		ostringstream str;
		str << "Arac turu: " << this->getAracTuru() << endl;
		str << "Plaka: " << this->getPlaka() << endl;
		str << "Sofor adi: " << this->getSofor() << endl;
		str << "Yuk sayisi: " << this->getYukListesi().size() << endl;

		//string olarak d�nd�r�yor
		return str.str();
	}


	//y�k listesi i�in setter fonksiyon
	virtual void setYukListesi(list<Yuk> liste) {
		yukListesi = liste;
	}

	//y�k ekleme fonksiyonu
	virtual void yukEkle(const Yuk& yuk) {
		yukListesi.push_back(yuk);
	}

	//y�k adedini d�nd�r�yor
	int getYukSayisi() {
		return yukListesi.size();
	}

	//y�k ekleme fonksiyonu
	//hepsi i�in direkt ayn� olacak bu y�zden virtual olmas�na gerek yok bence
	void yukBosalt(const Yuk& yuk) {

		//t�m y�k listesini geziyor
		for (auto it1{ yukListesi.begin() }; it1 != yukListesi.end(); ++it1) {

			//t�m �zellikleri e�it ise
			if (it1->getYukAdi() == yuk.getYukAdi() &&
				it1->getYukAgirligi() == yuk.getYukAgirligi() &&
				it1->getYukHacmi() == yuk.getYukHacmi() &&
				it1->getYukTuru() == yuk.getYukTuru()) {

				//siliyor ve ��k�yor
				//ayn� nesneden tekrar varsa silmiyor
				yukListesi.erase(it1);
				break;
			}
		}
	}

	//parametre olarak int alan bo�alt fonksiyonu
	void yukBosalt(const int index) {

		//saya� de�i�keni
		auto counter{ 0 };

		//iterator tan�m�
		auto it1{ yukListesi.begin() };

		//iterator istenen konuma getiriliyor
		for (; counter < index; ++counter) {
			++it1;
		}

		//o konumdaki y�k siliniyor
		yukListesi.erase(it1);
	}

	//+= operat�r� a��r�y�klemesi
	virtual Arac& operator+=(const Yuk& yuk) {

		//var olan fonksiyonu �a��r�yor
		yukEkle(yuk);

		//nesnenin referans�n� d�nd�r�yor
		return *this;
	}

	//-= operat�r� a��r�y�klemesi
	//yukbosaltin aynisi sadece referans d�nd�r�yor
	//virtual olmas�na gerek yok, hepsi i�in ayn�
	Arac& operator-=(const Yuk& yuk) {

		//yukBosalt fonksiyonu o i�i yap�yor zaten
		yukBosalt(yuk);

		return *this;
	}

	//y�k listesinin bo� olup olmad���n� kontrol eder
	//bo� ise true d�nd�r�r
	//s�n�f�n soyut olmas�n� sa�layan fonksyion
	virtual bool bosMu() = 0;

	//y�k listesini tamamen bo�altan fonksiyon
	void tamamenBosalt() {
		yukListesi.clear();
	}

	//bubble sort ile s�ral�yor
	//fonksyion pointer'� al�yor neye g�re s�ralama se�ilece�ini belirtmek i�in
	void yukSirala(bool (*compare)(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2)) {

		for (auto i{ 0 }; i < static_cast<int>(yukListesi.size()) - 1; ++i) {

			//list iterator'lar� + ile artmad��� i�in b�yle tan�mlad�m
			auto it1{ yukListesi.begin() };
			auto it2{ it1 };
			++it2;

			//iterator ile verilere eri�tim
			for (; it2 != yukListesi.end(); ++it1, ++it2) {

				if (compare(it1, it2)) {
					swap(it1, it2);
				}
			}
		}
	}

	//a��rl��a g�re k���kten b�y��e kontrol eden bir fonksiyon
	static bool agirligaGoreBK(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		//a��rl�klar�n� k�yasl�yor
		if (yuk1->getYukAgirligi() < yuk2->getYukAgirligi()) {
			return true;
		}

		return false;
	}

	//hacmine g�re k���kten b�y��e kontrol eden bir fonksiyon
	static bool hacmineGoreKB(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		if (yuk1->getYukHacmi() > yuk2->getYukHacmi()) {
			return true;
		}

		return false;
	}

	//y�k adlar�na g�re alfabetik kontrol eden bir fonksiyon
	static bool adinaGore(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		//ufak olan boyutu buluyor
		auto minSize{ 0 };
		yuk1->getYukAdi().size() < yuk2->getYukAdi().size() ?
			minSize = (*yuk1).getYukAdi().size() :
			minSize = (*yuk2).getYukAdi().size();

		//durum tutacak de�i�ken
		bool yuk1Buyuk{ false };

		//ufak olan�n uzunlu�una kadar giden d�ng�
		for (auto i{ 0 }; i < minSize; ++i) {
			//harfleri b�y�t�yor
			//bu sayede alfabetik s�ralama yap�labilecek
			char char1{ static_cast<char>(toupper((*yuk1).getYukAdi()[i])) };
			char char2{ static_cast<char>(toupper((*yuk2).getYukAdi()[i])) };

			if (char1 > char2) {
				yuk1Buyuk = true;
				break;
			}

			if (i == minSize) {
				yuk1Buyuk = true;
			}
		}

		return yuk1Buyuk;

		/*if (yuk1Buyuk) {
			return true;
		}

		return false;*/
	}

private:
	Plaka plate;
	Sofor sorumluSofor;
	list<Yuk> yukListesi;
	vector<char> aracTuru;

	//swap i�in fonksiyon
	void swap(list<Yuk>::iterator& yuk1, list<Yuk>::iterator& yuk2) {
		Yuk tempYuk = (*yuk1);
		(*yuk1) = (*yuk2);
		(*yuk2) = tempYuk;
	}
};


class Kamyon :public Arac {

	//kamyon s�n�f� i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const Kamyon& arac) {

		//base class pointer � ile onun operat�r�ne eri�iyor ve ekleme yap�yor
		const Arac* temp = &arac;

		out << *temp;
		out << "Agirlik: " << arac.getAgirlik() << endl;

		return out;
	}

public:

	//consturctor. liste a��rl�k s�n�r�na uyuyor mu diye kontrol ediyor
	Kamyon(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac(aracTuruStr, liste, plaka, driver) {

		//kamyon ile a��k kasa kamyonet aras�ndaki tek fark a��rl�k oldu�u i�in b�yle yapt�m
		//sabit olsalar da const olarak verince veri �yesini de�i�tiremedim
		//ba�ka veri �yesi eklemenin de pek bir anlam� yok bence
		if ("Kamyon" == aracTuruStr) {
			minAgirlik = 2000;
			maxAgirlik = 10000;
		}

		//kontrol� fonksiyonda yap�yor
		this->setYukListesi(liste);
	}

	//abstract s�n�f�nki defaulttu
	virtual ~Kamyon() = default;

	//to string fonksiyonu
	virtual string toStr() const override {

		//ata s�n�ftan ald���na kendi verilerini ekliyor
		string temp = Arac::toStr();
		temp += "Agirlik: ";
		temp += to_string(this->getAgirlik());
		temp += '\n';
		return temp;

	}

	//liste a��rl�k s�n�r�na uyuyor mu diye kontrol ediyor
	virtual void setYukListesi(list<Yuk> liste) override {

		//toplam agirligi tutacak de�i�ken
		auto sum{ 0 };

		//toplam a�irli�in hesaplanmasi
		for (Yuk yuk : liste) {
			sum += yuk.getYukAgirligi();
		}

		//agirligin uygun aralikta olup olmadigi kontorol ediliyor
		if (minAgirlik > sum || maxAgirlik < sum) {
			throw invalid_argument("Agirlik 2000-10000 kg arasi olmali.");
		}

		//uygun araliktaysa listeye ekliyor
		this->Arac::setYukListesi(liste);
	}

	//eklenince olu�acak liste a��rl�k s�n�r�na uyuyor mu diye kontrol ediyor
	virtual void yukEkle(const Yuk& yuk) override {

		//toplam agirligi tutacak de�i�ken
		auto sum{ 0 };

		//toplam a�irli�in hesaplanmasi
		for (Yuk yukcuk : this->getYukListesi()) {
			sum += yukcuk.getYukAgirligi();
		}

		//son olarak yeni geleni ekliyor
		sum += yuk.getYukAgirligi();

		//agirligin uygun aralikta olup olmadigi kontorol ediliyor
		if (minAgirlik > sum || maxAgirlik < sum) {
			throw invalid_argument("Agirlik 2000-10000 kg arasi olmali.");
		}

		//uygunsa y�k� ekliyor
		this->Arac::yukEkle(yuk);
	}

	//eklenince olu�acak liste a��rl�k s�n�r�na uyuyor mu diye kontrol ediyor
	virtual Kamyon& operator+=(const Yuk& yuk) override {

		//uygunsa y�k� ekliyor
		yukEkle(yuk);

		return *this;
	}

	//bo� olup olmad���n� kontrol ediyor
	//pure virtual oldu�u i�in hepsinde ayn� �ekilde tan�mlamam gerekti
	//bo�sa true d�nd�r�r
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}



private:
	int minAgirlik{ 1500 };
	int maxAgirlik{ 3000 };
};


class AcikKasa :public Kamyon {

	//a��k kasa kamyonet s�n�f� i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const AcikKasa& arac) {

		//base class pointer � ile onun operat�r�ne eri�iyor ve ekleme yap�yor
		const Kamyon* temp = &arac;

		out << *temp;

		return out;
	}

public:

	//constructor. kontroller ata s�n�fta yap�l�yor
	AcikKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Kamyon(aracTuruStr, liste, plaka, driver) {	}

	//t�retilmi� s�n�f oldu�u i�in
	virtual ~AcikKasa() = default;

private:

};


class KapaliKasa :public Kamyon {

	//Kapali Kasa Kamyonet s�n�f� i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const KapaliKasa& arac) {

		//base class pointer � ile onun operat�r�ne eri�iyor ve ekleme yap�yor
		const Kamyon* temp = &arac;

		out << *temp;
		out << "Toplam hacim: " << arac.getHacim() << endl;

		return out;
	}


public:

	//consturctor. listeyi kontrol ediyor
	KapaliKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Kamyon(aracTuruStr, liste, plaka, driver) {

		//uygun araliktaysa listeye ekliyor
		//degilse bo� liste olu�turuluyor constructorda
		this->setYukListesi(liste);
	}

	//default olsun diye
	virtual ~KapaliKasa() = default;

	//kapal� kasa i�in to string fonksiyonu
	virtual string toStr() const override {

		//ata s�n�ftan ald���na ekleme yap�yor
		string temp = Kamyon::toStr();
		temp += "Toplam hacim: ";
		temp += to_string(this->getHacim());
		temp += '\n';
		return temp;
	}

	//kontrol edip listeyi at�yor
	virtual void setYukListesi(list<Yuk> liste) override {

		//toplam hacmi tutacak de�i�ken
		auto sum{ 0 };

		//toplam hacmin hesaplanmasi
		for (Yuk yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		//hacmin uygun aralikta olup olmadigi kontorol ediliyor
		if (MIN_HACIM > sum || MAX_HACIM < sum) {
			throw invalid_argument("Hacim 10-30 araliginda degil");
		}

		//uygun de�erlerdeyse listeye ekliyor
		this->Kamyon::setYukListesi(liste);
	}

	//kontrol edip ekliyor
	virtual void yukEkle(const Yuk& yuk) override {

		//toplam hacim de�erini tutacak de�i�ken
		auto sum{ 0 };

		//toplam hacmin hesaplanmasi
		for (Yuk yukcuk : this->getYukListesi()) {
			sum += yukcuk.getYukHacmi();
		}

		//son olarak yeni geleni ekliyor
		sum += yuk.getYukHacmi();

		//hacmin uygun aralikta olup olmadigi kontorol ediliyor
		if (MIN_HACIM > sum || MAX_HACIM < sum) {
			throw invalid_argument("Hacim 10-30 m'3 arasi olmali.");
		}

		//uygunsa y�k� ekliyor
		this->Kamyon::yukEkle(yuk);
	}

	//kontrol edip ekliyor ve nesneyi d�nd�r�yor
	virtual KapaliKasa& operator+=(const Yuk& yuk) override {

		//uygunsa ekliyor
		yukEkle(yuk);

		//nesneyi d�nd�r�yor
		return *this;
	}

private:
	const int MIN_HACIM{ 10 };
	const int MAX_HACIM{ 30 };
};


class SogutmaliKasa :public KapaliKasa {

	//so�utmali kasa kamyonet s�n�f� i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const SogutmaliKasa& arac) {

		//base class pointer � ile onun operat�r�ne eri�iyor ve ekleme yap�yor
		const KapaliKasa* temp = &arac;

		out << *temp;
		out << "Kamyonet sicakligi: " << arac.getKasaSicakligi() << endl;

		return out;
	}


public:
	//consturctor. listeyi kontrol ediyor
	SogutmaliKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver, int sicaklik) :
		KapaliKasa(aracTuruStr, liste, plaka, driver), kasaSicakligi(sicaklik) {

		//uygun araliktaysa listeye ekliyor
		//degilse bo� liste olu�turuluyor constructorda
		this->setYukListesi(liste);
	}

	//t�retilmi� s�n�f oldu�u i�in
	virtual ~SogutmaliKasa() = default;

	//so�utmali kasa i�in to string fonksiyonu
	virtual string toStr() const override {

		//temp string olu�turup ata s�n�ftan ald���na ek yap�yor
		string temp = KapaliKasa::toStr();
		temp += "Kamyonet sicakligi: ";
		temp += to_string(this->getKasaSicakligi());
		temp += '\n';
		return temp;
	}

	//s�cakl�k kontrol� ile listeyi at�yor
	virtual void setYukListesi(list<Yuk> liste) override {

		//s�cakl�k kontrol� yap�yor
		if (MAX_SICAKLIK < kasaSicakligi || MIN_SICAKLIK > kasaSicakligi) {
			throw invalid_argument("Sicaklik degeri uygun aralikta degil.");
		}

		//uygunsa listeyi at�yor
		KapaliKasa::setYukListesi(liste);
	}

	//kasa sicakligi i�in setter
	void setKasaSicakligi(int sicaklik) {

		//sicaklik kontrol� yap�yor
		//kasa i�i bo�ssa y�klere bir �ey olmayaca�� i�in sorun yok
		if (!(this->bosMu()) && (MAX_SICAKLIK < sicaklik || MIN_SICAKLIK > sicaklik)) {
			throw invalid_argument("Girilen sicaklik degeri uygun aralikta degil.");
		}

		//uygun ise at�yor
		kasaSicakligi = sicaklik;
	}


	//kasa sicakligi i�in getter fonksiyon
	int getKasaSicakligi() const {
		return kasaSicakligi;
	}

	//y�k ekleme, ��karma gibi i�lerin s�cakl�k ile alakas� yok
	//kasan�n s�cakl���na ba�l�, y�ke de�il

private:
	int kasaSicakligi;
	const int MAX_SICAKLIK{ -10 };
	const int MIN_SICAKLIK{ -40 };
};


class Tir :public Arac {

	//tir s�n�f� i�in << operat�r tan�m�
	friend ostream& operator<<(ostream& out, const Tir& arac) {

		//base class pointer � ile onun operat�r�ne eri�iyor ve ekleme yap�yor
		const Arac* temp = &arac;

		out << *temp;
		out << "Toplam agirik: " << arac.getAgirlik() << endl;
		out << "Toplam hacim: " << arac.getHacim() << endl;
		out << "Dorse kodu: " << arac.getDorse() << endl;

		return out;
	}

public:

	//constructor. dorse kodu i�in yer aliyor
	Tir(const char* oDorse, string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac(aracTuruStr, liste, plaka, driver) {

		//uzunlu�u tespit etme ve o uzunlukta yer alma
		dorseLen = strlen(oDorse);
		dorse = new char[dorseLen];

		//yer al�rken hata olu�ursa hata f�rlat�yor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//al�nan yere veriyi kopyal�yor
		memcpy(dorse, oDorse, dorseLen);

		//listeyi at�yor. hata olursa i�eride olacak
		setYukListesi(liste);
	}

	//virtual destructor
	virtual ~Tir() {

		//pointer dolu mu diye bak�yor, dolu ise bo�alt�yor
		if (dorse) {
			delete[] dorse;
		}

		//bo�altt��� yere nullptr at�yor
		dorse = nullptr;
	}

	//copy constructor
	Tir(const Tir& o) :
		Arac(o.getAracTuru(), o.getYukListesi(), o.getPlaka()), dorseLen(o.dorseLen) {

		//yer aliyor
		dorse = new char[dorseLen];

		//ald��� yer al�nabilmi� mi diye bak�yor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//ald��� yere veriyi at�yor
		memcpy(dorse, o.dorse, dorseLen);

		//di�er veri �yelerini kopyal�yor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	//move constructor
	Tir(Tir&& o) noexcept :
		Arac(o.getAracTuru(), o.getYukListesi(), o.getPlaka()), dorseLen(o.dorseLen), dorse(o.dorse) {

		//eskisini s�f�rl�yor
		o.dorse = nullptr;
		o.dorseLen = 0;

		//di�er veri �yelerini kopyal�yor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	//copy assignment operator
	Tir& operator=(const Tir& o) {

		//self assignment kontrol� yap�yor
		if (this != &o) {

			//yer al�nm��sa b�rak�yor
			if (dorse) {
				delete[] dorse;
			}

			//boyutunu kopyal�yor o boyutta yer al�yor
			dorseLen = o.dorseLen;
			dorse = new char[dorseLen];

			//ald��� yeri alabilmi� mi diye bak�yor
			if (dorse == nullptr) {
				throw ("Yer alinirken hata olustu.");
			}

			//ald��� yere veriyi at�yor
			memcpy(dorse, o.dorse, dorseLen);

			//di�er veri �yelerini kopyal�yor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		//kendini d�nd�r�yor
		return *this;
	}

	//move assignment operator
	Tir& operator=(Tir&& o) noexcept {

		//self assignment kontrl�
		if (this != &o) {

			//daha �nce yer al�nm�� m� diye bak�yor
			if (dorse) {
				delete[] dorse;
			}

			//verileri kopyal�yor
			dorseLen = o.dorseLen;
			dorse = o.dorse;

			//eski verileri s�f�rl�yor
			o.dorseLen = 0;
			o.dorse = nullptr;

			//di�er veri �yelerini kopyal�yor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		//nesneyi d�nd�r�yor
		return *this;
	}

	virtual string toStr() const override {
		string temp = Arac::toStr();
		temp += "Agirlik: ";
		temp += to_string(this->getAgirlik());
		temp += '\n';
		temp += "Hacim: ";
		temp += to_string(this->getHacim());
		temp += '\n';
		temp += "Dorse kodu: ";
		temp += this->getDorse();
		temp += '\n';
		return temp;
	}

	//hacmi kontrol edip uygunsa ekliyor
	virtual void setYukListesi(list<Yuk> liste) override {

		//toplam hacim de�erini tutacak de�i�ken
		auto sum{ 0 };

		//toplam hacim de�erinin hesaplanmas�
		for (Yuk yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		//uygun aral�kta de�ilse exception f�rlat�yor
		if (MAX_HACIM<sum || MIN_HACIM>sum) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		//uygun aral�kta ise ekliyor
		this->Arac::setYukListesi(liste);
	}

	//kontrol edip y�k ekleyen fonksiyon
	virtual void yukEkle(const Yuk& yukcuk) override {

		//toplam hacim de�erini tutacak de�i�ken
		auto sum{ 0 };

		//toplam hacim de�erinin hesaplanmas�
		for (Yuk yuk : this->getYukListesi()) {
			sum += yuk.getYukHacmi();
		}

		//son olarak yeni geleni ekliyor
		sum += yukcuk.getYukHacmi();

		//uygun aral�kta de�ilse exception f�rlat�yor
		if (MAX_HACIM<sum || MIN_HACIM>sum) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		//uygun aral�kta ise ekliyor
		this->Arac::yukEkle(yukcuk);
	}

	//kontrol edip y�k ekleyen operat�r
	virtual Tir& operator+=(const Yuk& yuk) override {

		//uygunsa ekliyor
		yukEkle(yuk);

		return *this;
	}

	//bo� olup olmad���n� kontrol eder
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}

	//dorse i�in getter
	string getDorse() const {

		//temp string olu�turuyor
		string temp;

		//temp'e char olarak s�rayla at�yor ve d�nd�r�yor 
		for (auto i{ 0 }; i < dorseLen; ++i) {
			temp += dorse[i];
		}

		return temp;
	}

	//dorse i�in setter fonksiyon
	void setDorse(char* text) {

		//verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		//boyutunu al�p ona g�re yer al�yor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		//ald��� yer al�nabilmi� mi diye bak�yor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//ald��� yere veriyi at�yor
		memcpy(dorse, text, dorseLen);
	}

	//dorse i�in parametre olarak const char pointer'� alan fonksiyon
	void setDorse(const char* text) {

		//verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		//boyutunu al�p ona g�re yer al�yor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		//ald��� yer al�nabilmi� mi diye bak�yor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//ald��� yere veriyi at�yor
		memcpy(dorse, text, dorseLen);
	}

private:
	const int MAX_HACIM{ 40 };
	const int MIN_HACIM{ 30 };
	char* dorse;
	int dorseLen;
};


int main() {

	//ad hacim a��rl�k t�r
	//y�klerin tan�m�
	Yuk y1{ "elma yuk1", 10, 750, 2 };
	Yuk y2{ "armut yuk2", 15, 500, 3 };
	Yuk y3{ "kiraz yuk3", 10, 500, 1 };
	Yuk y4{ "kalem yuk4", 15, 750, 1 };
	Yuk y5{ "gitar yuk5", 15, 1000, 2 };
	Yuk y6{ "araba yuk6", 3, 1000, 3 };
	Yuk y7{ "karpuz yuk7", 1, 500, 2 };

	//listeler tan�m�
	list<Yuk> list1{ y1, y2, y3, y4, y5 };
	list<Yuk> list2{ y1, y1, y1, y1, y1 };
	list<Yuk> list3{ y2, y2, y2, y2, y2 };
	list<Yuk> list4{ y3, y3, y3, y3, y3 };
	list<Yuk> list5{ y4, y4, y4, y4, y4 };

	//t�ra eklenecek y�kler
	list<Yuk> list6;
	for (auto i{ 0 }; i < 10; ++i) {
		list6.push_back(y6);
	}

	//ara� pointer vekt�r tan�m�
	//bu sayede �al��ma zaman�nda hangi t�r ara� gelece�inin bilinmesine gerek yok
	//15 ara� bile fazla bence bu y�zden 20 yapmad�m
	//default consturctor yap�labilirdi ama tercih etmedim
	//�ok daha rahat olurdu belki ama �imdi d���n�nce ara� t�r�n� nas�l belirtece�imi bilemedim
	vector<Arac*> aracPtr;

	// 1
	try {
		aracPtr.push_back(new Kamyon{ "Kamyon", list1, "34LG1780", "Efe Kaya" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 2
	try {
		aracPtr.push_back(new Kamyon{ "Kamyon", list2, "41PS3737", "Dilara Y�nev" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 3
	try {
		aracPtr.push_back(new Kamyon{ "Kamyon", list3, "64BYZ482", "Ozgur Uysal" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 4
	try {
		aracPtr.push_back(new AcikKasa{ "Acik Kasa Kamyonet", list1, "24KGB171", "Fatma Akg�n" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 5
	try {
		aracPtr.push_back(new AcikKasa{ "Acik Kasa Kamyonet", list2, "24RAW292", "Demet Ozen" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 6
	try {
		aracPtr.push_back(new AcikKasa{ "Acik Kasa Kamyonet", list3, "07MIT593", "Safiye Utkan" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 7
	try {
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list1, "08MI6692", "Ethem Y�lmaz", -20 });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 8
	try {
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list2, "16MI5111", "Burcu �ahbaz", -25 });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 9
	try {
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list3, "06FBI137", "Fikri El�i", -5 });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 10
	try {
		aracPtr.push_back(new Tir{ "dorsekodu1", "Tir", list1, "08MI6692", "Zuhal Pala" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 11
	try {
		aracPtr.push_back(new Tir{ "dorsekodu2", "Tir", list6, "35KAH201", "Dogan Tutak" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 12
	try {
		aracPtr.push_back(new Tir{ "dorsekodu4", "Tir", list6, "55ELMA22", "Sibel Sari" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 13
	try {
		aracPtr.push_back(new KapaliKasa{ "Kapali Kasa Kamyonet", list3, "07SSD3448", "Halil Karaca" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 14
	try {
		aracPtr.push_back(new KapaliKasa{ "Kapali Kasa Kamyonet", list3, "49MAK650", "Fatih Konak" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 15
	try {
		aracPtr.push_back(new KapaliKasa{ "Kapali Kasa Kamyonet", list3, "77OP1092", "Murat Korkmaz" });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}


	for (Arac* araba : aracPtr) {
		cout << *araba << endl;
	}


	//�a���t�r�nca g�rd���n�z gibi �e�itli hatalar veriyor


	cout << "###########" << endl;
	cout << "YUK EKLENECEK TIR................" << endl;
	cout << "###########" << endl << endl;
	cout << *aracPtr[5] << endl;
	//t�ra 10 adet y�k y�kleme
	for (auto i{ 0 }; i < 10; ++i) {
		aracPtr[5]->yukEkle(y7);
	}
	cout << "###########" << endl;
	cout << "EKLENEN YUKUN BILGISI.................." << endl;
	cout << "###########" << endl;
	cout << endl << y7 << endl;
	cout << "###########" << endl;
	cout << "YUKLEME SONRASI.................." << endl;
	cout << "###########" << endl << endl <<
		*aracPtr[5] << endl;


	//var olan y�k listesi
	cout << "###########" << endl;
	cout << "YUK LISTESI.............." << endl;
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << endl << "###########" << endl;


	//burada i�inde 20 y�k olmu� oluyor
	//yazdirirken g�r�nt� kirlili�i yapaca�� i�in 6 taneye d���rece�im
	//eksiltmelerle birlikte sonunda 3 tane kalacak
	auto index{ 11 };
	for (auto i{ 0 }; i < 7; ++i) {
		aracPtr[5]->yukBosalt(index--);
		aracPtr[5]->yukBosalt(1);
	}


	//alfabetik s�ral�yor ard�ndan 3. elemani ��kart�yor
	cout << "ALFABETIK SIRALAMA......................" << endl;
	aracPtr[5]->yukSirala(Arac::adinaGore);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;
	cout << "EKSILTME......................" << endl;
	aracPtr[5]->yukBosalt(3);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();


	//a��rl��a g�re s�ral�yor ve 3. eleman� ��kart�yor
	cout << "###########" << endl;
	cout << "AGIRLIGA GORE SIRALAMA......................" << endl;
	aracPtr[5]->yukSirala(Arac::agirligaGoreBK);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;
	cout << "EKSILTME......................" << endl;
	aracPtr[5]->yukBosalt(3);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();


	//hacme g�re s�ral�yor ve 3. eleman� ��kart�yor
	cout << "###########" << endl;
	cout << "HACIME GORE SIRALAMA......................" << endl;
	aracPtr[5]->yukSirala(Arac::hacmineGoreKB);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;
	cout << "EKSILTME......................" << endl;
	aracPtr[5]->yukBosalt(3);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;


	return 0;
}