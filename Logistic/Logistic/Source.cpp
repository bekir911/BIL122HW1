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

//buraya integer'ý string yapan bi map koy
//o map araç türü olsun. kýyaslama için int, yazdýrmak için mapten gelen string kullanýlýr
map<int, string> yukTuruMap = { {1, "Kuru Yuk"}, {2, "Gida"}, {3, "Kimyasal"} };
//kullanimi yukturlerimap[1]; þeklinde. bu bir string döndürüyor

map<string, vector<char>> aracTuruMap = { {"Kamyon", {'K', 'a', 'm', 'y', 'o', 'n'}},
	{"Acik Kasa Kamyonet", {'A', 'c', 'i', 'k', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Kapali Kasa Kamyonet", {'K', 'a', 'p', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Sogutmali Kasa Kamyonet", {'S', 'o', 'g', 'u', 't', 'm', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Tir", {'T', 'i', 'r'}} };


class Yuk {

	//Yuk sýnýfý için == operatör tanýmý
	friend bool operator==(const Yuk& yukcuk, const Yuk& yuk) {

		if (yukcuk.getYukAdi() == yuk.getYukAdi() &&
			yukcuk.getYukAgirligi() == yuk.getYukAgirligi() &&
			yukcuk.getYukHacmi() == yuk.getYukHacmi() &&
			yukcuk.getYukTuru() == yuk.getYukTuru()) {

			return true;
		}

		return false;
	}

	//yük bilgisi için << operatör tanýmý
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

	//yük için hem default hem normal consturctor
	//ileride vector gibi bir þey içinde çaðýrýrsam default olsun diye
	Yuk(string ad = "koli", int hacim = 1, int agirlik = 1, int tur = 1) :
		yukAdi(ad), yukHacmi(hacim), yukAgirligi(agirlik), yukTuru(tur) { }

	//yük adý için getter fonksiyon
	string getYukAdi() const {
		return yukAdi;
	}

	//yük adý için setter fonksiyon
	void setYukAdi(string& isim) {
		yukAdi = isim;
	}

	//yük hacmi için getter fonksiyon
	int getYukHacmi() const {
		return yukHacmi;
	}

	//yük hacmi için setter fonksiyon
	void setYukHacmi(int hacim) {
		yukHacmi = hacim;
	}

	//yük aðýrlýðý için getter fonksiyon
	int getYukAgirligi() const {
		return yukAgirligi;
	}

	//yük aðýrlýðý için setter fonksiyon
	void setYukAdi(int agirlik) {
		yukAgirligi = agirlik;
	}

	//yük türü için getter fonksiyon
	string getYukTuru() const {
		return (yukTuruMap[yukTuru]);
	}

	//yük türü için setter fonksiyon
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

		//setter fonksiyon gerekli kontrolleri yapýyor
		setPlaka(plate);
	}

	//plaka gerektiðinde bununla çaðýrýlacak
	string getPlaka() const {
		return (il + harf + sayi);
	}

	//plaka için setter fonksiyon
	void setPlaka(string plate) {

		//uzunlðu 8 mi diye bakýyor, deðilse exception fýrlatýyor
		if (8 != plate.length()) {
			throw invalid_argument("Plaka 8 karakterli olmali.");
		}

		//il kýsmýný ayýrýp atýyor
		il = plate.substr(0, 2);
		//kalan kýsým için deðiþken oluþturuyor
		string tempStr{ plate.substr(2, plate.length()) };
		//tempStr'deki harf uzunluðunu anlamak için dizi oluþturuyor
		bool arr[6] = { 0, 0, 0, 0, 0, 0 };

		//tempStr'deki harflerin konumunu iþaretliyor
		for (auto i{ 0 }; i < 6; ++i) {
			if ((tempStr[i] <= 'z' && tempStr[i] >= 'a') || (tempStr[i] <= 'Z' && tempStr[i] >= 'A')) {
				++arr[i];
			}
		}

		//doðru karakterlerin harf olduðunu kontrol etmek için gerek deðiþken 
		auto tempInt{ 1 };
		//deðer toplamýný tutmak için deðiþken
		auto sum{ 0 };
		//harfli kýsmýn uzunluðunu tutmak için deðiþken
		auto harfLen{ 0 };

		//ikili sistemde deðerlerini topluyor. bu sayede her bir durum eþsiz bir deðer alacak
		for (auto i{ 0 }; i < 6; ++i) {
			sum += tempInt * arr[i];
			tempInt *= 2;
		}

		//toplam 1 ise sadece ilki, 3 ise ilki ve ikincisi, 7 ise ilk üçü, 15 ise ilk 4'ü harfir
		//diðer deðer durumlarý kurala uymayacaðý için exception fýrlatýyor
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

		//bulunan deðerleri veri üyelerinde kaydediyor
		harf = plate.substr(2, harfLen);
		sayi = plate.substr(2 + harfLen, plate.length() - 2 - harfLen);
	}

	//setter ve getter fonksiyonlar
	//setterlarda kontrol yapma gereði duymadým
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

	//sofor için setter fonksiyon
	void setSofor(string& sofor) {

		//bosluklarin indexini tutacak bir stack
		//þoförlerin bir soyadý var diye düþündüm. iki ismi olabilir
		stack<int> bosluk;

		//boþlularýn indexinin kaydedilmesi
		for (auto i{ 0 }; i < static_cast<int>(sofor.length()); ++i) {
			if (' ' == sofor[i]) {
				bosluk.push(i);
			}
		}

		//boþluk ile ayrýlýp ad ve soyad olarak kaydedilmesi
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

	//arac bilgisi için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const Arac& arac) {

		//string olarak alýp yazdýrýyor
		out << arac.toStr();

		//ostream referansý döndürüyor 
		return out;
	}

public:

	//constructor. kontroller olduðu için default deðerler koydum
	//kontroller olduðu için initializer list kullanmadým
	Arac(string aracTuruStr, list<Yuk> liste = {}, string plaka = "34LG1780", string driver = "Ahmet Karahan") {

		//setterlarý çaðýrýyor
		setYukListesi(liste);
		aracTuru = aracTuruMap[aracTuruStr];
		setPlaka(plaka);
		setSofor(driver);
	}

	//abstract sýnýfýn destrcutor'ýnýn virtual olmasý daha mantýklý
	virtual ~Arac() = default;

	//aractaki tüm yükleri tek tek basar
	//<< operatörü tanýmlý olduðu için bu þekilde yazýlabiliyor
	void printYukListesi() {

		//döngü kullanarak her yükü yazdýrýyor
		for (Yuk yukcuk : yukListesi) {
			cout << yukcuk << endl;
		}
	}

	//toplam aðýrlýðý döndüren fonkisyon
	int getAgirlik() const {

		//toplam aðýrlýðý tutacak deðiþken
		auto sum{ 0 };

		//tüm yüklerin aðýrlýklarýný deðiþkene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukAgirligi();
		}

		//toplam deðeri döndürüyor
		return sum;
	}

	//toplam hacmi döndüren fonksiyon
	int getHacim() const {

		//toplam hacmi tutacak deðiþken
		auto sum{ 0 };

		//tüm yüklerin hacimlerini deðiþkene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukHacmi();
		}

		//toplam deðeri döndürüyor
		return sum;
	}

	//araç türü için setter
	void setAracTuru(string aracTuruStr) {

		//mapten alip ekliyor
		aracTuru = aracTuruMap[aracTuruStr];
	}

	//araç türü için getter
	string getAracTuru() const {

		//geçici string oluþturuyor
		string temp;

		//geçici stringe elemanlarý tek tek ekliyor
		for (auto i{ 0 }; i < static_cast<int>(aracTuru.size()); ++i) {
			temp += aracTuru[i];
		}

		//geçici stringi döndürüyor
		return temp;
	}

	//plaka için setter fonksiyon
	void setPlaka(string plaka) {
		plate.setPlaka(plaka);
	}

	//plaka için getter fonksiyon
	string getPlaka() const {
		return plate.getPlaka();
	}

	//þoför ad-soyadý için setter fonksiyon
	void setSofor(string sofor) {
		sorumluSofor.setSofor(sofor);
	}

	//þoför ad-soyadý için getter fonksiyon
	string getSofor() const {
		return sorumluSofor.getSofor();
	}

	//þoför adý için setter fonksiyon
	void setSoforAdi(string isim) {
		sorumluSofor.setSoforAdi(isim);
	}

	//þoför adý için getter fonksiyon
	string getSoforAdi() const {
		return sorumluSofor.getSoforAdi();
	}

	//þoför soyadý için setter fonksiyon
	void setSoforSoyadi(string soyisim) {
		sorumluSofor.setSoforSoyadi(soyisim);
	}

	//þoför soyadý için getter fonksiyon
	string getSoforSoyadi() const {
		return sorumluSofor.getSoforSoyadi();
	}

	//yük listesi için getter fonksiyon
	list<Yuk> getYukListesi() const {
		return yukListesi;
	}

	//virtual << yapamadýðým için veriyi buradan alacaðým
	virtual string toStr() const {

		//stringstream oluþturup ekliyor
		ostringstream str;
		str << "Arac turu: " << this->getAracTuru() << endl;
		str << "Plaka: " << this->getPlaka() << endl;
		str << "Sofor adi: " << this->getSofor() << endl;
		str << "Yuk sayisi: " << this->getYukListesi().size() << endl;

		//string olarak döndürüyor
		return str.str();
	}


	//yük listesi için setter fonksiyon
	virtual void setYukListesi(list<Yuk> liste) {
		yukListesi = liste;
	}

	//yük ekleme fonksiyonu
	virtual void yukEkle(const Yuk& yuk) {
		yukListesi.push_back(yuk);
	}

	//yük adedini döndürüyor
	int getYukSayisi() {
		return yukListesi.size();
	}

	//yük ekleme fonksiyonu
	//hepsi için direkt ayný olacak bu yüzden virtual olmasýna gerek yok bence
	void yukBosalt(const Yuk& yuk) {

		//tüm yük listesini geziyor
		for (auto it1{ yukListesi.begin() }; it1 != yukListesi.end(); ++it1) {

			//tüm özellikleri eþit ise
			if (it1->getYukAdi() == yuk.getYukAdi() &&
				it1->getYukAgirligi() == yuk.getYukAgirligi() &&
				it1->getYukHacmi() == yuk.getYukHacmi() &&
				it1->getYukTuru() == yuk.getYukTuru()) {

				//siliyor ve çýkýyor
				//ayný nesneden tekrar varsa silmiyor
				yukListesi.erase(it1);
				break;
			}
		}
	}

	//parametre olarak int alan boþalt fonksiyonu
	void yukBosalt(const int index) {

		//sayaç deðiþkeni
		auto counter{ 0 };

		//iterator tanýmý
		auto it1{ yukListesi.begin() };

		//iterator istenen konuma getiriliyor
		for (; counter < index; ++counter) {
			++it1;
		}

		//o konumdaki yük siliniyor
		yukListesi.erase(it1);
	}

	//+= operatörü aþýrýyüklemesi
	virtual Arac& operator+=(const Yuk& yuk) {

		//var olan fonksiyonu çaðýrýyor
		yukEkle(yuk);

		//nesnenin referansýný döndürüyor
		return *this;
	}

	//-= operatörü aþýrýyüklemesi
	//yukbosaltin aynisi sadece referans döndürüyor
	//virtual olmasýna gerek yok, hepsi için ayný
	Arac& operator-=(const Yuk& yuk) {

		//yukBosalt fonksiyonu o iþi yapýyor zaten
		yukBosalt(yuk);

		return *this;
	}

	//yük listesinin boþ olup olmadýðýný kontrol eder
	//boþ ise true döndürür
	//sýnýfýn soyut olmasýný saðlayan fonksyion
	virtual bool bosMu() = 0;

	//yük listesini tamamen boþaltan fonksiyon
	void tamamenBosalt() {
		yukListesi.clear();
	}

	//bubble sort ile sýralýyor
	//fonksyion pointer'ý alýyor neye göre sýralama seçileceðini belirtmek için
	void yukSirala(bool (*compare)(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2)) {

		for (auto i{ 0 }; i < static_cast<int>(yukListesi.size()) - 1; ++i) {

			//list iterator'larý + ile artmadýðý için böyle tanýmladým
			auto it1{ yukListesi.begin() };
			auto it2{ it1 };
			++it2;

			//iterator ile verilere eriþtim
			for (; it2 != yukListesi.end(); ++it1, ++it2) {

				if (compare(it1, it2)) {
					swap(it1, it2);
				}
			}
		}
	}

	//aðýrlýða göre küçükten büyüðe kontrol eden bir fonksiyon
	static bool agirligaGoreBK(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		//aðýrlýklarýný kýyaslýyor
		if (yuk1->getYukAgirligi() < yuk2->getYukAgirligi()) {
			return true;
		}

		return false;
	}

	//hacmine göre küçükten büyüðe kontrol eden bir fonksiyon
	static bool hacmineGoreKB(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		if (yuk1->getYukHacmi() > yuk2->getYukHacmi()) {
			return true;
		}

		return false;
	}

	//yük adlarýna göre alfabetik kontrol eden bir fonksiyon
	static bool adinaGore(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {

		//ufak olan boyutu buluyor
		auto minSize{ 0 };
		yuk1->getYukAdi().size() < yuk2->getYukAdi().size() ?
			minSize = (*yuk1).getYukAdi().size() :
			minSize = (*yuk2).getYukAdi().size();

		//durum tutacak deðiþken
		bool yuk1Buyuk{ false };

		//ufak olanýn uzunluðuna kadar giden döngü
		for (auto i{ 0 }; i < minSize; ++i) {
			//harfleri büyütüyor
			//bu sayede alfabetik sýralama yapýlabilecek
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

	//swap için fonksiyon
	void swap(list<Yuk>::iterator& yuk1, list<Yuk>::iterator& yuk2) {
		Yuk tempYuk = (*yuk1);
		(*yuk1) = (*yuk2);
		(*yuk2) = tempYuk;
	}
};


class Kamyon :public Arac {

	//kamyon sýnýfý için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const Kamyon& arac) {

		//base class pointer ý ile onun operatörüne eriþiyor ve ekleme yapýyor
		const Arac* temp = &arac;

		out << *temp;
		out << "Agirlik: " << arac.getAgirlik() << endl;

		return out;
	}

public:

	//consturctor. liste aðýrlýk sýnýrýna uyuyor mu diye kontrol ediyor
	Kamyon(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac(aracTuruStr, liste, plaka, driver) {

		//kamyon ile açýk kasa kamyonet arasýndaki tek fark aðýrlýk olduðu için böyle yaptým
		//sabit olsalar da const olarak verince veri üyesini deðiþtiremedim
		//baþka veri üyesi eklemenin de pek bir anlamý yok bence
		if ("Kamyon" == aracTuruStr) {
			minAgirlik = 2000;
			maxAgirlik = 10000;
		}

		//kontrolü fonksiyonda yapýyor
		this->setYukListesi(liste);
	}

	//abstract sýnýfýnki defaulttu
	virtual ~Kamyon() = default;

	//to string fonksiyonu
	virtual string toStr() const override {

		//ata sýnýftan aldýðýna kendi verilerini ekliyor
		string temp = Arac::toStr();
		temp += "Agirlik: ";
		temp += to_string(this->getAgirlik());
		temp += '\n';
		return temp;

	}

	//liste aðýrlýk sýnýrýna uyuyor mu diye kontrol ediyor
	virtual void setYukListesi(list<Yuk> liste) override {

		//toplam agirligi tutacak deðiþken
		auto sum{ 0 };

		//toplam aðirliðin hesaplanmasi
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

	//eklenince oluþacak liste aðýrlýk sýnýrýna uyuyor mu diye kontrol ediyor
	virtual void yukEkle(const Yuk& yuk) override {

		//toplam agirligi tutacak deðiþken
		auto sum{ 0 };

		//toplam aðirliðin hesaplanmasi
		for (Yuk yukcuk : this->getYukListesi()) {
			sum += yukcuk.getYukAgirligi();
		}

		//son olarak yeni geleni ekliyor
		sum += yuk.getYukAgirligi();

		//agirligin uygun aralikta olup olmadigi kontorol ediliyor
		if (minAgirlik > sum || maxAgirlik < sum) {
			throw invalid_argument("Agirlik 2000-10000 kg arasi olmali.");
		}

		//uygunsa yükü ekliyor
		this->Arac::yukEkle(yuk);
	}

	//eklenince oluþacak liste aðýrlýk sýnýrýna uyuyor mu diye kontrol ediyor
	virtual Kamyon& operator+=(const Yuk& yuk) override {

		//uygunsa yükü ekliyor
		yukEkle(yuk);

		return *this;
	}

	//boþ olup olmadýðýný kontrol ediyor
	//pure virtual olduðu için hepsinde ayný þekilde tanýmlamam gerekti
	//boþsa true döndürür
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}



private:
	int minAgirlik{ 1500 };
	int maxAgirlik{ 3000 };
};


class AcikKasa :public Kamyon {

	//açýk kasa kamyonet sýnýfý için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const AcikKasa& arac) {

		//base class pointer ý ile onun operatörüne eriþiyor ve ekleme yapýyor
		const Kamyon* temp = &arac;

		out << *temp;

		return out;
	}

public:

	//constructor. kontroller ata sýnýfta yapýlýyor
	AcikKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Kamyon(aracTuruStr, liste, plaka, driver) {	}

	//türetilmiþ sýnýf olduðu için
	virtual ~AcikKasa() = default;

private:

};


class KapaliKasa :public Kamyon {

	//Kapali Kasa Kamyonet sýnýfý için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const KapaliKasa& arac) {

		//base class pointer ý ile onun operatörüne eriþiyor ve ekleme yapýyor
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
		//degilse boþ liste oluþturuluyor constructorda
		this->setYukListesi(liste);
	}

	//default olsun diye
	virtual ~KapaliKasa() = default;

	//kapalý kasa için to string fonksiyonu
	virtual string toStr() const override {

		//ata sýnýftan aldýðýna ekleme yapýyor
		string temp = Kamyon::toStr();
		temp += "Toplam hacim: ";
		temp += to_string(this->getHacim());
		temp += '\n';
		return temp;
	}

	//kontrol edip listeyi atýyor
	virtual void setYukListesi(list<Yuk> liste) override {

		//toplam hacmi tutacak deðiþken
		auto sum{ 0 };

		//toplam hacmin hesaplanmasi
		for (Yuk yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		//hacmin uygun aralikta olup olmadigi kontorol ediliyor
		if (MIN_HACIM > sum || MAX_HACIM < sum) {
			throw invalid_argument("Hacim 10-30 araliginda degil");
		}

		//uygun deðerlerdeyse listeye ekliyor
		this->Kamyon::setYukListesi(liste);
	}

	//kontrol edip ekliyor
	virtual void yukEkle(const Yuk& yuk) override {

		//toplam hacim deðerini tutacak deðiþken
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

		//uygunsa yükü ekliyor
		this->Kamyon::yukEkle(yuk);
	}

	//kontrol edip ekliyor ve nesneyi döndürüyor
	virtual KapaliKasa& operator+=(const Yuk& yuk) override {

		//uygunsa ekliyor
		yukEkle(yuk);

		//nesneyi döndürüyor
		return *this;
	}

private:
	const int MIN_HACIM{ 10 };
	const int MAX_HACIM{ 30 };
};


class SogutmaliKasa :public KapaliKasa {

	//soðutmali kasa kamyonet sýnýfý için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const SogutmaliKasa& arac) {

		//base class pointer ý ile onun operatörüne eriþiyor ve ekleme yapýyor
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
		//degilse boþ liste oluþturuluyor constructorda
		this->setYukListesi(liste);
	}

	//türetilmiþ sýnýf olduðu için
	virtual ~SogutmaliKasa() = default;

	//soðutmali kasa için to string fonksiyonu
	virtual string toStr() const override {

		//temp string oluþturup ata sýnýftan aldýðýna ek yapýyor
		string temp = KapaliKasa::toStr();
		temp += "Kamyonet sicakligi: ";
		temp += to_string(this->getKasaSicakligi());
		temp += '\n';
		return temp;
	}

	//sýcaklýk kontrolü ile listeyi atýyor
	virtual void setYukListesi(list<Yuk> liste) override {

		//sýcaklýk kontrolü yapýyor
		if (MAX_SICAKLIK < kasaSicakligi || MIN_SICAKLIK > kasaSicakligi) {
			throw invalid_argument("Sicaklik degeri uygun aralikta degil.");
		}

		//uygunsa listeyi atýyor
		KapaliKasa::setYukListesi(liste);
	}

	//kasa sicakligi için setter
	void setKasaSicakligi(int sicaklik) {

		//sicaklik kontrolü yapýyor
		//kasa içi boþssa yüklere bir þey olmayacaðý için sorun yok
		if (!(this->bosMu()) && (MAX_SICAKLIK < sicaklik || MIN_SICAKLIK > sicaklik)) {
			throw invalid_argument("Girilen sicaklik degeri uygun aralikta degil.");
		}

		//uygun ise atýyor
		kasaSicakligi = sicaklik;
	}


	//kasa sicakligi için getter fonksiyon
	int getKasaSicakligi() const {
		return kasaSicakligi;
	}

	//yük ekleme, çýkarma gibi iþlerin sýcaklýk ile alakasý yok
	//kasanýn sýcaklýðýna baðlý, yüke deðil

private:
	int kasaSicakligi;
	const int MAX_SICAKLIK{ -10 };
	const int MIN_SICAKLIK{ -40 };
};


class Tir :public Arac {

	//tir sýnýfý için << operatör tanýmý
	friend ostream& operator<<(ostream& out, const Tir& arac) {

		//base class pointer ý ile onun operatörüne eriþiyor ve ekleme yapýyor
		const Arac* temp = &arac;

		out << *temp;
		out << "Toplam agirik: " << arac.getAgirlik() << endl;
		out << "Toplam hacim: " << arac.getHacim() << endl;
		out << "Dorse kodu: " << arac.getDorse() << endl;

		return out;
	}

public:

	//constructor. dorse kodu için yer aliyor
	Tir(const char* oDorse, string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac(aracTuruStr, liste, plaka, driver) {

		//uzunluðu tespit etme ve o uzunlukta yer alma
		dorseLen = strlen(oDorse);
		dorse = new char[dorseLen];

		//yer alýrken hata oluþursa hata fýrlatýyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//alýnan yere veriyi kopyalýyor
		memcpy(dorse, oDorse, dorseLen);

		//listeyi atýyor. hata olursa içeride olacak
		setYukListesi(liste);
	}

	//virtual destructor
	virtual ~Tir() {

		//pointer dolu mu diye bakýyor, dolu ise boþaltýyor
		if (dorse) {
			delete[] dorse;
		}

		//boþalttýðý yere nullptr atýyor
		dorse = nullptr;
	}

	//copy constructor
	Tir(const Tir& o) :
		Arac(o.getAracTuru(), o.getYukListesi(), o.getPlaka()), dorseLen(o.dorseLen) {

		//yer aliyor
		dorse = new char[dorseLen];

		//aldýðý yer alýnabilmiþ mi diye bakýyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//aldýðý yere veriyi atýyor
		memcpy(dorse, o.dorse, dorseLen);

		//diðer veri üyelerini kopyalýyor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	//move constructor
	Tir(Tir&& o) noexcept :
		Arac(o.getAracTuru(), o.getYukListesi(), o.getPlaka()), dorseLen(o.dorseLen), dorse(o.dorse) {

		//eskisini sýfýrlýyor
		o.dorse = nullptr;
		o.dorseLen = 0;

		//diðer veri üyelerini kopyalýyor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	//copy assignment operator
	Tir& operator=(const Tir& o) {

		//self assignment kontrolü yapýyor
		if (this != &o) {

			//yer alýnmýþsa býrakýyor
			if (dorse) {
				delete[] dorse;
			}

			//boyutunu kopyalýyor o boyutta yer alýyor
			dorseLen = o.dorseLen;
			dorse = new char[dorseLen];

			//aldýðý yeri alabilmiþ mi diye bakýyor
			if (dorse == nullptr) {
				throw ("Yer alinirken hata olustu.");
			}

			//aldýðý yere veriyi atýyor
			memcpy(dorse, o.dorse, dorseLen);

			//diðer veri üyelerini kopyalýyor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		//kendini döndürüyor
		return *this;
	}

	//move assignment operator
	Tir& operator=(Tir&& o) noexcept {

		//self assignment kontrlü
		if (this != &o) {

			//daha önce yer alýnmýþ mý diye bakýyor
			if (dorse) {
				delete[] dorse;
			}

			//verileri kopyalýyor
			dorseLen = o.dorseLen;
			dorse = o.dorse;

			//eski verileri sýfýrlýyor
			o.dorseLen = 0;
			o.dorse = nullptr;

			//diðer veri üyelerini kopyalýyor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		//nesneyi döndürüyor
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

		//toplam hacim deðerini tutacak deðiþken
		auto sum{ 0 };

		//toplam hacim deðerinin hesaplanmasý
		for (Yuk yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		//uygun aralýkta deðilse exception fýrlatýyor
		if (MAX_HACIM<sum || MIN_HACIM>sum) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		//uygun aralýkta ise ekliyor
		this->Arac::setYukListesi(liste);
	}

	//kontrol edip yük ekleyen fonksiyon
	virtual void yukEkle(const Yuk& yukcuk) override {

		//toplam hacim deðerini tutacak deðiþken
		auto sum{ 0 };

		//toplam hacim deðerinin hesaplanmasý
		for (Yuk yuk : this->getYukListesi()) {
			sum += yuk.getYukHacmi();
		}

		//son olarak yeni geleni ekliyor
		sum += yukcuk.getYukHacmi();

		//uygun aralýkta deðilse exception fýrlatýyor
		if (MAX_HACIM<sum || MIN_HACIM>sum) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		//uygun aralýkta ise ekliyor
		this->Arac::yukEkle(yukcuk);
	}

	//kontrol edip yük ekleyen operatör
	virtual Tir& operator+=(const Yuk& yuk) override {

		//uygunsa ekliyor
		yukEkle(yuk);

		return *this;
	}

	//boþ olup olmadýðýný kontrol eder
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}

	//dorse için getter
	string getDorse() const {

		//temp string oluþturuyor
		string temp;

		//temp'e char olarak sýrayla atýyor ve döndürüyor 
		for (auto i{ 0 }; i < dorseLen; ++i) {
			temp += dorse[i];
		}

		return temp;
	}

	//dorse için setter fonksiyon
	void setDorse(char* text) {

		//verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		//boyutunu alýp ona göre yer alýyor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		//aldýðý yer alýnabilmiþ mi diye bakýyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//aldýðý yere veriyi atýyor
		memcpy(dorse, text, dorseLen);
	}

	//dorse için parametre olarak const char pointer'ý alan fonksiyon
	void setDorse(const char* text) {

		//verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		//boyutunu alýp ona göre yer alýyor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		//aldýðý yer alýnabilmiþ mi diye bakýyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		//aldýðý yere veriyi atýyor
		memcpy(dorse, text, dorseLen);
	}

private:
	const int MAX_HACIM{ 40 };
	const int MIN_HACIM{ 30 };
	char* dorse;
	int dorseLen;
};


int main() {

	//ad hacim aðýrlýk tür
	//yüklerin tanýmý
	Yuk y1{ "elma yuk1", 10, 750, 2 };
	Yuk y2{ "armut yuk2", 15, 500, 3 };
	Yuk y3{ "kiraz yuk3", 10, 500, 1 };
	Yuk y4{ "kalem yuk4", 15, 750, 1 };
	Yuk y5{ "gitar yuk5", 15, 1000, 2 };
	Yuk y6{ "araba yuk6", 3, 1000, 3 };
	Yuk y7{ "karpuz yuk7", 1, 500, 2 };

	//listeler tanýmý
	list<Yuk> list1{ y1, y2, y3, y4, y5 };
	list<Yuk> list2{ y1, y1, y1, y1, y1 };
	list<Yuk> list3{ y2, y2, y2, y2, y2 };
	list<Yuk> list4{ y3, y3, y3, y3, y3 };
	list<Yuk> list5{ y4, y4, y4, y4, y4 };

	//týra eklenecek yükler
	list<Yuk> list6;
	for (auto i{ 0 }; i < 10; ++i) {
		list6.push_back(y6);
	}

	//araç pointer vektör tanýmý
	//bu sayede çalýþma zamanýnda hangi tür araç geleceðinin bilinmesine gerek yok
	//15 araç bile fazla bence bu yüzden 20 yapmadým
	//default consturctor yapýlabilirdi ama tercih etmedim
	//çok daha rahat olurdu belki ama þimdi düþününce araç türünü nasýl belirteceðimi bilemedim
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
		aracPtr.push_back(new Kamyon{ "Kamyon", list2, "41PS3737", "Dilara Yönev" });
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
		aracPtr.push_back(new AcikKasa{ "Acik Kasa Kamyonet", list1, "24KGB171", "Fatma Akgün" });
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
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list1, "08MI6692", "Ethem Yýlmaz", -20 });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 8
	try {
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list2, "16MI5111", "Burcu Þahbaz", -25 });
	}
	catch (const std::exception& e) {
		cout << e.what() << endl;
	}
	// 9
	try {
		aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list3, "06FBI137", "Fikri Elçi", -5 });
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


	//çaþýþtýrýnca gördüðünüz gibi çeþitli hatalar veriyor


	cout << "###########" << endl;
	cout << "YUK EKLENECEK TIR................" << endl;
	cout << "###########" << endl << endl;
	cout << *aracPtr[5] << endl;
	//týra 10 adet yük yükleme
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


	//var olan yük listesi
	cout << "###########" << endl;
	cout << "YUK LISTESI.............." << endl;
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << endl << "###########" << endl;


	//burada içinde 20 yük olmuþ oluyor
	//yazdirirken görüntü kirliliði yapacaðý için 6 taneye düþüreceðim
	//eksiltmelerle birlikte sonunda 3 tane kalacak
	auto index{ 11 };
	for (auto i{ 0 }; i < 7; ++i) {
		aracPtr[5]->yukBosalt(index--);
		aracPtr[5]->yukBosalt(1);
	}


	//alfabetik sýralýyor ardýndan 3. elemani çýkartýyor
	cout << "ALFABETIK SIRALAMA......................" << endl;
	aracPtr[5]->yukSirala(Arac::adinaGore);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;
	cout << "EKSILTME......................" << endl;
	aracPtr[5]->yukBosalt(3);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();


	//aðýrlýða göre sýralýyor ve 3. elemaný çýkartýyor
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


	//hacme göre sýralýyor ve 3. elemaný çýkartýyor
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