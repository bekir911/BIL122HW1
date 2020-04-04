#include "Triangle.h"

const map<Triangle::Color, string> Triangle::colorToStringMap = { {Triangle::Color::PINK, "Pink"},
{Triangle::Color::RED, "Red"},
{Triangle::Color::BLUE, "Blue"},
{Triangle::Color::WHITE, "White"},
{Triangle::Color::BLACK, "Black"},
{Triangle::Color::GREEN, "Green"}
};

Triangle::Triangle(const Point& a, const Point& b, const Point& c, const Color& color) {
	this->a.x = a.x;
	this->a.y = a.y;
	this->b.x = b.x;
	this->b.y = b.y;
	this->c.x = c.x;
	this->c.y = c.y;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Triangle::Triangle(const vector<Point>& pts, const Color& color) {
	a.x = pts[0].x;
	a.y = pts[0].y;
	b.x = pts[1].x;
	b.y = pts[1].y;
	c.x = pts[2].x;
	c.y = pts[2].y;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Triangle::Triangle(const array<Point, NUMBER_OF_CORNERS>& pts, const Color& color) {
	a.x = pts[0].x;
	a.y = pts[0].y;
	b.x = pts[1].x;
	b.y = pts[1].y;
	c.x = pts[2].x;
	c.y = pts[2].y;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Point Triangle::getA() const noexcept {
	return pts[0];
}

Point Triangle::getB() const noexcept {
	return pts[1];
}

Point Triangle::getC() const noexcept {
	return pts[2];
}

Triangle::Color Triangle::getColor() const noexcept {
	return this->color;
}

string Triangle::getColorAsString() const noexcept {
	return colorToStringMap.at(this->color);
}

double Triangle::getPerimeter() const noexcept {
	double perimeter = a.distanceTo(b);
	perimeter += b.distanceTo(c);
	perimeter += a.distanceTo(c);
	return perimeter;
}

bool Triangle::setA(const Point& pt) {
	a.x = pt.x;
	a.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Ucgenin A noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Triangle::setB(const Point& pt) {
	b.x = pt.x;
	b.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Ucgenin B noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Triangle::setC(const Point& pt) {
	c.x = pt.x;
	c.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Ucgenin C noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Triangle::setColor(const Color& color){
	this->color = color;	// el ile çaðýrýlma ihtimaline karþý isValid koymayý denemedim ama döngüde renkleri çaðýrýp kýyaslayamadým
	return true;
}

bool Triangle::isValid() const {
	if (a.x == b.x && a.x == c.x) {	// X deðerleri ayný ise
		return false;
	}
	else if (a.y == b.y && a.y == c.y) {	// Y deðerleri ayný ise
		return false;
	}
	else if (0 != (a.x - b.x) || 0 != (a.x - c.x)) {	// Y eksenine paralel kenar yoksa
		auto egimAB = (a.y - b.y) / (a.x - b.x);
		auto egimAC = (a.y - c.y) / (a.x - c.x);
		if (egimAB == egimAC) {
			return false;
		}
	}
	else if (0 != (a.y - b.y) || 0 != (a.y - c.y)) {	// X eksenine paralel kenar yoksa
		auto egimBA = (a.x - b.x) / (a.y - b.y);
		auto egimCA = (a.x - c.x) / (a.y - c.y);
		if (egimBA == egimCA) {
			return false;
		}
	}
	return true;
}

void Triangle::printInfo() const noexcept {
	cout << "Triangle" << endl;
	cout << "Number of points: " << NUMBER_OF_CORNERS << "\nPoints: (";
	cout << a.x << ", " << a.y << "), (";
	cout << b.x << ", " << b.y << "), (";
	cout << c.x << ", " << c.y << ")\nPerimeter: ";
	cout << getPerimeter() << "\nColor: ";
	cout << getColorAsString() << endl;
}
