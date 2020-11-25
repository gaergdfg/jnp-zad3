#include "geometry.h"
#include <cassert>


/* ======================== PLACEHOLDER ======================== */

Placeholder::Placeholder(const int x, const int y) : posX(x), posY(y) {}

int Placeholder::x() const { return posX; }

int Placeholder::y() const { return posY; }

Placeholder Placeholder::reflection() {
	return Placeholder(posY, posX);
}

bool Placeholder::operator==(const Placeholder &other) const {
	return posX == other.posX && posY == other.posY;
}


/* ======================== POSITION ======================== */

Position::Position(Vector &vector) : Placeholder(vector.x(), vector.y()) {}

const Position &Position::origin() {
	const static Position *origin = new Position(0, 0);
	return *origin;
}

Position &Position::operator+=(Vector &vector) {
	posX += vector.x();
	posY += vector.y();

	return *this;
}

Position Position::operator+(Vector &vector) {
	return Position(*this) += vector;
}


/* ======================== VECTOR ======================== */

Vector::Vector(Position &pos) : Placeholder(pos.x(), pos.y()) {}

Vector &Vector::operator+=(const Vector &other) {
	posX += other.posX;
	posY += other.posY;

	return *this;
}

Vector Vector::operator+(const Vector &rhs) {
	return Vector(*this) += rhs;
}

Rectangle Vector::operator+(Rectangle &rec) {
    return rec + (*this);
}

Position Vector::operator+(Position &pos) {
	return pos + (*this);
}


/* ======================== RECTANGLE ======================== */

Rectangle::Rectangle(const int width, const int height, const Position pos) : rec_width(width), rec_height(height), rec_pos(pos) {
    assert(width > 0 && height > 0);
}
Rectangle::Rectangle(const int width, const int height) : rec_width(width), rec_height(height), rec_pos(Position(0, 0)) {
    assert(width > 0 && height > 0);
}

int Rectangle::width() const { return rec_width; }

int Rectangle::height() const { return rec_height; }

Position Rectangle::pos() const { return rec_pos; }

/*Rectangle Rectangle::reflection() {
    return Rectangle(rec_height, rec_width, rec_pos.reflection());
}*/

int Rectangle::area() {
    return rec_width * rec_height;
}

bool Rectangle::operator==(const Rectangle &other) const {
    return rec_width == other.rec_width && rec_height == other.rec_height && rec_pos == other.rec_pos;
}

Rectangle &Rectangle::operator+=(Vector &vector) {
    rec_pos += vector;
    return *this;
}

Rectangle Rectangle::operator+(Vector &vector) {
    return Rectangle(*this) += vector;
}
