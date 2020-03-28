#include "Quadrilateral.h"

const map<Quadrilateral::Color, string> Quadrilateral::colorToStringMap = { {Quadrilateral::Color::RED, "Red"},
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
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Quadrilateral::Quadrilateral(const array<Point, NUMBER_OF_CORNERS>& pts, const Color& color) {
	setA(pts[0]);
	setB(pts[1]);
	setC(pts[2]);
	setD(pts[3]);
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
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

Quadrilateral::Color Quadrilateral::getColor() const noexcept {
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
	if (0 != (a.x - b.x) || 0 != (a.x - c.x) || 0 != (a.x - d.x) || 0 != (b.x - c.x) || 0 != (b.x - d.x)) {		// Y eksenine paralel kenar yoksa
		auto egimAB = (a.y - b.y) / (a.x - b.x);
		auto egimAC = (a.y - c.y) / (a.x - c.x);
		auto egimAD = (a.y - d.y) / (a.x - d.x);
		auto egimBC = (b.y - c.y) / (b.x - c.x);
		auto egimBD = (b.y - d.y) / (b.x - d.x);
		if (egimAB == egimAC || egimAB == egimAD || egimAC == egimAD || egimBC == egimBD) {
			return false;
		}
	}
	else if (0 != (a.y - b.y) || 0 != (a.y - c.y) || 0 != (a.y - d.y) || 0 != (b.y - c.y) || 0 != (b.y - d.y)) {	// X eksenine paralel kenar yoksa
		auto egimBA = (a.x - b.x) / (a.y - b.y);
		auto egimCA = (a.x - c.x) / (a.y - c.y);
		auto egimDA = (a.x - d.x) / (a.y - d.y);
		auto egimCB = (b.x - c.x) / (b.y - c.y);
		auto egimDB = (b.x - d.x) / (b.y - d.y);
		if (egimBA == egimCA || egimBA || egimDA || egimCA == egimDA || egimCB == egimDB) {
			return false;
		}
	}
	else if (0 == (a.x - b.x) && 0 != (b.x - c.x) && 0 != (c.x - d.x) && 0 != (d.x - a.x)) {	// Sadece AB kenar� Y eksenine dikse
		if (b.x == c.x || b.x == d.x) {
			return false;
		}
		else if (c.y == d.y && b.y == c.y) {
			return false;
		}
		else if (c.y == d.y && a.y == c.y) {
			return false;
		}
	}
	else if (0 == (c.x - b.x) && 0 != (b.x - a.x) && 0 != (a.x - d.x) && 0 != (d.x - c.x)) {	// Sadece BC kenar� Y eksenine dikse
		if (b.x == a.x || b.x == d.x) {
			return false;
		}
		else if (a.y == d.y && b.y == a.y) {
			return false;
		}
		else if (a.y == d.y && c.y == a.y) {
			return false;
		}
	}
	else if (0 == (c.x - d.x) && 0 != (d.x - a.x) && 0 != (a.x - b.x) && 0 != (b.x - c.x)) {	// Sadece CD kenar� Y eksenine dikse
		if (d.x == a.x || d.x == b.x) {
			return false;
		}
		else if (a.y == b.y && d.y == a.y) {
			return false;
		}
		else if (a.y == b.y && c.y == a.y) {
			return false;
		}
	}
	else if (0 == (a.x - d.x) && 0 != (d.x - c.x) && 0 != (c.x - b.x) && 0 != (b.x - a.x)) {	// Sadece DA kenar� Y eksenine dikse
		if (d.x == c.x || d.x == b.x) {
			return false;
		}
		else if (c.y == b.y && d.y == c.y) {
			return false;
		}
		else if (c.y == b.y && a.y == c.y) {
			return false;
		}
	}
	else if (0 == (a.y - b.y) && 0 != (b.y - c.y) && 0 != (c.y - d.y) && 0 != (d.y - a.y)) {	// Sadece AB kenar� X eksenine dikse
		if (b.y == c.y || b.y == d.y) {
			return false;
		}
		else if (c.x == d.x && b.x == c.x) {
			return false;
		}
		else if (c.x == d.x && a.x == c.x) {
			return false;
		}
	}
	else if (0 == (c.y - b.y) && 0 != (b.y - a.y) && 0 != (a.y - d.y) && 0 != (d.y - c.y)) {	// Sadece BC kenar� Y eksenine dikse
		if (b.y == a.y || b.y == d.y) {
			return false;
		}
		else if (a.x == d.x && b.x == a.x) {
			return false;
		}
		else if (a.x == d.x && c.x == a.x) {
			return false;
		}
	}
	else if (0 == (c.y - d.y) && 0 != (d.y - a.y) && 0 != (a.y - b.y) && 0 != (b.y - c.y)) {	// Sadece CD kenar� Y eksenine dikse
		if (d.y == a.y || d.y == b.y) {
			return false;
		}
		else if (a.x == b.x && d.x == a.x) {
			return false;
		}
		else if (a.x == b.x && c.x == a.x) {
			return false;
		}
	}
	else if (0 == (a.y - d.y) && 0 != (d.y - c.y) && 0 != (c.y - b.y) && 0 != (b.y - a.y)) {	// Sadece DA kenar� Y eksenine dikse
		if (d.y == c.y || d.y == b.y) {
			return false;
		}
		else if (c.x == b.x && d.x == c.x) {
			return false;
		}
		else if (c.x == b.x && a.x == c.x) {
			return false;
		}
	}
	if (a.x == b.x && a.x == c.x) {			//ABC x'leri ayn� ise
		return false;
	}
	else if (a.x == b.x && a.x == d.x) {	//ABD x'leri ayn� ise
		return false;
	}
	else if (a.x == d.x && a.x == c.x) {	//ACD x'leri ayn� ise
		return false;
	}
	else if (d.x == b.x && b.x == c.x) {	//BCD x'leri ayn� ise
		return false;
	}
	else if (a.y == b.y && a.y == c.y) {	//ABC y'leri ayn� ise
		return false;
	}
	else if (a.y == b.y && a.y == d.y) {	//ABD y'leri ayn� ise
		return false;
	}
	else if (a.y == d.y && a.y == c.y) {	//ACD y'leri ayn� ise
		return false;
	}
	else if (d.y == b.y && b.y == c.y) {	//BCD y'leri ayn� ise
		return false;
	}
	return true;
}

bool Quadrilateral::setA(const Point& pt) {		//T�m set harflerinde b�yleydi ama ilklendirirken a'y� verip kontrol etti�inde;
	a.x = pt.x;									//di�erlerinin de�eri olmad��� i�in hata veriyordu. Ben de constructor'lara ta��d�m
	a.y = pt.y;
	/*if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}*/
	return true;
}

bool Quadrilateral::setB(const Point& pt) {
	b.x = pt.x;
	b.y = pt.y;
	return true;
}

bool Quadrilateral::setC(const Point& pt) {
	c.x = pt.x;
	c.y = pt.y;
	return true;
}

bool Quadrilateral::setD(const Point& pt) {
	d.x = pt.x;
	d.y = pt.y;
	return true;
}

void Quadrilateral::printInfo() const noexcept {
	cout << "Quadrilateral" << endl;
	cout << "Number of points: 4\nPoints: (";					// Rectangle demi�siniz ama hepsi �yle olmak zorunda de�il
	cout << a.x << "," << a.y << "," << "), (";					// Vakit bulabilirsem �yle olanlar� �zel olarak yazd�rmak i�in bir �eyler yazabilirim
	cout << b.x << "," << b.y << "," << "), (";
	cout << c.x << "," << c.y << "," << "), (";
	cout << d.x << "," << d.y << "," << ")\nPeripheral: ";
	cout << getPerimeter() << "\nColor: ";
	cout << getColorAsString() << endl;
}
