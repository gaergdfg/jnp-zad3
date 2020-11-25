#include "geometry.h"
#include <cassert>


/* ======================== PLACEHOLDER ======================== */

Placeholder::Placeholder(const int x, const int y) : posX(x), posY(y) {}

int Placeholder::x() const { return posX; }

int Placeholder::y() const { return posY; }

Placeholder Placeholder::reflection() const {
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

Position &Position::operator+=(const Vector &vector) {
	posX += vector.posX;
	posY += vector.posY;

	return *this;
}

Position Position::operator+(const Vector &vector) const {
	return Position(*this) += vector;
}


/* ======================== VECTOR ======================== */

Vector::Vector(Position &pos) : Placeholder(pos.x(), pos.y()) {}

Vector &Vector::operator+=(const Vector &other) {
	posX += other.posX;
	posY += other.posY;

	return *this;
}

Vector Vector::operator+(const Vector &rhs) const {
	return Vector(*this) += rhs;
}

Position Vector::operator+(const Position &pos) const {
	return pos + (*this);
}

Rectangle Vector::operator+(const Rectangle &rec) const {
    return rec + (*this);
}

Rectangles Vector::operator+(const Rectangles &recs) const {
    return recs + (*this);
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

Rectangle Rectangle::reflection() const {
	return Rectangle(recHeight, recWidth, Position(recPos.reflection()));
}

int Rectangle::area() const {
    return recWidth * recHeight;
}

bool Rectangle::operator==(const Rectangle &other) const {
    return
		recWidth == other.recWidth &&
		recHeight == other.recHeight &&
		recPos == other.recPos;
}

bool Rectangle::operator!=(const Rectangle &other) const {
	return !(*this == other);
}

Rectangle &Rectangle::operator+=(const Vector &vector) {
    recPos += vector;
    return *this;
}

Rectangle Rectangle::operator+(const Vector &vector) const {
    return Rectangle(*this) += vector;
}

bool can_merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
	int upperEdge = rect1.pos().y() + rect1.height();
	int lowerEdge = rect2.pos().y();

	if (upperEdge != lowerEdge)
		return false;

	int rect1LeftSide = rect1.pos().x();
	int rect2LeftSide = rect2.pos().x();

	return rect1LeftSide == rect2LeftSide;
}

bool can_merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
	int rightEdge = rect1.pos().x() + rect1.width();
	int leftEdge = rect2.pos().x();

	if (rightEdge == leftEdge)
		return false;

	int rect1LowerSide = rect1.pos().y();
	int rect2LowerSide = rect2.pos().y();

	return rect1LowerSide == rect2LowerSide;
}

Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
	assert(can_merge_horizontally(rect1, rect2));

	return Rectangle(rect1.recWidth, rect1.recHeight + rect2.recHeight, rect1.recPos);
}

Rectangle merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
	assert(can_merge_vertically(rect1, rect2));

	return Rectangle(rect1.recWidth + rect2.recWidth, rect1.recHeight, rect1.recPos);
}


/* ======================== RECTANGLES ======================== */

Rectangles::Rectangles(std::initializer_list<Rectangle> rectanglesList)
	: rectangles{rectanglesList} {}

bool Rectangles::operator==(const Rectangles &other) const {
	if (rectangles.size() != other.rectangles.size())
		return false;

	for (size_t i = 0; i < rectangles.size(); i++) {
		if (rectangles[i] != other.rectangles[i])
			return false;
	}

	return true;
}

Rectangles &Rectangles::operator+=(const Vector &vector) {
	for (size_t i = 0; i < rectangles.size(); i++) {
		rectangles[i] += vector;
	}

	return *this;
}

Rectangles Rectangles::operator+(const Vector &vector) const {
	Rectangles result = Rectangles(*this);

    for (size_t i = 0; i < rectangles.size(); i++) {
		result.rectangles[i] += vector;
	}

	return result;
}

Rectangle &Rectangles::operator[](int i) {
	assert(i >= 0 && (size_t)i < rectangles.size());

	return rectangles[i];
}

const Rectangle &Rectangles::operator[](int i) const {
	assert(i >= 0 && (size_t)i < rectangles.size());

	return rectangles[i];
}

size_t Rectangles::size() const {
	return rectangles.size();
}

Rectangle merge_all(const Rectangles &recs) {
	assert(recs.rectangles.size() != 0);

	Rectangle result = recs.rectangles[0];

	for (size_t i = 1; i < recs.rectangles.size(); i++) {
		if (can_merge_horizontally(result, recs.rectangles[i]))
			result = merge_horizontally(result, recs.rectangles[i]);
		else if (can_merge_vertically(result, recs.rectangles[i]))
			result = merge_vertically(result, recs.rectangles[i]);
		else assert(false);
	}

	return result;
}
