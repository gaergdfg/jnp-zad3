#include "geometry.h"


/* ======================== PLACEHOLDER ======================== */
Placeholder::Placeholder(const int x, const int y) : posX(x), posY(y) {}

int Placeholder::x() { return posX; }

int Placeholder::y() { return posY; }

Placeholder Placeholder::reflection() { return Placeholder(posY, posX); }

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

Position Vector::operator+(Position &pos) {
	return pos + (*this);
}
