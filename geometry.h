#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <initializer_list>
#include <vector>


class Point {
	protected:
		int posX, posY;
	
	public:
		Point() = delete;

		Point(const int x, const int y);

		Point(const Point &other) = default;

		int x() const;

		int y() const;

		// returns point reflected across the line x = y
		Point reflection() const;

		Point &operator=(const Point &rhs) = default;

		bool operator==(const Point &other) const;
};


class Vector;


class Position : public Point {
	public:
		using Point::Point;

		Position(const Point &);

		explicit Position(Vector &vector);

		const static Position &origin();

		Position &operator=(Vector &rhs) = delete;

		Position &operator=(const Vector &rhs) = delete;

		Position &operator+=(const Vector &vector);

		Position operator+(const Vector &vector) const;
};


class Rectangle;


class Rectangles;


class Vector : public Point {
	public:
		using Point::Point;

		explicit Vector(Position &pos);

		Vector &operator=(Position &rhs) = delete;

		Vector &operator=(const Position &rhs) = delete;

		Vector &operator+=(const Vector &other);

		Vector operator+(const Vector &rhs) const;

		Position operator+(const Position &pos) const;

        Rectangle operator+(const Rectangle &rec) const;

		Rectangles operator+(const Rectangles &recs) const;

		friend Position &Position::operator+=(const Vector &);
};


class Rectangle {
    private:
        int recWidth, recHeight;

        Position recPos;

    public:
        Rectangle() = delete;
		
        Rectangle(const int width, const int height, const Position pos);

        Rectangle(const int width, const int height);

        int width() const;

		int height() const;

        Position pos() const;

		// returns rectangle reflected across the line x = y
        Rectangle reflection() const;

        int area() const;

        bool operator==(const Rectangle &other) const;

		bool operator!=(const Rectangle &other) const;

        Rectangle &operator+=(const Vector &vector);

        Rectangle operator+(const Vector &vector) const;

		/* returns the result of merging [rect1] and [rect2] horizontally;
		exits programm with an non-zero exit code when it's not possible */
		friend Rectangle merge_horizontally(
			const Rectangle &rect1,
			const Rectangle &rect2
		);

		/* returns the result of merging [rect1] and [rect2] vertically;
		exits programm with an non-zero exit code when it's not possible */
		friend Rectangle merge_vertically(
			const Rectangle &rect1,
			const Rectangle &rect2
		);
};


class Rectangles {
	private:
		std::vector<Rectangle> rectangles;

	public:
		Rectangles() = default;

		Rectangles(const Rectangles &) = default;

		Rectangles(Rectangles &&) = default;

		Rectangles(std::initializer_list<Rectangle> rectanglesList);

		Rectangles &operator=(const Rectangles &) = default;

		Rectangles &operator=(Rectangles &&) = default;

		bool operator==(const Rectangles &other) const;

		Rectangles &operator+=(const Vector &vector);

		Rectangles operator+(const Vector &vector) const;

		Rectangle &operator[](int i);

		const Rectangle &operator[](int i) const;

		size_t size() const;
};

/* returns the result of merging the collection of rectangles [recs];
exits programm with an non-zero exit code when it's not possible */
Rectangle merge_all(const Rectangles &recs);

Rectangles operator+(Rectangles &&recs, const Vector &vector);

Rectangles operator+(const Vector &vector, Rectangles &&recs);


#endif /* GEOMETRY_H */
