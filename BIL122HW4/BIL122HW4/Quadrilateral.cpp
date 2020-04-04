#include "Quadrilateral.h"

const map<Quadrilateral::Color, string> Quadrilateral::colorToStringMap = { {Quadrilateral::Color::RED, "Red"},
{Quadrilateral::Color::BLUE, "Blue"},
{Quadrilateral::Color::WHITE, "White"},
{Quadrilateral::Color::BLACK, "Black"},
{Quadrilateral::Color::GREEN, "Green"}
};

Quadrilateral::Quadrilateral(const Point& a, const Point& c, const Color& color) {
	this->a.x = a.x;
	this->a.y = a.y;
	this->c.x = c.x;
	this->c.y = c.y;
	this->b.x = c.x;
	this->b.y = a.y;
	this->d.x = a.x;
	this->d.y = c.y;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Quadrilateral::Quadrilateral(const Point& a, double width, double height, const Color& color) {
	a.x = a.x;
	a.y = a.y;
	b.x = this->a.x + width;
	b.y = this->a.y;
	c.x = b.x;
	c.y = b.y - height;
	d.x = b.y;
	d.y = this->a.x;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Quadrilateral::Quadrilateral(const Point& a, const Point& b, const Point& c, const Point& d, const Color& color) {
	this->a.x = a.x;
	this->a.y = a.y;
	this->b.x = b.x;
	this->b.y = b.y;
	this->c.x = c.x;
	this->c.y = c.y;
	this->d.x = d.x;
	this->d.y = d.y;
	this->color = color;
	if (false == isValid()) {
		throw invalid_argument("Hatali deger girdiniz.");
	}
}

Quadrilateral::Quadrilateral(const array<Point, NUMBER_OF_CORNERS>& pts, const Color& color) {
	a.x = pts[0].x;
	a.y = pts[0].y;
	b.x = pts[1].x;
	b.y = pts[1].y;
	c.x = pts[2].x;
	c.y = pts[2].y;
	d.x = pts[3].x;
	d.y = pts[3].y;
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
	auto perimeter = a.distanceTo(b);
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
	else if (0 == (a.x - b.x) && 0 != (b.x - c.x) && 0 != (c.x - d.x) && 0 != (d.x - a.x)) {	// Sadece AB kenarý Y eksenine dikse
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
	else if (0 == (c.x - b.x) && 0 != (b.x - a.x) && 0 != (a.x - d.x) && 0 != (d.x - c.x)) {	// Sadece BC kenarý Y eksenine dikse
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
	else if (0 == (c.x - d.x) && 0 != (d.x - a.x) && 0 != (a.x - b.x) && 0 != (b.x - c.x)) {	// Sadece CD kenarý Y eksenine dikse
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
	else if (0 == (a.x - d.x) && 0 != (d.x - c.x) && 0 != (c.x - b.x) && 0 != (b.x - a.x)) {	// Sadece DA kenarý Y eksenine dikse
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
	else if (0 == (a.y - b.y) && 0 != (b.y - c.y) && 0 != (c.y - d.y) && 0 != (d.y - a.y)) {	// Sadece AB kenarý X eksenine dikse
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
	else if (0 == (c.y - b.y) && 0 != (b.y - a.y) && 0 != (a.y - d.y) && 0 != (d.y - c.y)) {	// Sadece BC kenarý Y eksenine dikse
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
	else if (0 == (c.y - d.y) && 0 != (d.y - a.y) && 0 != (a.y - b.y) && 0 != (b.y - c.y)) {	// Sadece CD kenarý Y eksenine dikse
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
	else if (0 == (a.y - d.y) && 0 != (d.y - c.y) && 0 != (c.y - b.y) && 0 != (b.y - a.y)) {	// Sadece DA kenarý Y eksenine dikse
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
	if (a.x == b.x && a.x == c.x) {			//ABC x'leri ayný ise
		return false;
	}
	else if (a.x == b.x && a.x == d.x) {	//ABD x'leri ayný ise
		return false;
	}
	else if (a.x == d.x && a.x == c.x) {	//ACD x'leri ayný ise
		return false;
	}
	else if (d.x == b.x && b.x == c.x) {	//BCD x'leri ayný ise
		return false;
	}
	else if (a.y == b.y && a.y == c.y) {	//ABC y'leri ayný ise
		return false;
	}
	else if (a.y == b.y && a.y == d.y) {	//ABD y'leri ayný ise
		return false;
	}
	else if (a.y == d.y && a.y == c.y) {	//ACD y'leri ayný ise
		return false;
	}
	else if (d.y == b.y && b.y == c.y) {	//BCD y'leri ayný ise
		return false;
	}
	return true;
}

bool Quadrilateral::setA(const Point& pt) {
	a.x = pt.x;
	a.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Dortgenin A noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Quadrilateral::setB(const Point& pt) {
	b.x = pt.x;
	b.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Dortgenin B noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Quadrilateral::setC(const Point& pt) {
	c.x = pt.x;
	c.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Dortgenin C noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

bool Quadrilateral::setD(const Point& pt) {
	d.x = pt.x;
	d.y = pt.y;
	if (false == isValid()) {
		throw invalid_argument("Dortgenin D noktasi icin hatali deger girdiniz.");
		return false;
	}
	return true;
}

void Quadrilateral::printInfo() const noexcept {
	cout << "Quadrilateral" << endl;
	cout << "Number of points: " << NUMBER_OF_CORNERS << "\nPoints: (";					// Rectangle demiþsiniz ama hepsi öyle olmak zorunda deðil
	cout << a.x << ", " << a.y << "), (";					// Vakit bulabilirsem öyle olanlarý özel olarak yazdýrmak için bir þeyler yazabilirim
	cout << b.x << ", " << b.y << "), (";
	cout << c.x << ", " << c.y << "), (";
	cout << d.x << ", " << d.y << ")\nPerimeter: ";		//Peripheral yazmýþsýnýz ama perimeter olmalý diye düþündüm
	cout << getPerimeter() << "\nColor: ";
	cout << getColorAsString() << endl;
}
