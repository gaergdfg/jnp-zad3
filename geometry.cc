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

Position::Position(Placeholder &&placeholder) : Placeholder(placeholder) {}

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

Rectangle::Rectangle(const int width, const int height, const Position pos)
	: recWidth(width), recHeight(height), recPos(pos) {
    assert(width > 0 && height > 0);
}

Rectangle::Rectangle(const int width, const int height)
	: recWidth(width), recHeight(height), recPos(Position(0, 0)) {
    assert(width > 0 && height > 0);
}

int Rectangle::width() const { return recWidth; }

int Rectangle::height() const { return recHeight; }

Position Rectangle::pos() const { return recPos; }

Rectangle Rectangle::reflection() {
	return Rectangle(recHeight, recWidth, Position(recPos.reflection()));
}

int Rectangle::area() const {
    return recWidth * recHeight;
}

bool Rectangle::operator==(const Rectangle &other) const {
    return recWidth == other.recWidth && recHeight == other.recHeight && recPos == other.recPos;
}

Rectangle &Rectangle::operator+=(Vector &vector) {
    recPos += vector;
    return *this;
}

Rectangle Rectangle::operator+(Vector &vector) {
    return Rectangle(*this) += vector;
}
