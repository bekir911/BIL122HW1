#pragma once
#include <string>

using namespace std;

class Complex{

	string boslukSil(const string& str); //a function that deletes the spaces in a string

	bool sayiMi(const string& str);

public:

	Complex(const int& re); //2 basic type conversion constructor

	Complex(const string& str); //4 conversion constructor that takes a string as parameter

	Complex(double re = 0, double im = 0); //1, 3, 5 Default, conversion and 2-parameter constructor

	double getRe() const; //6. getter function for reel part

	double getIm() const; //6. getter function for imaginary part 

	bool setRe(double re); //6. setter function for reel part

	bool setIm(double im); //6. setter function for imaginary part

	void printComplex(); //10. prints the complex number in a+bi form

	void add(Complex& value); //7 adds a complex number to another one

	void subtract(Complex& value);  //8 subtracts a complex number from itself

	void divide(Complex& value); //9 divides itself by a complex number 

private:
	double re; //reel part
	double im; //imaginary part
};

