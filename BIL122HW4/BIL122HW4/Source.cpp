#include <iostream>
#include <vector>
#include <random>							//BEN EKLEDÝM
#include "Triangle.h"
#include "Quadrilateral.h"

using namespace std;

constexpr auto TRIANGLE_COLOR = 6;
constexpr auto QUADRILATERAL_COLOR = 5;

std::random_device rastgele;
std::mt19937 calis(rastgele());
std::uniform_int_distribution<std::mt19937::result_type> motor(0, 100);


// Rastgele olarak Triangle nesneleri olusturur ve parametre olarak verilen vektore ekler.
/* Triangle nesnelerinde yer alacak noktalarýn x ve y deðerleri [0, 100] arasýnda olabilir.
   Þeklin renk deðeri de rastgele olarak belirlenmelidir.
*/
void fillTriangles(vector<Triangle>& v, int numberOfItems = 100) {
	v.resize(numberOfItems);
	for (auto i{ 0 }; i < numberOfItems; ++i) {
		Point p1 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p2 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p3 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		try {
			auto randomColor = motor(calis) % TRIANGLE_COLOR;
			auto color = static_cast<Triangle::Color>(randomColor);
			v[i].setA(p1);
			v[i].setB(p2);
			v[i].setC(p3);
			v[i].setColor(color);
		}
		catch (invalid_argument& ex) {
			cout << "Invalid Triangle, Index: " << i << " " << ex.what() << endl;
		}
	}
}

// Rastgele olarak Quadrilateral nesneleri olusturur ve parametre olarak verilen vektore ekler.
/* Quadrilateral nesnelerinde yer alacak noktalarýn x ve y deðerleri [0, 100] arasýnda olabilir.
   Þeklin renk deðeri de rastgele olarak belirlenmelidir.
*/
void fillQuads(vector<Quadrilateral>& v, int numberOfItems = 100) {
	v.resize(numberOfItems);
	for (auto i{ 0 }; i < numberOfItems; ++i) {
		Point p1 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p2 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p3 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		Point p4 = { static_cast<double>(motor(calis)), static_cast<double>(motor(calis)) };
		try {
			auto randomColor = motor(calis) % QUADRILATERAL_COLOR;
			auto color = static_cast<Quadrilateral::Color>(randomColor);
			v[i].setA(p1);
			v[i].setB(p2);
			v[i].setC(p3);
			v[i].setD(p4);
			v[i].setColor(color);
		}
		catch (invalid_argument& ex) {
			cout << "Invalid Quadrilateral, Index: " << i << " " << ex.what() << endl;
		}
	}
}

///* Verilen Triangle veya Rectangle vektörününde çevre uzunluðu ve renk deðeri eþleþen ilk elemanýn indeksini döndürür.
//Eleman bulunamazsa -1 döndürülür.*/
template<class T>
int search(const vector<T>& v, const T& key) {
	auto perimeter{ key.getPerimeter() };
	auto size{ v.size() };
	auto colorA = static_cast<typename T::Color>(key.getColor());
	for (size_t i{ 0 }; i < size; ++i) {
		auto colorB = static_cast<typename T::Color>(v[i].getColor());
		if (v[i].getPerimeter() == perimeter && colorB == colorA) {
			return i;
		}
	}
	return -1;
}

template<class T>
int sortByPerimeter(vector<T>& v) {
	auto size{ v.size() };
	for (size_t i{ 0 }; i < size - 1; ++i) {
		for (size_t j{ 0 }; j < size - i - 1; ++j) {
			if (v[j].getPerimeter() < v[j + 1].getPerimeter()) {
				T temp;
				temp.setA(v[j].getA());
				temp.setB(v[j].getB());
				temp.setC(v[j].getC());
				temp.setColor(v[j].getColor());

				/*if (4 == v[j].NUMBER_OF_CORNERS) {			//SIKINTI ÇIKABÝLÝR
					temp.setD(v[j].getD());
				}*/

				v[j].setA(v[j + 1].getA());
				v[j].setB(v[j + 1].getB());
				v[j].setC(v[j + 1].getC());
				v[j].setColor(v[j + 1].getColor());

				/*if (4 == v[j].NUMBER_OF_CORNERS) {			//SIKINTI ÇIKABÝLÝR
					v[j].setD(v[j + 1].getD());
				}*/

				v[j + 1].setA(temp.getA());
				v[j + 1].setB(temp.getB());
				v[j + 1].setC(temp.getC());
				v[j + 1].setColor(temp.getColor());

				/*if (4 == v[j].NUMBER_OF_CORNERS) {			//SIKINTI ÇIKABÝLÝR
					v[j + 1].setD(temp.getD());
				}*/
			}
		}
	}
	return 0;
}


template<class T>
void pushBack(vector<T>& v, const T& key, const int& index = 0) {	//Belki de eklememeliydim ama bence güzel oldu.
	auto size{ v.size() };											//vectorOfTriangles.push_back(sampleTriangle);
	v.resize(size + 1);
	v[size].setA(key.getA());
	v[size].setB(key.getB());
	v[size].setC(key.getC());
	v[size].setColor(key.getColor());
	//if (4 == key.NUMBER_OF_CORNERS) {
	//	v[size].setD(key.getD());		//SIKINTI ÇIKABÝLÝR
	//}
}

//int main()
//{
//	// Point class test
//	auto p = Point{ 4.5, 6.2 };
//	
//	cout << p.x << " " << p.y << endl;
//	cout << p.coords[0] << " " << p.coords[1] << endl;
//
//	// Sample Quad and Triangle Objects
//
//	auto sampleQuad = Quadrilateral{ Point(4, 5), 20, 20 };
//	cout << "Color of Sample Quad: " << sampleQuad.getColorAsString() << endl;
//
//	auto sampleTriangle = Triangle{ Point(4, 5),  Point(9, 5),  Point(14, 15) };
//	cout << "Color of Sample Triangle: " << sampleTriangle.getColorAsString() << endl;
//	
//	// Filling vectors randomly
//	auto vectorOfQuads = vector<Quadrilateral>{};
//	auto vectorOfTriangles = vector<Triangle>{};
//	
//	fillTriangles(vectorOfTriangles,10);
//	fillQuads(vectorOfQuads,10);
//
//	// Search sample objects in the corresponding vectors
//	cout << "Searching a triangle...\n";
//	sampleTriangle.printInfo();
//	if (auto idx = search(vectorOfTriangles, sampleTriangle) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//	cout << "Searching a quadrilateral...\n";
//	sampleQuad.printInfo();
//	if (auto idx = search(vectorOfQuads, sampleQuad) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//	// Add sample Triangle object to the vector and sort the vector				
//	pushBack(vectorOfTriangles, sampleTriangle);							//push_back hata verdiði için bunu yaptým ama bu da hata verdi
//	//vectorOfTriangles.push_back(sampleTriangle);
//	sortByPerimeter(vectorOfTriangles);										//BU SATIRI YAPAMIYOR
//
//	// Search sample item again. Now, you must have a hit.
//	cout << "Searching a triangle...\n";
//	sampleTriangle.printInfo();
//	if (auto idx = search(vectorOfTriangles, sampleTriangle) >= 0)
//		cout << "A similar object is found at index-" << idx << endl;
//	else cout << "No similar object can be found" << endl;
//
//
//
//	// Add sample Quad object to the vector and sort the vector
//	//vectorOfQuads.push_back(sampleQuad);
//	pushBack(vectorOfQuads, sampleQuad);							//push_back hata verdiði için bunu yaptým ama bu da hata verdi
//	sortByPerimeter(vectorOfQuads);
//
//
//	// Search sample item again. Now, you must have a hit.
//	cout << "Searching a quadrilateral...\n";
//	sampleQuad.printInfo();
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
	auto sampleTriangle = Triangle{ Point(4, 5),  Point(9, 5),  Point(14, 15) ,Triangle::Color::BLUE };

	//buradan önceki kýsýmlarda hata olmuyor, basit þeyler zaten
	//constructor ya da fonksiyonlarda sorun yok
	//vektör iþin içine girince sýkýntýlar oluþmaya baþlýyor
	//dörtgen olmasý bir þey deðiþtirmiyor. isvalid çok büyük oldu o kadar
	//bu yüzden onu kullanmadým. template class, setD yapýnca üçgende hata verdiði için

	auto vectorOfTriangles = vector<Triangle>{};
	fillTriangles(vectorOfTriangles, 5);			//5 yaptým hata az olsun diye

	// Search sample objects in the corresponding vectors
	cout << "Searching a triangle...\n";
	sampleTriangle.printInfo();
	if (auto idx = search(vectorOfTriangles, sampleTriangle) >= 0)
		cout << "A similar object is found at index-" << idx << endl;
	else cout << "No similar object can be found" << endl;

	//pushback yapamadýðýmýz için sonradan aramanýn bir anlamý yok

	//pushBack(vectorOfTriangles, sampleTriangle);		//normal push_back zaten hata veriyordu	
	sortByPerimeter(vectorOfTriangles);					//Elle yazdým, o da iþini yapsa da sonrasýnda hata oluyor					

	// Invalid cases
	try
	{
		auto invalidTriangle1 = Triangle{ Point{4, 0},  Point{9, 0},  Point{14, 0} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid triangle: " << ex.what() << endl;
	}

	try
	{
		auto invalidTriangle2 = Triangle{ Point{4, 4},  Point{4, 4},  Point{4, 4} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid triangle: " << ex.what() << endl;
	}

	try
	{
		auto invalidTriangle3 = Triangle{ Point{4, 0},  Point{4, 4},  Point{4, 14} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid triangle: " << ex.what() << endl;
	}

	try
	{
		auto invalidQuad1 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{14, 0}, Point{0, 0} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid Quad: " << ex.what() << endl;
	}

	try
	{
		auto invalidQuad1 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{14, 0}, Point{0, 0} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid Quad: " << ex.what() << endl;
	}

	try
	{
		auto invalidQuad2 = Quadrilateral{ Point{4, 0},  Point{9, 0},  Point{3, 20}, Point{10, 20} };
	}
	catch (invalid_argument& ex)
	{
		cout << "Invalid Quad: " << ex.what() << endl;
	}
	return 0;
}