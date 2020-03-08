//Bekir Öztürk
//19120205061
//BIL 122 Ödev-2

#include "Complex.h"
#include <iostream> //main'de cout kullandýðým için gerekti

int main() {
	
	Complex ahmet; //1
	ahmet.printComplex(); //10

	Complex ahmet1(-6); //2
	ahmet1.printComplex();

	double aa = 3.14;
	Complex ahmet2(aa); //3
	ahmet2.printComplex();

	Complex ahmet3(1.618033); //3
	ahmet3.printComplex();

	string aa1(" 5 +3 i"); //4
	Complex ahmet4(aa1);
	ahmet4.printComplex();

	Complex ahmet6("..."); //4
	ahmet6.printComplex();

	Complex ahmet5(-3,-7); //5
	ahmet5.printComplex();
	
	cout << "Complex number's reel part is: " << ahmet5.getRe() << endl; //6

	ahmet4.add(ahmet5); //7
	ahmet4.printComplex();
	
	ahmet4.subtract(ahmet5); //8
	ahmet4.printComplex();

	ahmet4.divide(ahmet5); //9
	ahmet4.printComplex();

	return 0;
}