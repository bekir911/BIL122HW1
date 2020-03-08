#include "Complex.h"
#include <iostream>

string Complex::boslukSil(const string& str) { //parametre olarak string al�r ve i�indeki bo�luk olan karakterleri siler
	string copyStr = ("");
	int length = str.length();
	int index = 0;
	string bosluk = { " " };
	while (length > 0) {
		if (str[index] != bosluk[0]) {
			copyStr = copyStr + str[index];
		}
		--length;
		++index;
	}
	return copyStr;
}

bool Complex::sayiMi(const string& str) { //parametre olarak string al�r ve tamamen say�lardan olu�up olu�mad���n� kontrol eder
	int tutucu = 0;
	int strLength = str.length();
	for (int i = 0; i < strLength; ++i) {
		if (!(str[i] - 48 >= 0 && str[i] - 48 <= 9)) {
			++tutucu;
		}
	}
	if (tutucu == 0) {
		return true;
	}
	return false;
}

Complex::Complex(const int& re) { //2 i�levini yerine getirir
	setRe(re);
	setIm(0);
}

Complex::Complex(const string& str) { //4 i�levini yerine getirir
	setIm(0); //de�erleri s�f�r olarak atar
	setRe(0);

	string copyStr = boslukSil(str); //burda copyStr stringi bo�luklardan ar�nm�� �ekilde

	int isaretci = 0; // (+/-) i�areti indexini tutar
	int isaretVarMi = 0; //isaret varsa 1 de�eri al�r

	if (copyStr.length() == 0) { //veri girilmediyse
		return;
	}

	for (isaretci = copyStr.length(); isaretci >= 0; --isaretci) { //(+/-) i�areti olup olmad�n� kontrol eder. varsa de�i�ken ile bildirir
		if (copyStr[isaretci] == '+' || copyStr[isaretci] == '-') {
			++isaretVarMi;
			break;
		}
	}

	//isaretci de�i�keninde kullan�lan i�aretin (+/-) indexi var

	if (isaretVarMi == 0) { //uygun metin girilmediyse yap�c�y� sonland�r�r. de�erler s�f�r olarak atanm�� olur
		if (copyStr[0] == 'i') { //sadece i olan veri al�n�rsa
			setIm(1);
			return;
		}
		else if (copyStr.back() == 'i') { //ai format�nda veri al�n�rsa
			setIm(stod(copyStr));
			return;
		}
		else if (sayiMi(copyStr)) { //girilen veri tamamen say�dan olu�uyorsa
			setRe(stod(copyStr));
			return;
		}
		return; // girilen veri ge�ersiz ise
	}

	if (isaretci == 0) {
		if (copyStr.back() == 'i') {
			if (copyStr.length() == 2) { //girilen veri -i ise
				setIm(-1);
				return;
			}
			else { //girilen veri -bi �eklinde ise
				setIm(stod(copyStr));
				return;
			}
		}
		else { //girilen veri -a �eklinde ise
			setRe(stod(copyStr));
			return;
		}
	}

	else if (isaretci == -1) {
		if (copyStr[0] == 'i') { //girilen veri i ise
			setRe(1);
			return;
		}
		else if (copyStr.back() == 'i') { //girilen veri bi �eklinde ise
			setRe(stod(copyStr));
			return;
		}
		else {
			cout << "hata 102 Complex.cpp" << endl;
		}
	}

	if (isaretci == copyStr.length() - 2 && copyStr[copyStr.length() - 1] == 'i') {
		if (copyStr[isaretci] == '-') {
			if (copyStr.back() == 'i') { //a-i ya da -a-i �eklinde ise
				setIm(-1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else if (copyStr[isaretci] == '+') {
			if (copyStr.back() == 'i') { //a+i ya da -a+i �eklinde ise
				setIm(1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else {
			cout << "hata oldu satir 122 Complex.cpp " << endl; //hata olursa tespit etmek i�in
			return;
		}
	}

	if (copyStr.front() == 'i') { //i(+/-)a �eklinde ise
		setIm(1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}
	else if (copyStr[1] == 'i' && copyStr.front() == '-') { //-i(+/-)a �eklinde ise
		setIm(-1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}

	//�zel durumlardan hi�biri ge�erli olmad�ysa buraya gelir

	string reelStr = copyStr.substr(0, isaretci); //aradaki i�arete g�re reel ve imaginary k�s�m ayr�l�r
	string imgStr = copyStr.substr(isaretci);

	if (copyStr.back() == 'i') { //a(+/-)bi �eklinde ise
		setRe(stod(reelStr));
		setIm(stod(imgStr));
	}
	else {
		setRe(stod(imgStr)); //bi(+/-)a �eklinde ise
		setIm(stod(reelStr));
	}
}

Complex::Complex(double re, double im) { //1, 3, 5 numaral� i�levleri yerine getirir
	setRe(re);
	setIm(im);
}

double Complex::getRe() const { //6 numaral� i�levi yerine getirir
	return re;
}

double Complex::getIm() const { //6 numaral� i�levi yerine getirir 
	return im;
}

bool Complex::setRe(double re) { //6 numaral� i�levi yerine getirir
	this->re = re;
	return true;
}

bool Complex::setIm(double im) { //6 numaral� i�levi yerine getirir
	this->im = im;
	return true;
}

void Complex::printComplex() { //10 numaral� i�levi yerine getirir
	cout << "Complex number: ";
	if (im >= 0) { //imaginary k�s�m pozitif ise art� i�areti ile bast�r�r
		cout << getRe() << "+" << getIm() << "i" << endl;
	}
	else { //pozitif de�ilse signed double oldu�u i�in i�aretini kendi bast�r�r
		cout << getRe() << getIm() << "i" << endl;
	}
}

void Complex::add(Complex& value) { //7 numaral� i�levi yerine getirir
	setRe(re + value.re);
	setIm(im + value.im);
}

void Complex::subtract(Complex& value) { //8 numaral� i�levi yerine getirir
	setRe(re - value.re);
	setIm(im - value.im);
}

void Complex::divide(Complex& value) { //9 numaral� i�levi yerine getirir
	// ka��t �zerinde a+bi ve c+di olarak yaz�p paydaday� e�lenik ile �arp�p hesaplad�m
	double reelValue = (re * value.re + im * value.im) / (value.re * value.re + value.im * value.im);
	double imgValue = (im * value.re - re * value.im) / (value.re * value.re + value.im * value.im);
	setRe(reelValue);
	setIm(imgValue);
}


