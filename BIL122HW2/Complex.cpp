#include "Complex.h"
#include <iostream>

string Complex::boslukSil(const string& str) { //takes a string as parameter then deletes the spaces in it
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

bool Complex::sayiMi(const string& str) { //takes a string as parameter and checks whether its made up with only numbers or not
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

Complex::Complex(const int& re) { //2 constructor that takes an integer as parameter
	setRe(re);
	setIm(0);
}

Complex::Complex(const string& str) { //4 constructor that takes a string as parameter
	setIm(0); //assigns the values as zero
	setRe(0);

	string copyStr = boslukSil(str); //copyStr is now free from spaces

	int isaretci = 0; // (+/-) holds the index of the sign
	int isaretVarMi = 0; //if theres a sign it becomes 1

	if (copyStr.length() == 0) { //if the string is empty
		return;
	}

	for (isaretci = copyStr.length(); isaretci >= 0; --isaretci) { //(+/-) checks if theres a sign. if theres a sign the variable becomes 1
		if (copyStr[isaretci] == '+' || copyStr[isaretci] == '-') {
			++isaretVarMi;
			break;
		}
	}

	// isaretci variable holds index of sign (+/-)

	if (isaretVarMi == 0) { //checks if  if the string is incorrect constructor ends. values would be assigned 0
		if (copyStr[0] == 'i') { //if the string includes only "i"
			setIm(1);
			return;
		}
		else if (copyStr.back() == 'i') { //if its in "ai" format
			setIm(stod(copyStr));
			return;
		}
		else if (sayiMi(copyStr)) { //if the string is made up with only numbers
			setRe(stod(copyStr));
			return;
		}
		return; //if the string is incorrect it ends
	}

	if (isaretci == 0) {
		if (copyStr.back() == 'i') {
			if (copyStr.length() == 2) { //if the string includes only "-i"
				setIm(-1);
				return;
			}
			else { //if its in "-bi" format
				setIm(stod(copyStr));
				return;
			}
		}
		else { //if its in "-a" format
			setRe(stod(copyStr));
			return;
		}
	}

	else if (isaretci == -1) {
		if (copyStr.back() == 'i') { //if its in "bi" format
			setRe(stod(copyStr));
			return;
		}
		else {
			cout << "Error line 99 Complex.cpp" << endl;
			return;
		}
	}

	if (isaretci == copyStr.length() - 2 && copyStr[copyStr.length() - 1] == 'i') {
		if (copyStr[isaretci] == '-') {
			if (copyStr.back() == 'i') { //if its in "a-i" or "-a-i" format
				setIm(-1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else if (copyStr[isaretci] == '+') {
			if (copyStr.back() == 'i') { //if its in "a+i" or "-a+i" format
				setIm(1);
				setRe(stod(copyStr.substr(0, isaretci)));
				return;
			}
		}
		else {
			cout << "Error line 120 Complex.cpp " << endl; //to check if an error occurs
			return;
		}
	}

	if (copyStr.front() == 'i') { //if its in "i-a" or "i+a" format
		setIm(1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}
	else if (copyStr[1] == 'i' && copyStr.front() == '-') { //if its in "-i-a" or "-i+a" format
		setIm(-1);
		setRe(stod(copyStr.substr(isaretci)));
		return;
	}

	//if nothing special happened it comes down here

	string reelStr = copyStr.substr(0, isaretci); //seperates while considering the sign
	string imgStr = copyStr.substr(isaretci);

	if (copyStr.back() == 'i') { //if its in "a+bi" or "a-bi" format
		setRe(stod(reelStr));
		setIm(stod(imgStr));
	}
	else { //if its in "bi+a" or "bi-a" format
		setRe(stod(imgStr));
		setIm(stod(reelStr));
	}
}

Complex::Complex(double re, double im) { //1, 3, 5 default constructor/conversion constructor/ 2 parameter constructor
	setRe(re);
	setIm(im);
}

double Complex::getRe() const { //6 getter function for reel part
	return re;
}

double Complex::getIm() const { //6 getter function for imaginary part
	return im;
}

bool Complex::setRe(double re) { //6 setter function for reel part
	this->re = re;
	return true;
}

bool Complex::setIm(double im) { //6 setter function for imaginary part
	this->im = im;
	return true;
}

void Complex::printComplex() { //10 prints the compex number
	cout << "Complex number: ";
	if (im >= 0) { //if imaginary part is positive prints the plus sign 
		cout << getRe() << "+" << getIm() << "i" << endl;
	}
	else { //if its not positive it prints its own sign because its a signed double
		cout << getRe() << getIm() << "i" << endl;
	}
}

void Complex::add(Complex& value) { //7 takes a complex number as parameter then adds it to itself
	setRe(re + value.re);
	setIm(im + value.im);
}

void Complex::subtract(Complex& value) { //8 takes a complex number as parameter then subtructs from itself
	setRe(re - value.re);
	setIm(im - value.im);
}

void Complex::divide(Complex& value) { //9 takes a complex number as parameter then divides itself by it
	// I made the calculations on a paper. considered the complex numbers as a+bi and c+di then multiplied by its conjugate

	if (0 == value.re && 0 == value.im) {
		cout << "Cant divide by zero" << endl;
		return;
	}
	double reelValue = (re * value.re + im * value.im) / (value.re * value.re + value.im * value.im);
	double imgValue = (im * value.re - re * value.im) / (value.re * value.re + value.im * value.im);
	setRe(reelValue);
	setIm(imgValue);
}
