#include "Complex.h"
#include <iostream>

string Complex::boslukSil(const string& str) { //parametre olarak string alýr ve içindeki boþluk olan karakterleri siler
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

bool Complex::sayiMi(const string& str) { //parametre olarak string alýr ve tamamen sayýlardan oluþup oluþmadýðýný kontrol eder
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

Complex::Complex(const int& re) { //2 iþlevini yerine getirir
	setRe(re);
	setIm(0);
}

Complex::Complex(const string& str) { //4 iþlevini yerine getirir
	setIm(0); //deðerleri sýfýr olarak atar
	setRe(0);

	string copyStr = boslukSil(str); //burda copyStr stringi boþluklardan arýnmýþ þekilde

	int isaretci = 0; // (+/-) iþareti indexini tutar
	int isaretVarMi = 0; //isaret varsa 1 deðeri alýr

	if (copyStr.length() == 0) { //veri girilmediyse
		return;
	}

	for (isaretci = copyStr.length(); isaretci >= 0; --isaretci) { //(+/-) iþareti olup olmadýný kontrol eder. varsa deðiþken ile bildirir
		if (copyStr[isaretci] == '+' || copyStr[isaretci] == '-') {
			++isaretVarMi;
			break;
		}
	}

	//isaretci deðiþkeninde kullanýlan iþaretin (+/-) indexi var

	if (isaretVarMi == 0) { //uygun metin girilmediyse yapýcýyý sonlandýrýr. deðerler sýfýr olarak atanmýþ olur
		if (copyStr[0] == 'i') { //sadece i olan veri alýnýrsa
			setIm(1);
			return;
		}
		else if (copyStr.back() == 'i') { //ai formatýnda veri alýnýrsa
			setIm(stod(copyStr));
			return;
		}
		else if (sayiMi(copyStr)) { //girilen veri tamamen sayýdan oluþuyorsa
			setRe(stod(copyStr));
			return;
		}
		return; // girilen veri geçersiz ise
	}

	if (isaretci == 0) {
		if (copyStr.back() == 'i') {
			if (copyStr.length() == 2) { //girilen veri -i ise
				setIm(-1);
				return;
			}
			else { //girilen veri -bi þeklinde ise
				setIm(stod(copyStr));
				return;
			}
		}
		else { //girilen veri -a þeklinde ise
			setRe(stod(copyStr));
			return;
		}
	}

	else if (isaretci == -1) {
		if (copyStr[0] == 'i') { //girilen veri i ise
			setRe(1);
			return;
		}
		else if (copyStr.back() == 'i') { //girilen veri bi þeklinde ise
			setRe(stod(copyStr));
			return;
		}
		else {
			cout << "hata 102 Complex.cpp" << endl;
		}
	}

	if (isaretci == copyStr.length() - 2 && copyStr[copyStr.length() - 1] == 'i') {
		if (copyStr[isaretci] == '-') {
			if (copyStr.back() == 'i') { //a-i ya da -a-i þeklinde ise
				setIm(-1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else if (copyStr[isaretci] == '+') {
			if (copyStr.back() == 'i') { //a+i ya da -a+i þeklinde ise
				setIm(1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else {
			cout << "hata oldu satir 122 Complex.cpp " << endl; //hata olursa tespit etmek için
			return;
		}
	}

	if (copyStr.front() == 'i') { //i(+/-)a þeklinde ise
		setIm(1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}
	else if (copyStr[1] == 'i' && copyStr.front() == '-') { //-i(+/-)a þeklinde ise
		setIm(-1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}

	//özel durumlardan hiçbiri geçerli olmadýysa buraya gelir

	string reelStr = copyStr.substr(0, isaretci); //aradaki iþarete göre reel ve imaginary kýsým ayrýlýr
	string imgStr = copyStr.substr(isaretci);

	if (copyStr.back() == 'i') { //a(+/-)bi þeklinde ise
		setRe(stod(reelStr));
		setIm(stod(imgStr));
	}
	else {
		setRe(stod(imgStr)); //bi(+/-)a þeklinde ise
		setIm(stod(reelStr));
	}
}

Complex::Complex(double re, double im) { //1, 3, 5 numaralý iþlevleri yerine getirir
	setRe(re);
	setIm(im);
}

double Complex::getRe() const { //6 numaralý iþlevi yerine getirir
	return re;
}

double Complex::getIm() const { //6 numaralý iþlevi yerine getirir 
	return im;
}

bool Complex::setRe(double re) { //6 numaralý iþlevi yerine getirir
	this->re = re;
	return true;
}

bool Complex::setIm(double im) { //6 numaralý iþlevi yerine getirir
	this->im = im;
	return true;
}

void Complex::printComplex() { //10 numaralý iþlevi yerine getirir
	cout << "Complex number: ";
	if (im >= 0) { //imaginary kýsým pozitif ise artý iþareti ile bastýrýr
		cout << getRe() << "+" << getIm() << "i" << endl;
	}
	else { //pozitif deðilse signed double olduðu için iþaretini kendi bastýrýr
		cout << getRe() << getIm() << "i" << endl;
	}
}

void Complex::add(Complex& value) { //7 numaralý iþlevi yerine getirir
	setRe(re + value.re);
	setIm(im + value.im);
}

void Complex::subtract(Complex& value) { //8 numaralý iþlevi yerine getirir
	setRe(re - value.re);
	setIm(im - value.im);
}

void Complex::divide(Complex& value) { //9 numaralý iþlevi yerine getirir
	// kaðýt üzerinde a+bi ve c+di olarak yazýp paydadayý eþlenik ile çarpýp hesapladým
	double reelValue = (re * value.re + im * value.im) / (value.re * value.re + value.im * value.im);
	double imgValue = (im * value.re - re * value.im) / (value.re * value.re + value.im * value.im);
	setRe(reelValue);
	setIm(imgValue);
}


