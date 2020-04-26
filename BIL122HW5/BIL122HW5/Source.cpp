//Bekir Öztürk
//19120205061

#include <iostream>
#include "Str.h"

using namespace std;

int main() {
	Str a;
	Str b("ahmet");

	cout << "A: ";
	cin >> a;

	cout << "copy constructor a to c" << endl;
	Str c(a);
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "b.at(3): " << b.at(3) << endl;
	cout << "b==a: " << (b == a) << endl;
	cout << "b!=a: " << (b != a) << endl;
	cout << "b<a: " << (b < a) << endl;
	cout << "b>a: " << (b > a) << endl;
	cout << "b<=a: " << (b <= a) << endl;
	cout << "b>=a: " << (b >= a) << endl<<endl;

	cout << "a=b" << endl;
	a = b;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "c+=a" << endl;
	c += a;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "c+=\" deneme3\"" << endl;
	c += " deneme3";
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "a= \"deneme5\"" << endl;
	a = "deneme5";
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "a = b + c" << endl;
	a = b + c;	
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "b = b + \"deneme13\"" << endl;
	b = b + "deneme13";
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;

	cout << "c = \"deneme22\" + c" << endl;
	c = "deneme22"+c;
	cout << "a: " << a << endl;
	cout << "b: " << b << endl;
	cout << "c: " << c << endl << endl;
	cout << "deneme" << endl;


	return 0;
}