#include "geometry.h"
#include <cassert>


/* ======================== POINT ======================== */

Point::Point(const int x, const int y) : posX(x), posY(y) {}

int Point::x() const { return posX; }

int Point::y() const { return posY; }

// reflect point across the line x = y
Point Point::reflection() const {
	return Point(posY, posX);
}

bool Point::operator==(const Point &other) const {
	return posX == other.posX && posY == other.posY;
}


/* ======================== POSITION ======================== */

Position::Position(const Point &point) : Point(point) {}

Position::Position(Vector &vector) : Point(vector.x(), vector.y()) {}

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

Vector::Vector(Position &pos) : Point(pos.x(), pos.y()) {}

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

// reflect rectangle across the line x = y
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

/* returns true if it's possible to merge [rect1] and [rect2] horizontally;
false otherwise */
bool can_merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
	int upperEdge = rect1.pos().y() + rect1.height();
	int lowerEdge = rect2.pos().y();

	if (upperEdge != lowerEdge)
		return false;

	int rect1LeftSide = rect1.pos().x();
	int rect2LeftSide = rect2.pos().x();

	return rect1LeftSide == rect2LeftSide;
}

/* returns true if it's possible to merge [rect1] and [rect2] vertically;
false otherwise */
bool can_merge_vertically(const Rectangle &rect1, const Rectangle &rect2) {
	int rightEdge = rect1.pos().x() + rect1.width();
	int leftEdge = rect2.pos().x();

	if (rightEdge != leftEdge)
		return false;

	int rect1LowerSide = rect1.pos().y();
	int rect2LowerSide = rect2.pos().y();

	return rect1LowerSide == rect2LowerSide;
}

/* returns the result of merging [rect1] and [rect2] horizontally;
exits programm with an non-zero exit code when it's not possible */
Rectangle merge_horizontally(const Rectangle &rect1, const Rectangle &rect2) {
	assert(can_merge_horizontally(rect1, rect2));

	return Rectangle(rect1.recWidth, rect1.recHeight + rect2.recHeight, rect1.recPos);
}

/* returns the result of merging [rect1] and [rect2] vertically;
exits programm with an non-zero exit code when it's not possible */
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

/* returns the result of merging the collection of rectangles [recs];
exits programm with an non-zero exit code when it's not possible */
Rectangle merge_all(const Rectangles &recs) {
	assert(recs.size() != 0);

	Rectangle result = recs[0];

	for (size_t i = 1; i < recs.size(); i++) {
		if (can_merge_horizontally(result, recs[i]))
			result = merge_horizontally(result, recs[i]);
		else if (can_merge_vertically(result, recs[i]))
			result = merge_vertically(result, recs[i]);
		else assert(false);
	}

	return result;
}

Rectangles operator+(Rectangles &&recs, const Vector &vector) {
	Rectangles temp = std::move(recs);
	temp += vector;
	return temp;
}

Rectangles operator+(const Vector &vector, Rectangles &&recs) {
	Rectangles temp = std::move(recs);
	temp += vector;
	return temp;
}
