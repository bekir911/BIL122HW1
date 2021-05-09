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
#include <cstdlib>

#define PLATE_LENGTH				0x0008
#define REMANING_PLATE_LENGHT			0x0006
#define KAMYON_MIN_AGIRLIK			0x07D0
#define KAMYON_MAX_AGIRLIK			0x2710
#define KAMYON_DEFAULT_MIN_AGIRLIK		0x05DC
#define KAMYON_DEFAULT_MAX_AGIRLIK		0x0BB8
#define KAPALI_KASA_MIN_HACIM			0x000A
#define KAPALI_KASA_MAX_HACIM			0x001E
#define SOGUTMALI_KASA_MIN_SICAKLIK	       -0x0028
#define SOGUTMALI_KASA_MAX_SICAKLIK	       -0x000A
#define TIR_MIN_HACIM				0x001E
#define TIR_MAX_HACIM				0x0028

#define KAMYON					"Kamyon"
#define ACIK_KASA_KAMYONET			"Acik Kasa Kamyonet"
#define SOGUTMALI_KASA_KAMYONET			"Sogutmali Kasa Kamyonet"
#define TIR					"Tir"

using namespace std;

map<int, string> yukTuruMap = { {1, "Kuru Yuk"}, {2, "Gida"}, {3, "Kimyasal"} };

map<string, vector<char>> aracTuruMap = { {"Kamyon", {'K', 'a', 'm', 'y', 'o', 'n'}},
	{"Acik Kasa Kamyonet", {'A', 'c', 'i', 'k', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Kapali Kasa Kamyonet", {'K', 'a', 'p', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Sogutmali Kasa Kamyonet", {'S', 'o', 'g', 'u', 't', 'm', 'a', 'l', 'i', ' ', 'K', 'a', 's', 'a', ' ', 'K', 'a', 'm', 'y', 'o', 'n', 'e', 't'}},
	{"Tir", {'T', 'i', 'r'}} };

class Yuk {

	// Yuk sinifi icin == operator tanimi
	friend bool operator==(const Yuk& yukcuk, const Yuk& yuk) {

		if (yukcuk.getYukAdi() == yuk.getYukAdi() &&
			yukcuk.getYukAgirligi() == yuk.getYukAgirligi() &&
			yukcuk.getYukHacmi() == yuk.getYukHacmi() &&
			yukcuk.getYukTuru() == yuk.getYukTuru()) {

			return true;
		}

		return false;
	}

	// Yuk bilgisi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const Yuk& yuk) {

		ostringstream ss;
		ss << "Yuk adi: " << yuk.getYukAdi() << endl;
		ss << "Yuk turu: " << yuk.getYukTuru() << endl;
		ss << "Yuk hacmi: " << yuk.getYukHacmi() << endl;
		ss << "Yuk agirligi: " << yuk.getYukAgirligi() << endl;

		out << ss.str();

		return out;
	}

public:

	// Yuk icin hem default hem normal constructor
	Yuk(string ad = "koli", int hacim = 1, int agirlik = 1, int tur = 1) :
		yukAdi{ ad }, yukHacmi{ hacim }, yukAgirligi{ agirlik }, yukTuru{ tur } { }

	// Yuk adi icin getter metot
	string getYukAdi() const {
		return yukAdi;
	}

	// Yuk adi icin setter metot
	void setYukAdi(string& isim) {
		yukAdi = isim;
	}

	// Yuk hacmi icin getter metot
	int getYukHacmi() const {
		return yukHacmi;
	}

	// Yuk hacmi icin setter metot
	void setYukHacmi(int hacim) {
		yukHacmi = hacim;
	}

	// Yuk agirligi icin getter metot
	int getYukAgirligi() const {
		return yukAgirligi;
	}

	// Yuk agirligi icin setter metot
	void setYukAdi(int agirlik) {
		yukAgirligi = agirlik;
	}

	// Yuk turu icin getter metot
	string getYukTuru() const {
		return (yukTuruMap[yukTuru]);
	}

	// Yuk turu icin setter metot
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

	// Hem default hem conversion constructor
	Plaka(string plate = "34LG1780") {

		// Setter metot gerekli kontrolleri yapiyor
		setPlaka(plate);
	}

	// Plaka icin getter metot
	string getPlaka() const {
		return (il + harf + sayi);
	}

	// Plaka icin setter metot
	void setPlaka(string plate) {

		// Uzunlugu 8 mi diye bakiyor, degilse exception firlatiyor
		if (PLATE_LENGTH != plate.length()) {
			throw invalid_argument("Plaka 8 karakterli olmali.");
		}

		// Il kismini ayirip atama yapiyor
		il = plate.substr(0, 2);
		// Kalan kisim icin degisken olusturuyor
		string tempStr{ plate.substr(il.length(), plate.length()) };
		// Kontrol icin string degiskeni
		string testStr{ "" };

		// tempStr'deki harflerin konumunu isaretliyor
		for (auto& i : tempStr) {
			testStr += isalpha(i) ? "1" : "0";
		}

		auto binaryVal{ stoi(testStr) };
		binaryVal /= 100;
		auto harfLen{ 0 };

		// Toplam 1 ise ilki, 3 ise ilk ve ikinci, 7 ise ilk ucu, 15 ise ilk dordu harftir
		// Diger durumlar kurala uymayacagi icin exception firlatiyor
		switch (binaryVal) {
		case 1000:
			harfLen = 1;
			break;
		case 1100:
			harfLen = 2;
			break;
		case 1110:
			harfLen = 3;
			break;
		case 1111:
			harfLen = 4;
			break;
		default:
			throw invalid_argument("Plaka harf uzunlugu 1-4 araliginda degil.");
		}

		// Bulunan degerleri veri uyelerine kaydediyor
		harf = plate.substr(2, harfLen);
		sayi = plate.substr(2 + harfLen, plate.length() - 2 - harfLen);
	}

	// Il icin getter metot
	string getIl() const {
		return il;
	};

	// Il icin setter metot
	void setIl(string& other) {
		il = other;
	};

	// Harf icin getter metot
	string getHarf() const {
		return harf;
	}

	// Harf icin setter metot
	void setHarf(string& other) {
		harf = other;
	}

	// Sayi icin getter metot
	string getSayi() const {
		return sayi;
	}

	// Sayi icin setter metot
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

	// Hem default hem conversion constructor
	Sofor(string sofor = "Ahmet Karahan") {
		setSofor(sofor);
	}

	// Sofor icin getter metot
	string getSofor() const {
		return soforAdi + soforSoyadi;
	}

	// Sofor icin setter metot
	void setSofor(string& sofor) {

		// Bosluklarin indexini tutacak bir stack
		// Soforlerin bir soyadi var diye dusundum. iki ismi olabilir
		stack<int> bosluk;

		// Boslularin indexinin kaydedilmesi
		for (auto i{ 0 }; i < static_cast<int>(sofor.length()); ++i) {
			if (' ' == sofor[i]) {
				bosluk.push(i);
			}
		}

		// Bosluk ile ayrilip ad ve soyad olarak kaydedilmesi
		soforAdi = sofor.substr(0, bosluk.top());
		soforSoyadi = sofor.substr(bosluk.top(), sofor.length() - bosluk.top());
	}

	// Sofor adi icin getter metot
	string getSoforAdi() const {
		return soforAdi;
	}

	// Sofor adi icin setter metot
	void setSoforAdi(string& isim) {
		soforAdi = isim;
	}

	// Sofor soyadi icin getter metot
	string getSoforSoyadi() const {
		return soforSoyadi;
	}

	// Sofor soyadi icin setter metot
	void setSoforSoyadi(string& soyisim) {
		soforSoyadi = soyisim;
	}

private:
	string soforAdi;
	string soforSoyadi;
};

class Arac {

	// Arac bilgisi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const Arac& arac) {

		// String olarak alip yazdiriyor
		out << arac.toStr();

		// Ostream referansi donduruyor 
		return out;
	}

public:

	// Constructor. Kontroller oldugu icin default degerler koydum
	// Kontroller oldugu icin initializer list kullanmadim
	Arac(string aracTuruStr,
		list<Yuk> liste = {},
		string plaka = "34LG1780",
		string driver = "Ahmet Karahan") {

		// Setter metotlari cagiriyor
		setYukListesi(liste);
		aracTuru = aracTuruMap[aracTuruStr];
		setPlaka(plaka);
		setSofor(driver);
	}

	// Abstract sinifin destrcutor'inin virtual olmasi daha mantikli
	virtual ~Arac() = default;

	// Aractaki tum yukleri tek tek basar
	// << operatoru tanimli oldugu icin bu sekilde yazilabiliyor
	void printYukListesi() {

		// Dongu kullanarak her yuku yazdiriyor
		for (Yuk yukcuk : yukListesi) {
			cout << yukcuk << endl;
		}
	}

	// Toplam agirligi donduren metot
	int getAgirlik() const {

		// Toplam agirligi tutacak degisken
		auto sum{ 0 };

		// Tum yuklerin agirligini degiskene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukAgirligi();
		}

		// Toplam degeri donduruyor
		return sum;
	}

	// Toplam hacmi donduren metot
	int getHacim() const {

		// Toplam hacmi tutacak degisken
		auto sum{ 0 };

		// Tum yuklerin hacimlerini degiskene ekliyor
		for (Yuk yukcuk : yukListesi) {
			sum += yukcuk.getYukHacmi();
		}

		// Toplam degeri donduruyor
		return sum;
	}

	// Arac turu icin setter metot
	void setAracTuru(string aracTuruStr) {

		// Map'ten alip ekliyor
		aracTuru = aracTuruMap[aracTuruStr];
	}

	// Arac turu icin getter metot
	string getAracTuru() const {

		// Gecici string olusturuyor
		string temp{ "" };

		// Gecici stringe elemanlari tek tek ekliyor
		for (auto& i : aracTuru) {
			temp += i;
		}

		// Gecici stringi donduruyor
		return temp;
	}

	// Plaka icin getter metot
	string getPlaka() const {
		return plate.getPlaka();
	}

	// Plaka icin setter metot
	void setPlaka(string plaka) {
		plate.setPlaka(plaka);
	}

	// Sofor ad-soyadi icin getter metot
	string getSofor() const {
		return sorumluSofor.getSofor();
	}

	// Sofor ad-soyadi icin setter metot
	void setSofor(string sofor) {
		sorumluSofor.setSofor(sofor);
	}

	// Sofor adi icin getter metot
	string getSoforAdi() const {
		return sorumluSofor.getSoforAdi();
	}

	// Sofor adi icin setter metot
	void setSoforAdi(string isim) {
		sorumluSofor.setSoforAdi(isim);
	}

	// Sofor soyadi icin getter metot
	string getSoforSoyadi() const {
		return sorumluSofor.getSoforSoyadi();
	}

	// Sofor soyadi icin setter metot
	void setSoforSoyadi(string soyisim) {
		sorumluSofor.setSoforSoyadi(soyisim);
	}

	// Yuk listesi icin getter metot
	list<Yuk> getYukListesi() const {
		return yukListesi;
	}

	// Yuk listesi icin setter metot
	virtual void setYukListesi(list<Yuk> liste) {
		yukListesi = liste;
	}

	//virtual << yapamadigim icin veriyi buradan aliyorum
	virtual string toStr() const {

		// Stringstream olusturup ekliyor
		ostringstream ss;
		ss << "Arac turu: " << this->getAracTuru() << endl;
		ss << "Plaka: " << this->getPlaka() << endl;
		ss << "Sofor adi: " << this->getSofor() << endl;
		ss << "Yuk sayisi: " << this->getYukListesi().size() << endl;

		// String olarak donduruyor
		return ss.str();
	}

	// Yuk eklemek icin metot
	virtual void yukEkle(const Yuk& yuk) {
		yukListesi.push_back(yuk);
	}

	// Yuk adedi icin getter metot
	int getYukSayisi() {
		return yukListesi.size();
	}

	// Yuk bosaltmak icin metot
	void yukBosalt(const Yuk& yuk) {

		// Tum yuk listesini geziyor
		for (auto it1{ yukListesi.begin() }; it1 != yukListesi.end(); ++it1) {

			// Tum ozellikleri esit ise
			if (it1->getYukAdi() == yuk.getYukAdi() &&
				it1->getYukAgirligi() == yuk.getYukAgirligi() &&
				it1->getYukHacmi() == yuk.getYukHacmi() &&
				it1->getYukTuru() == yuk.getYukTuru()) {

				// Siliyor ve cikiyor
				// Ayni nesneden tekrar varsa silmiyor
				yukListesi.erase(it1);
				break;
			}
		}
	}

	// Parametre olarak integer index alan bosalt metodu
	void yukBosalt(const int index) {

		// Sayac degiskeni
		auto counter{ 0 };

		// Iterator tanimi
		auto it1{ yukListesi.begin() };

		// Iterator istenen konuma getiriliyor
		for (; counter < index; ++counter) {
			++it1;
		}

		// O konumdaki yuk siliniyor
		yukListesi.erase(it1);
	}

	// += operator overloading
	virtual Arac& operator+=(const Yuk& yuk) {

		// Var olan metodu cagiriyor
		yukEkle(yuk);

		// Nesnenin referansini donduruyor
		return *this;
	}

	// -= operator overloading
	// Yuk bosalt'in aynisi, sadece referans donduruyor
	Arac& operator-=(const Yuk& yuk) {
		yukBosalt(yuk);

		return *this;
	}

	// Yuk listesinde olup olmadigini kontrol eder
	// Bos ise true dondurur
	// Sinifin soyut olmasini saglayan metot
	virtual bool bosMu() = 0;

	// Yuk listesini tamamen bosaltan metot
	void tamamenBosalt() {
		yukListesi.clear();
	}

	// Bubblesort kullanarak siralama yapiyor
	// Fonksiyon pointer'i aliyor, neye gore siralama secilecegini belirtmek icin
	void yukSirala(bool (*compare)(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2)) {
		for (auto i{ 0 }; i < static_cast<int>(yukListesi.size()) - 1; ++i) {
			auto it1{ yukListesi.begin() };
			auto it2{ it1 };
			++it2;

			while (it2 != yukListesi.end()) {
				if (compare(it1, it2)) {
					swap(it1, it2);
				}

				++it1; ++it2;
			}
		}
	}

	// Agirligina gore buyukten kucuge kontrol eden metot
	static bool agirligaGoreBK(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {
		return yuk1->getYukAgirligi() < yuk2->getYukAgirligi();
	}

	// Hacmine gore kucukten buyuge kontrol eden metot
	static bool hacmineGoreKB(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {
		return yuk1->getYukHacmi() > yuk2->getYukHacmi();
	}

	// Yuk adlarina gore alfabetin kontrol eden metot
	static bool adinaGore(const list<Yuk>::iterator& yuk1, const list<Yuk>::iterator& yuk2) {
		// Ufak olan boyutu buluyor
		auto minSize{ min(yuk1->getYukAdi().size(), yuk2->getYukAdi().size()) };

		// Durum tutacak degisken
		bool yuk1Buyuk{ false };

		// Ufak olanin boyutuna kadar giden dongu
		for (auto i{ 0 }; i < static_cast<int>(minSize); ++i) {
			// Harfleri buyutuyor, bu sayede alfabetik siralama yapabilecek
			char char1{ static_cast<char>(toupper(yuk1->getYukAdi()[i])) };
			char char2{ static_cast<char>(toupper(yuk2->getYukAdi()[i])) };

			if (char1 > char2) {
				yuk1Buyuk = true;
				break;
			}
		}

		return yuk1Buyuk;
	}

private:
	Plaka plate;
	Sofor sorumluSofor;
	list<Yuk> yukListesi;
	vector<char> aracTuru;

	// Swap icin metot
	void swap(list<Yuk>::iterator& yuk1, list<Yuk>::iterator& yuk2) {
		Yuk tempYuk = (*yuk1);
		(*yuk1) = (*yuk2);
		(*yuk2) = tempYuk;
	}
};

class Kamyon :public Arac {

	// Kamyon sinifi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const Kamyon& arac) {

		// Base class pointer'i ile operatorune erisilip ekleme yapiyor
		const Arac* temp{ &arac };

		out << *temp;
		out << "Agirlik: " << arac.getAgirlik() << endl;

		return out;
	}

public:

	// Consturctor. Liste agirlik sinirina uyuyor mu diye kontrol ediyor
	Kamyon(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac{ aracTuruStr, liste, plaka, driver } {

		// Kamyon ile acik kara kamyonet arasindaki fark agirlik oldugu icin bakiyor
		if (KAMYON == aracTuruStr) {
			minAgirlik = KAMYON_MIN_AGIRLIK;	// 2000 
			maxAgirlik = KAMYON_MAX_AGIRLIK;	// 10000
		}

		// Kontrolu metot ile yapiyor
		this->setYukListesi(liste);
	}

	// Abstract sinifinki gibi default
	virtual ~Kamyon() = default;

	// To string metodu
	virtual string toStr() const override {

		// Ata siniftan aldigina kendi verilerini ekliyor
		string temp{ Arac::toStr() };
		temp += "Agirlik: ";
		temp += to_string(this->getAgirlik());
		temp += '\n';

		return temp;
	}

	// Liste agirlik sinirina uyuyor mu diye kontrol ediyor
	virtual void setYukListesi(list<Yuk> liste) override {

		// Toplam agirligi tutacak degisken
		auto sum{ 0 };

		// Toplam agirligin hesaplanmasi
		for (Yuk& yuk : liste) {
			sum += yuk.getYukAgirligi();
		}

		// Agirligin uygun aralikta olup olmadigi kontorol ediliyor
		if (sum < minAgirlik || sum > maxAgirlik) {
			throw invalid_argument("Agirlik 2000-10000 kg arasi olmali.");
		}

		// Uygun araliktaysa listeye ekliyor
		this->Arac::setYukListesi(liste);
	}

	// Eklenince olusacak liste agirlik sinirina uyuyor mu diye kontrol ediyor
	virtual void yukEkle(const Yuk& yuk) override {

		// Toplam agirligi tutacak degisken
		auto sum{ 0 };

		// Toplam agirligin hesaplanmasi
		for (Yuk& yukcuk : this->getYukListesi()) {
			sum += yukcuk.getYukAgirligi();
		}

		// Son olarak yeni geleni ekliyor
		sum += yuk.getYukAgirligi();

		// Agirligin uygun aralikta olup olmadigi kontrol ediliyor
		if (sum < minAgirlik || sum > maxAgirlik) {
			throw invalid_argument("Agirlik 2000-10000 kg arasi olmali.");
		}

		// Uygunsa yuku ekliyor
		this->Arac::yukEkle(yuk);
	}

	// Kamyon yuk eklemek icin += operator tanimi
	virtual Kamyon& operator+=(const Yuk& yuk) override {

		// Uygunsa yuku ekliyor
		yukEkle(yuk);

		return *this;
	}

	// Bos olup olmadigini kontrol ediyor
	// Bossa true dondurur
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}

private:
	int minAgirlik{ KAMYON_DEFAULT_MIN_AGIRLIK };
	int maxAgirlik{ KAMYON_DEFAULT_MAX_AGIRLIK };
};

class AcikKasa :public Kamyon {

	// Acik kasa kamyonet sinifi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const AcikKasa& arac) {

		// Base class pointer'i ile onun operatorune erisiliyor ve ekleme yapiyor
		const Kamyon* temp{ &arac };

		out << *temp;

		return out;
	}

public:

	// Constructor. Kontroller ata sinifta yapiliyor
	AcikKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Kamyon{ aracTuruStr, liste, plaka, driver } {
	}

	// Turetilmis sinif oldugu icin
	virtual ~AcikKasa() = default;

private:

};

class KapaliKasa :public Kamyon {

	// Kapali kasa kamyonet sinifi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const KapaliKasa& arac) {

		// Base class pointer'i ile onun operatorune erisiliyor ve ekleme yapiyor
		const Kamyon* temp{ &arac };

		out << *temp;
		out << "Toplam hacim: " << arac.getHacim() << endl;

		return out;
	}

public:

	// Consturctor. Listeyi kontrol ediyor
	KapaliKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Kamyon{ aracTuruStr, liste, plaka, driver } {

		// Yygun araliktaysa listeye ekliyor
		// Degilse bos liste olusturuluyor constructorda
		this->setYukListesi(liste);
	}

	// Turetilmis sinif oldugu icin
	virtual ~KapaliKasa() = default;

	// Kapali kasa icin to string metodu
	virtual string toStr() const override {

		// Ata siniftan aldigina ekleme yapiyor
		string temp{ Kamyon::toStr() };
		temp += "Toplam hacim: ";
		temp += to_string(this->getHacim());
		temp += '\n';

		return temp;
	}

	// Kontrol edip listeyi atiyor
	virtual void setYukListesi(list<Yuk> liste) override {

		// Toplam hacmi tutacak degisken
		auto sum{ 0 };

		// Toplam hacmin hesaplanmasi
		for (Yuk& yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		// Hacmin uygun aralikta olup olmadigi kontorol ediliyor
		if (sum < MIN_HACIM || sum > MAX_HACIM) {
			throw invalid_argument("Hacim 10-30 araliginda degil");
		}

		// Uygun degerlerdeyse listeye ekliyor
		this->Kamyon::setYukListesi(liste);
	}

	// Gelen yuku kontrol edip ekliyor
	virtual void yukEkle(const Yuk& yuk) override {

		// Toplam hacmi tutacak degisken
		auto sum{ 0 };

		// Toplam hacmin hesaplanmasi
		for (Yuk& yukcuk : this->getYukListesi()) {
			sum += yukcuk.getYukHacmi();
		}

		// Son olarak yeni geleni ekliyor
		sum += yuk.getYukHacmi();

		// Hacmin uygun aralikta olup olmadigi kontorol ediliyor
		if (sum < MIN_HACIM || sum > MAX_HACIM) {
			throw invalid_argument("Hacim 10-30 m'3 arasi olmali.");
		}

		// Uygunsa yuku ekliyor
		this->Kamyon::yukEkle(yuk);
	}

	// Kapali kasa icin += operator tanimi
	virtual KapaliKasa& operator+=(const Yuk& yuk) override {

		// Uygunsa ekliyor
		yukEkle(yuk);

		return *this;
	}

private:
	const int MIN_HACIM{ KAPALI_KASA_MIN_HACIM };
	const int MAX_HACIM{ KAPALI_KASA_MAX_HACIM };
};

class SogutmaliKasa :public KapaliKasa {

	// Sogutmali kasa kamyonet sinifi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const SogutmaliKasa& arac) {

		// Base class pointer'i ile onun operatorune erisiyor ve ekleme yapiyor
		const KapaliKasa* temp{ &arac };

		out << *temp;
		out << "Kamyonet sicakligi: " << arac.getKasaSicakligi() << endl;

		return out;
	}

public:

	// Consturctor. Listeyi kontrol ediyor
	SogutmaliKasa(string aracTuruStr, list<Yuk>& liste, string plaka, string driver, int sicaklik) :
		KapaliKasa{ aracTuruStr, liste, plaka, driver },
		kasaSicakligi{ sicaklik } {

		// Uygun araliktaysa listeye ekliyor
		// Degilse bos liste olusturuluyor constructorda
		this->setYukListesi(liste);
	}

	// Turetilmis sinif oldugu icin
	virtual ~SogutmaliKasa() = default;

	// Sogutmali kasa icin to string metodu
	virtual string toStr() const override {

		// Temp string olusturup ata siniftan aldigina ek yapiyor
		string temp{ KapaliKasa::toStr() };
		temp += "Kamyonet sicakligi: ";
		temp += to_string(this->getKasaSicakligi());
		temp += '\n';
		return temp;
	}

	// Sicaklik kontrolu ile listeye atiyor
	virtual void setYukListesi(list<Yuk> liste) override {

		// Sicaklik kontrolu yapiyor
		if (kasaSicakligi > MAX_SICAKLIK || kasaSicakligi < MIN_SICAKLIK) {
			throw invalid_argument("Sicaklik degeri uygun aralikta degil.");
		}

		// Uygunsa listeyi atiyor
		KapaliKasa::setYukListesi(liste);
	}

	// Kasa sicakligi icin getter metot
	int getKasaSicakligi() const {
		return kasaSicakligi;
	}

	// Kasa sicakligi icin setter metot
	void setKasaSicakligi(int sicaklik) {

		// Sicaklik kontrolu yapiyor
		// Kasa ici bossa yuklere bir sey olmayacagi icin sorun yok
		if (!(this->bosMu()) && (MAX_SICAKLIK < sicaklik || MIN_SICAKLIK > sicaklik)) {
			throw invalid_argument("Girilen sicaklik degeri uygun aralikta degil.");
		}

		// Uygun ise atiyor
		kasaSicakligi = sicaklik;
	}

private:
	int kasaSicakligi;
	const int MIN_SICAKLIK{ SOGUTMALI_KASA_MIN_SICAKLIK };
	const int MAX_SICAKLIK{ SOGUTMALI_KASA_MAX_SICAKLIK };
};

class Tir :public Arac {

	// Tir sinifi icin << operator tanimi
	friend ostream& operator<<(ostream& out, const Tir& arac) {

		// Base class pointer'i ile onun operatorune erisiyor ve ekleme yapiyor
		const Arac* temp{ &arac };

		out << *temp;
		out << "Toplam agirik: " << arac.getAgirlik() << endl;
		out << "Toplam hacim: " << arac.getHacim() << endl;
		out << "Dorse kodu: " << arac.getDorse() << endl;

		return out;
	}

public:

	// Constructor. Dorse kodu icin yer aliyor
	Tir(const char* oDorse, string aracTuruStr, list<Yuk>& liste, string plaka, string driver) :
		Arac{ aracTuruStr, liste, plaka, driver } {

		// Uzunlugu tespit etme ve o uzunlukta yer alma
		dorseLen = strlen(oDorse);
		dorse = new char[dorseLen];

		// Yer alirken hata olusursa exception firlatiyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		// Alinnan yere veriyi kopyaliyor
		memcpy(dorse, oDorse, dorseLen);

		// Listeyi atiyor. Hata olursa iceride olacak
		setYukListesi(liste);
	}

	// Virtual destructor
	virtual ~Tir() {

		// Pointer dolu mu diye bakiyor, dolu ise bosaltiyor
		if (dorse) {
			delete[] dorse;
		}

		// Bosalttigi yer nullptr atiyor
		dorse = nullptr;
	}

	// Copy constructor
	Tir(const Tir& o) :
		Arac{ o.getAracTuru(), o.getYukListesi(), o.getPlaka() },
		dorseLen{ o.dorseLen } {

		// Yer aliyor
		dorse = new char[dorseLen];

		// Aldigi yer alinabilmis mi diye bakiyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		// Aldigi yere veriyi atiyor
		memcpy(dorse, o.dorse, dorseLen);

		// Diger veri uyelerini kopyaliyor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	// Move constructor
	Tir(Tir&& o) noexcept :
		Arac{ o.getAracTuru(), o.getYukListesi(), o.getPlaka() },
		dorseLen{ o.dorseLen },
		dorse{ o.dorse } {

		// Eskisini sifirliyor
		o.dorse = nullptr;
		o.dorseLen = 0;

		// Diger veri uyelerini kopyaliyor
		this->setAracTuru(o.getAracTuru());
		this->setPlaka(o.getPlaka());
		this->setSofor(o.getSofor());
		this->setYukListesi(o.getYukListesi());
	}

	// Copy assignment operator
	Tir& operator=(const Tir& o) {

		// Self assignment kontrolu yapiyor
		if (this != &o) {

			// Yer alinmissa birakiyor
			if (dorse) {
				delete[] dorse;
			}

			// Boyutunu kopyaliyor o boyutta yer aliyor
			dorseLen = o.dorseLen;
			dorse = new char[dorseLen];

			// Aldigi yeri alabilmis mi diye bakiyor
			if (nullptr == dorse) {
				throw ("Yer alinirken hata olustu.");
			}

			// Aldigi yere veriyi atiyor
			memcpy(dorse, o.dorse, dorseLen);

			// Diger veri uyelerini kopyaliyor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		return *this;
	}

	// Move assignment operator
	Tir& operator=(Tir&& o) noexcept {

		// Self assignment kontrolu
		if (this != &o) {

			// Daha once yer alinmis mi diye bakiyor
			if (dorse) {
				delete[] dorse;
			}

			// Verileri kopyaliyor
			dorseLen = o.dorseLen;
			dorse = o.dorse;

			// Eski verileri sifirliyor
			o.dorseLen = 0;
			o.dorse = nullptr;

			// Diger veri uyelerini kopyaliyor
			this->setAracTuru(o.getAracTuru());
			this->setPlaka(o.getPlaka());
			this->setSofor(o.getSofor());
			this->setYukListesi(o.getYukListesi());
		}

		return *this;
	}

	// Tir icin to string metodu
	virtual string toStr() const override {
		string temp{ Arac::toStr() };
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

	// Hacmi kontrol edip uygunsa ekliyor
	virtual void setYukListesi(list<Yuk> liste) override {

		// Toplam hacim degerini tutacak degisken
		auto sum{ 0 };

		// Toplam hacim degerinin hesaplanmasi
		for (Yuk& yuk : liste) {
			sum += yuk.getYukHacmi();
		}

		// Uygun aralikta degilse exception firlatiyor
		if (sum > MAX_HACIM || sum < MIN_HACIM) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		// Uygun aralikta ise ekliyor
		this->Arac::setYukListesi(liste);
	}

	// Gelen yuku kontrol edip ekleyen metot
	virtual void yukEkle(const Yuk& yukcuk) override {

		// Toplam hacim degerini tutacak degisken
		auto sum{ 0 };

		// Toplam hacim degerinin hesaplanmasi
		for (Yuk& yuk : this->getYukListesi()) {
			sum += yuk.getYukHacmi();
		}

		// Son olarak yeni geleni ekliyor
		sum += yukcuk.getYukHacmi();

		// Uygun aralikta degilse exception firlatiyor
		if (sum > MAX_HACIM || sum < MIN_HACIM) {
			throw invalid_argument("Hacim uygun aralikta degil.");
		}

		// Uygun aralikta ise ekliyor
		this->Arac::yukEkle(yukcuk);
	}

	// Tir sinifi icin += operator tanimi
	virtual Tir& operator+=(const Yuk& yuk) override {

		// Uygunsa ekliyor
		yukEkle(yuk);

		return *this;
	}

	// Bos olup olmadigini kontrol eder
	// Bos ise true dondurur
	virtual bool bosMu() override final {
		return (0 == this->getYukListesi().size());
	}

	// Dorse icin getter metot
	string getDorse() const {

		// Temp string olusturuyor
		string temp{ "" };

		// Temp'e char olarak sirayla atiyor ve donduruyor 
		for (auto i{ 0 }; i < dorseLen; ++i) {
			temp += dorse[i];
		}

		return temp;
	}

	// Dorse icin setter metot
	void setDorse(char* text) {

		// Verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		// Boyutunu alip ona gore yer aliyor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		// Aldigi yer alinabilmis mi diye bakiyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		// Aldigi yere veriyi atiyor
		memcpy(dorse, text, dorseLen);
	}

	// Dorse icin parametre olarak const char pointer'i alan metot
	void setDorse(const char* text) {

		// Verisi varsa siliyor
		if (dorse) {
			delete[] dorse;
		}

		// Boyutunu alip ona gore yer aliyor
		dorseLen = strlen(text);
		dorse = new char[dorseLen];

		// Aldigi yer alinabilmis mi diye bakiyor
		if (nullptr == dorse) {
			throw ("Yer alinirken hata olustu.");
		}

		// Aldigi yere veriyi atiyor
		memcpy(dorse, text, dorseLen);
	}

private:
	const int MIN_HACIM{ TIR_MIN_HACIM };
	const int MAX_HACIM{ TIR_MAX_HACIM };
	char* dorse;
	int dorseLen;
};

int main() {

	// Ad hacim agirlik tur
	// Yuklerin tanimi
	Yuk y1{ "elma yuk1", 10, 750, 2 };
	Yuk y2{ "armut yuk2", 15, 500, 3 };
	Yuk y3{ "kiraz yuk3", 10, 500, 1 };
	Yuk y4{ "kalem yuk4", 15, 750, 1 };
	Yuk y5{ "gitar yuk5", 15, 1000, 2 };
	Yuk y6{ "araba yuk6", 3, 1000, 3 };
	Yuk y7{ "karpuz yuk7", 1, 500, 2 };

	// Listeler tanimi
	list<Yuk> list1{ y1, y2, y3, y4, y5 };
	list<Yuk> list2{ y1, y1, y1, y1, y1 };
	list<Yuk> list3{ y2, y2, y2, y2, y2 };
	list<Yuk> list4{ y3, y3, y3, y3, y3 };
	list<Yuk> list5{ y4, y4, y4, y4, y4 };

	// Tira eklenecek yukler
	list<Yuk> list6;
	for (auto i{ 0 }; i < 10; ++i) {
		list6.push_back(y6);
	}

	// Arac pointer vector tanimi
	// Bu sayede calisma zamaninda hangi tur geleceginin bilinmesine gerek yok
	vector<Arac*> aracPtr;

	{
		// 1
		try {
			aracPtr.push_back(new Kamyon{ "Kamyon", list1, "34LG1780", "Efe Kaya" });
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}
		// 2
		try {
			aracPtr.push_back(new Kamyon{ "Kamyon", list2, "41PS3737", "Dilara Yonev" });
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
			aracPtr.push_back(new AcikKasa{ "Acik Kasa Kamyonet", list1, "24KGB171", "Fatma Akgun" });
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
			aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list1, "08MI6692", "Ethem Yilmaz", -20 });
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}
		// 8
		try {
			aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list2, "16MI5111", "Burcu Sahbaz", -25 });
		}
		catch (const std::exception& e) {
			cout << e.what() << endl;
		}
		// 9
		try {
			aracPtr.push_back(new SogutmaliKasa{ "Sogutmali Kasa Kamyonet", list3, "06FBI137", "Fikri Elci", -5 });
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

	}

	for (Arac* araba : aracPtr) {
		cout << *araba << endl;
	}

	// Calistirinca olmasi gerektigi gibi bazilarinda hatalar veriyor

	cout << "###########" << endl;
	cout << "YUK EKLENECEK TIR................" << endl;
	cout << "###########" << endl << endl;
	cout << *aracPtr[5] << endl;
	// Tira 10 adet yuk yukleme
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

	// Var olan yuk listesi
	cout << "###########" << endl;
	cout << "YUK LISTESI.............." << endl;
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << endl << "###########" << endl;

	// Burada icinde 20 yuk olmus oluyor
	// Yazdirirken goruntu kirliligi yapacagi icin 6 taneye dusurdum
	// Eksiltmelerle birlikte sonunda 3 tane kalacak
	auto index{ 11 };
	for (auto i{ 0 }; i < 7; ++i) {
		aracPtr[5]->yukBosalt(index--);
		aracPtr[5]->yukBosalt(1);
	}

	// Alfabetik siraliyor ardindan 3. elemani cikartiyor
	cout << "ALFABETIK SIRALAMA......................" << endl;
	aracPtr[5]->yukSirala(Arac::adinaGore);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();
	cout << "###########" << endl;
	cout << "EKSILTME......................" << endl;
	aracPtr[5]->yukBosalt(3);
	cout << "###########" << endl << endl;
	aracPtr[5]->printYukListesi();

	// Agirliga gore siraliyor ve 3. elemani cikartiyor
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

	// Hacme gore siraliyor ve 3. elemani cikartiyor
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
