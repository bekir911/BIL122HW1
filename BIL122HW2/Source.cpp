//Bekir Öztürk
//19120205061
//BIL 122 Ödev-2

#include "Complex.h"
#include <iostream>
#include <vector>

using namespace std;

void sortComplex(vector<Complex>& victor) {

	cout << endl << "Sorting for reel part" << endl << endl;

	int size = victor.size();

	for (int i = 0; i < size - 1; ++i) { // bubble sort for reel part
		for (int j = 0; j < size - i - 1; ++j) {
			if (victor[j].getRe() < victor[j + 1].getRe()) { //sorts from big to small
				Complex temp = victor[j + 1];
				victor.erase(victor.begin() + j + 1);
				victor.insert(victor.begin() + j, temp);
			}
		}
	}

	for (int i = 0; i < size; ++i) { //prints compex numbers
		victor[i].printComplex();
	}

	cout << endl << "Sorting for imaginary part" << endl << endl;

	for (int i = 0; i < size - 1; ++i) { // bubble sort for imaginary part
		for (int j = 0; j < size - i - 1; ++j) {
			if (victor[j].getIm() < victor[j + 1].getIm()) { //sorts from big to small
				Complex temp = victor[j + 1];
				victor.erase(victor.begin() + j + 1);
				victor.insert(victor.begin() + j, temp);
			}
		}
	}

	for (int i = 0; i < size; ++i) { //prints complex numbers
		victor[i].printComplex();
	}
}

int main() {

	Complex c1; //1
	cout << "c1 ";
	c1.printComplex(); //10

	Complex c2(-6); //2
	cout << "c2 ";
	c2.printComplex();

	double pi = 3.14;
	Complex c3(pi); //3
	cout << "c3 ";
	c3.printComplex();

	Complex c4(1.618033); //3
	cout << "c4 ";
	c4.printComplex();

	string str(" 5 +3 i"); //4
	Complex c5(str);
	cout << "c5 ";
	c5.printComplex();

	Complex c6("gfdgg"); //4
	cout << "c6 ";
	c6.printComplex();

	Complex c7(-3, -7); //5
	cout << "c7 ";
	c7.printComplex();

	Complex c8(" 37 +7i");
	cout << "c8 ";
	c8.printComplex();

	Complex c9(2.718281);
	cout << "c9 ";
	c9.printComplex();

	cout << "c5's reel part is: " << c5.getRe() << endl; //6

	c2.add(c3); //7
	cout << "c2 + c3 ";
	c2.printComplex();

	c5.subtract(c7); //8
	cout << "c5 - c7 ";
	c5.printComplex();

	c2.divide(c3); //9
	cout << "c2 / c3 ";
	c2.printComplex();

	cout << endl;

	c4.divide(c1);
	cout << "c4 / c1 ";
	c4.printComplex();

	vector <Complex> victor;

	victor.push_back(c1);
	victor.push_back(c2);
	victor.push_back(c3);
	victor.push_back(c4);
	victor.push_back(c5);
	victor.push_back(c6);
	victor.push_back(c7);
	victor.push_back(c8);
	victor.push_back(c9);

	sortComplex(victor);

	Complex anan("i");

	return 0;
}