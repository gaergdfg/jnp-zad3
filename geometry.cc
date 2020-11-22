#include "geometry.h"


/* ======================== POSITION ======================== */
Placeholder::Placeholder(const int x, const int y) : posX(x), posY(y) {}

int Placeholder::x() { return posX; }

int Placeholder::y() { return posY; }

Placeholder Placeholder::reflection() { return Placeholder(posY, posX); }

bool Placeholder::operator==(const Placeholder &other) const {
	return posX == other.posX && posY == other.posY;
}


/* ======================== POSITION ======================== */

// Position::Position(const int x, const int y) : posX(x), posY(y) {}

// Position::Position(Vector &vector) : posX(vector.x()), posY(vector.y()) {}
// Position::Position(Vector &vector) { posX = vector.x(); posY = vector.y(); }
Position::Position(Vector &vector) : Placeholder(vector.x(), vector.y()) {}

// int Position::x() { return posX; }

// int Position::y() { return posY; }

// Position Position::reflection() { return Position(posY, posX); }

const Position &Position::origin() {
	const static Position *origin = new Position(0, 0);
	return *origin;
}

// bool Position::operator==(Position &other) const {
// 	return posX == other.x() && posY == other.y();
// }

Position &Position::operator+=(Vector &vector) {
	posX += vector.x();
	posY += vector.y();

	return *this;
}

Position Position::operator+(Vector &vector) {
	return Position(*this) += vector;
}


/* ======================== VECTOR ======================== */

// Vector::Vector(const int x, const int y) : posX(x), posY(y) {}

Vector::Vector(Position &pos) : Placeholder(pos.x(), pos.y()) {}

// int Vector::x() { return posX; }

// int Vector::y() { return posY; }

// Vector Vector::reflection() { return Vector(posY, posX); }

// bool Vector::operator==(Vector &other) const {
// 	return posX == other.x() && posY == other.y();
// }

Vector &Vector::operator+=(const Vector &other) {
	posX += other.posX;
	posY += other.posY;

	return *this;
}

Position Vector::operator+(Position &pos) {
	return pos + (*this);
}
