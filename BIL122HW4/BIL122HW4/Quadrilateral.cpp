#include "Quadrilateral.h"

static const map<Quadrilateral::Color, string> colorToStringMap = { {Quadrilateral::Color::RED, "Red"},
		{Quadrilateral::Color::BLUE, "Blue"},
		{Quadrilateral::Color::WHITE, "White"},
		{Quadrilateral::Color::BLACK, "Black"},
		{Quadrilateral::Color::GREEN, "Green"}
};

Quadrilateral::Quadrilateral(const Point& a, const Point& c, const Color& color) {
	setA(a);
	setC(c);
	this->color = color;
	Point tempB;
	Point tempD;
	tempB.x = c.x;
	tempB.y = a.y;
	tempD.x = a.x;
	tempD.y = c.y;
	setB(tempB);
	setD(tempD);
}

Quadrilateral::Quadrilateral(const Point& a, double width, double height, const Color& color) {
	setA(a);
	Point tempB;
	Point tempC;
	Point tempD;
	tempB.y = this->a.y;
	tempB.x = this->a.x + width;
	tempC.x = tempB.x;
	tempC.y = tempB.y - height;
	tempD.y = tempC.y;
	tempD.x = this->a.x;
	setB(tempB);
	setC(tempC);
	setD(tempD);
	this->color = color;
}

Quadrilateral::Quadrilateral(const Point& a, const Point& b, const Point& c, const Point& d, const Color& color) {
	setA(a);
	setB(b);
	setC(c);
	setD(d);
	this->color = color;
}

Quadrilateral::Quadrilateral(const array<Point, NUMBER_OF_CORNERS>& pts, const Color& color) { 
	setA(pts[0]);
	setB(pts[1]);
	setC(pts[2]);
	setD(pts[3]);
	this->color = color;
}

Point Quadrilateral::getA() const noexcept {
	return pts[0];
}

Point Quadrilateral::getB() const noexcept {
	return pts[1];
}

Point Quadrilateral::getC() const noexcept {
	return pts[2];
}

Point Quadrilateral::getD() const noexcept {
	return pts[3];
}

Quadrilateral::Color Quadrilateral::getColor() const noexcept{
	return this->color;
}

string Quadrilateral::getColorAsString() const noexcept {
	return colorToStringMap.at(this->color);
}

double Quadrilateral::getPerimeter() const noexcept {
	double perimeter = a.distanceTo(b);
	perimeter += b.distanceTo(c);
	perimeter += c.distanceTo(d);
	perimeter += d.distanceTo(a);
	return perimeter;
}

bool Quadrilateral::isValid() const {

	return false;
}

bool Quadrilateral::setA(const Point& pt) {
	a.x = pt.x;
	a.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");	
		return false;
	}
	return true;
}

bool Quadrilateral::setB(const Point& pt) {
	b.x = pt.x;
	b.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");	
		return false;
	}
	return true;
}

bool Quadrilateral::setC(const Point& pt) {
	c.x = pt.x;
	c.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");	
		return false;
	}
	return true;
}

bool Quadrilateral::setD(const Point& pt) {
	d.x = pt.x;
	d.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");	
		return false;
	}
	return true;
}

void Quadrilateral::printInfo() const noexcept {
	cout << "Rectangle\nNumber of points: 4\nPoints: (";
	cout << a.x << "," << a.y << "," << "), (";
	cout << b.x << "," << b.y << "," << "), (";
	cout << c.x << "," << c.y << "," << "), (";
	cout << d.x << "," << d.y << "," << ")\nPeripheral: ";
	cout << getPerimeter() << "\nColor: ";
	cout << colorToStringMap.at(this->color) << endl;
}
