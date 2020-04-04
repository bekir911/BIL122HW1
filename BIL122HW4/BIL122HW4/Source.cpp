#include <iostream>
#include <vector>
#include <random>							//BEN EKLEDÝM
#include <ctime>							//BEN EKLEDÝM. RANDOM ÝÇÝN GEREKLÝYDÝ
#include "Triangle.h"
#include "Quadrilateral.h"

#include <iomanip>							//SÝL BUNU SONRA

using namespace std;

std::random_device rastgele;
std::mt19937 calis(rastgele());
std::uniform_int_distribution<std::mt19937::result_type> motor(0, 100);

// Rastgele olarak Triangle nesneleri olusturur ve parametre olarak verilen vektore ekler.
/* Triangle nesnelerinde yer alacak noktalarýn x ve y deðerleri [0, 100] arasýnda olabilir.
   Þeklin renk deðeri de rastgele olarak belirlenmelidir.
*/
void fillTriangles(vector<Triangle>& v, int numberOfItems = 100) {
	for (auto i{ 0 }; i < numberOfItems; ++i) {
		Point p1 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p2 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p3 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		try {
			auto randomColor = motor(calis) % 6;	//RENK SAYISI
			auto color = static_cast<Triangle::Color>(randomColor);
			Triangle triangle(p1, p2, p3, color);
			v.push_back(triangle);

			cout << "\ni: " << i << endl;

			cout << "a.x " << v[i].getA().x << endl;
			cout << "a.y " << v[i].getA().y << endl;
			cout << "b.x " << v[i].getB().x << endl;
			cout << "b.y " << v[i].getB().y << endl;
			cout << "c.x " << v[i].getC().x << endl;
			cout << "c.y " << v[i].getC().y << endl;

			//v[i].printInfo();
		}
		catch (invalid_argument& ex) {
			cout << "Invalid Triangle: " << ex.what() << endl;
		}
	}
}

// Rastgele olarak Quadrilateral nesneleri olusturur ve parametre olarak verilen vektore ekler.
/* Quadrilateral nesnelerinde yer alacak noktalarýn x ve y deðerleri [0, 100] arasýnda olabilir.
   Þeklin renk deðeri de rastgele olarak belirlenmelidir.
*/
void fillQuads(vector<Quadrilateral>& v, int numberOfItems = 100) {
	for (auto i{ 0 }; i < numberOfItems; ++i) {
		Point p1 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p2 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p3 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p4 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		try {
			auto randomColor = motor(calis) % 5;	//RENK SAYISI
			auto color = static_cast<Quadrilateral::Color>(randomColor);
			Quadrilateral quadrilateral(p1, p2, p3, p4, color);
			v.push_back(quadrilateral);
		}
		catch (invalid_argument& ex) {
			cout << "Invalid Quadrilateral: " << ex.what() << endl;
		}
	}

}


///* Verilen Triangle veya Rectangle vektörününde çevre uzunluðu ve renk deðeri eþleþen ilk elemanýn indeksini döndürür.
//Eleman bulunamazsa -1 döndürülür.*/
//template<class T>
//int search(const vector<T>& v, const T& key) {
//	auto perimeter{ key.getPerimeter() };
//	auto size{ v.size() };
//	auto colorA = static_cast<typename T::Color>(key.getColor());
//	for (size_t i{ 0 }; i < size; ++i) {
//		auto colorB = static_cast<typename T::Color>(v[i].getColor());
//		if (v[i].getPerimeter() == perimeter && colorB == colorA) {
//			return i;
//		}
//	}
//	return -1;
//}

template<class T>
int sortByPerimeter(vector<T>& v) {
	auto size{ v.size() };
	auto kopya = vector<T>{};
	auto bosluk = vector<T>{};
	auto bosluk2 = vector<T>{};
	auto bosluk3 = vector<T>{};

	//copy(v.begin(), v.end(), back_inserter(kopya));

	//for (const auto index : kopya) {

	for (int i{ 0 }; i < v.size(); ++i) {


		/*double a1 = kopya[i].getA().x;				DURUMA GÖRE YORUMA ALIP KALDIRABÝLÝRSÝNÝZ
		cout << "geta.x: " << a1 << endl;
		double a2 = kopya[i].getA().y;
		cout << "geta.y: " << a2 << endl;
		double b1 = kopya[i].getB().x;
		cout << "getb.x: " << b1 << endl;
		double b2 = kopya[i].getB().y;
		cout << "getb.y: " << b2 << endl;
		double c1 = kopya[i].getC().x;
		cout << "getc.x: " << c1 << endl;
		double c2 = kopya[i].getC().y;
		cout << "getc.y: " << c2 << endl;*/

		for (const auto index : v) {
			cout << "\ngirdi i: " << i << endl;

			double a1 = index.getA().x;
			cout << "geta.x: " << a1 << endl;			//DURUMA GÖRE YORUMA ALIP KALDIRABÝLÝRSÝNÝZ
			double a2 = index.getA().y;
			cout << "geta.y: " << a2 << endl;
			double b1 = index.getB().x;
			cout << "getb.x: " << b1 << endl;
			double b2 = index.getB().y;
			cout << "getb.y: " << b2 << endl;
			double c1 = index.getC().x;
			cout << "getc.x: " << c1 << endl;
			double c2 = index.getC().y;
			cout << "getc.y: " << c2 << endl;

			/*cout << index.getA().x << endl;
			cout << index.getA().y << endl;
			cout << index.getB().x << endl;
			cout << index.getB().y << endl;
			cout << index.getC().x << endl;
			cout << index.getC().y << endl;*/
		}
	}

	//for (size_t i{ 0 }; i < size - 2; ++i) {							BURASI ASIL KODUM. TABÝÝ YAPIM AÞAMASINDAYDI
	//	for (size_t j{ 0 }; j < size - i - 2; ++j) {					HATA VERÝNCE HATAYI ÇÖZMEYE ÇALIÞIRKEN YORUMA ALDIM
	//		cout << "3: " << endl;
	//		cout << "v.size: " << v.size() << endl;
	//		if (v[j].getPerimeter() < v[j + 1].getPerimeter()) {
	//			T temp = v[j + 1];
	//			v.erase(v.begin() + j + 1);
	//			v.insert(v.begin() + j, temp);
	//		}
	//	}
	//}

	return 0;
}

//int main()
//{
//
//	// Point class test
//	auto p = Point{ 4.5, 6.2 };
//
//	cout << p.x << " " << p.y << endl;
//	cout << p.coords[0] << " " << p.coords[1] << endl;
//
//	// Sample Quad and Triangle Objects
//	auto sampleQuad = Quadrilateral{ Point(4, 5), 20, 20 };
//	cout << "Color of Sample Quad:" << sampleQuad.getColorAsString() << endl;
//
//	auto sampleTriangle = Triangle{ Point(4, 5),  Point(9, 5),  Point(14, 15) };
//	cout << "Color of Sample Triangle:" << sampleTriangle.getColorAsString() << endl;
//
//
//	// Filling vectors randomly
//	auto vectorOfQuads = vector<Quadrilateral>{};
//	auto vectorOfTriangles = vector<Triangle>{};
//
//	fillTriangles(vectorOfTriangles);
//	fillQuads(vectorOfQuads);
//
//	// Search sample objects in the corresponding vectors
//	cout << "Searching a triangle...\n";
//	cout << sampleTriangle.printInfo() << endl;
//	if (auto idx = search(vectorOfTriangles, sampleTriangle) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//	cout << "Searching a quadrilateral...\n";
//	cout << sampleQuad.printInfo() << endl;
//	if (auto idx = search(vectorOfQuads, sampleQuad) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//
//	// Add sample Triangle object to the vector and sort the vector
//	vectorOfTriangles.push_back(sampleTriangle);
//	sortByPerimeter(vectorOfTriangles);
//
//
//	// Search sample item again. Now, you must have a hit.
//	cout << "Searching a triangle...\n";
//	cout << sampleTriangle.printInfo() << endl;
//	if (auto idx = search(vectorOfTriangles, sampleTriangle) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//
//
//	// Add sample Quad object to the vector and sort the vector
//	vectorOfQuads.push_back(sampleQuad);
//	sortByPerimeter(vectorOfQuads);
//
//	// Search sample item again. Now, you must have a hit.
//	cout << "Searching a quadrilateral...\n";
//	cout << sampleQuad.printInfo() << endl;
//	if (auto idx = search(vectorOfQuads, sampleQuad) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//
//	// Invalid cases
//	try
//	{
//		auto invalidTriangle1 = Triangle{ Point{4, 0},  Point{9, 0},  Point{14, 0} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid triangle: " << ex.what() << endl;
//	}
//
//	try
//	{
//		auto invalidTriangle2 = Triangle{ Point{4, 4},  Point{4, 4},  Point{4, 4} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid triangle: " << ex.what() << endl;
//	}
//
//	try
//	{
//		auto invalidTriangle3 = Triangle{ Point{4, 0},  Point{4, 4},  Point{4, 14} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid triangle: " << ex.what() << endl;
//	}
//
//	try
//	{
//		auto invalidQuad1 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{14, 0}, Point{0, 0} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid Quad: " << ex.what() << endl;
//	}
//
//
//	try
//	{
//		auto invalidQuad1 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{14, 0}, Point{0, 0} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid Quad: " << ex.what() << endl;
//	}
//
//
//	try
//	{
//		auto invalidQuad2 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{3, 20}, Point{10, 20} };
//	}
//	catch (invalid_argument& ex)
//	{
//		cout << "Invalid Quad: " << ex.what() << endl;
//	}
//
//	return 0;
//}

int main() {
	// Sample Quad and Triangle Objects

	auto sampleTriangle = Triangle{ Point(29, 41),  Point(78, 63),  Point(50, 6) ,Triangle::Color::BLUE };
	sampleTriangle.printInfo();

	auto vectorOfTriangles = vector<Triangle>{};
	fillTriangles(vectorOfTriangles);

	sortByPerimeter(vectorOfTriangles);

	return 0;
}



//SORTUN ÝÇÝ BUYDU

//auto size{ v.size() };
//
//vector<T> kopya{};
//copy(v.begin(), v.end(), back_inserter(kopya));
//
//cout << "1: " << endl;
//
//for (size_t i{ 0 }; i < size - 2; ++i) {
//
//	cout << "2: " << endl;
//
//	for (size_t j{ 0 }; j < size - i - 2; ++j) {
//
//		cout << "3: " << endl;
//		cout << "v.size: " << v.size() << endl;
//
//
//		cout << "deneme5: " << kopya[5].getPerimeter() << endl;
//		double deneme5 = kopya.at(5).getPerimeter();
//		cout << "deneme5: " << deneme5 << endl;
//
//		double deneme = v[5].getPerimeter();
//
//		double deneme2 = v[j + 1].getPerimeter();
//
//
//		if (deneme < deneme2) {
//
//
//
//			/*if (v[j].getPerimeter() < v[j + 1].getPerimeter()) {*/
//
//			cout << "4: " << endl;
//
//			//T temp = v[j + 1];
//			/*T temp = v.at(j + 1);
//
//			cout << "5: " << endl;
//
//			v.erase(v.begin() + j + 1);
//
//			cout << "6: " << endl;
//
//			v.insert(v.begin() + j, temp);
//
//			cout << "7: " << endl;*/
//		}
//		cout << "7: " << endl;
//	}
//}
//return 0;