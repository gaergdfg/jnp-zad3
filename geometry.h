#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <initializer_list>
#include <vector>
#include <cstdint>


class Point {
	protected:
		int posX, posY;
	
	public:
		Point() = delete;

		Point(const int32_t x, const int32_t y);

		Point(const Point &other) = default;
		
		virtual ~Point() = 0;

		int x() const;

		int y() const;

		Point &operator=(const Point &rhs) = default;

		bool operator==(const Point &other) const;
};


class Vector;


class Position : public Point {
	public:
		using Point::Point;

		explicit Position(const Vector &vector);

		const static Position &origin();

		// returns position reflected across the line x = y
		Position reflection() const;

		Position &operator+=(const Vector &vector);

		Position operator+(const Vector &vector) const;
};


class Rectangle;


class Rectangles;


class Vector : public Point {
	public:
		using Point::Point;

		explicit Vector(const Position &pos);

		// returns vector reflected across the line x = y
		Vector reflection() const;

		Vector &operator+=(const Vector &other);

		Vector operator+(const Vector &rhs) const;

		Position operator+(const Position &pos) const;

        Rectangle operator+(const Rectangle &rec) const;

		Rectangles operator+(const Rectangles &recs) const;

		friend Position &Position::operator+=(const Vector &);
};


class Rectangle {
    private:
        int32_t recWidth, recHeight;

        Position recPos;

    public:
        Rectangle() = delete;
		
        Rectangle(const int32_t width, const int32_t height, const Position pos);

        Rectangle(const int32_t width, const int32_t height);

        int32_t width() const;

		int height() const;

        Position pos() const;

		// returns rectangle reflected across the line x = y
        Rectangle reflection() const;

        int32_t area() const;

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

		Rectangle &operator[](int32_t i);

		const Rectangle &operator[](int32_t i) const;

		size_t size() const;
};

/* returns the result of merging the collection of rectangles [recs];
exits programm with an non-zero exit code when it's not possible */
Rectangle merge_all(const Rectangles &recs);

Rectangles operator+(Rectangles &&recs, const Vector &vector);

Rectangles operator+(const Vector &vector, Rectangles &&recs);


#endif /* GEOMETRY_H */
