#ifndef GEOMETRY_H
#define GEOMETRY_H
#include <initializer_list>
#include <vector>


class Placeholder {
	protected:
		int posX, posY;
	
	public:
		Placeholder() = delete;

		Placeholder(const int x, const int y);

		Placeholder(const Placeholder &other) = default;

		int x() const;

		int y() const;

		Placeholder reflection() const;

		Placeholder &operator=(const Placeholder &rhs) = default;

		bool operator==(const Placeholder &other) const;
};


class Vector;


class Position : public Placeholder {
	public:
		using Placeholder::Placeholder;

		explicit Position(Vector &vector);

		Position(Placeholder &&placeholder);

		const static Position &origin();

		Position &operator=(Vector &rhs) = delete;

		Position &operator=(const Vector &rhs) = delete;

		Position &operator+=(const Vector &vector);

		Position operator+(const Vector &vector) const;
};


class Rectangle;


class Rectangles;


class Vector : public Placeholder {
	public:
		using Placeholder::Placeholder;

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

        Rectangle reflection() const;

        int area() const;

        bool operator==(const Rectangle &other) const;

		bool operator!=(const Rectangle &other) const;

        Rectangle &operator+=(const Vector &vector);

        Rectangle operator+(const Vector &vector) const;

		friend Rectangle merge_horizontally(
			const Rectangle &rect1,
			const Rectangle &rect2
		);

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

		friend Rectangle merge_all(const Rectangles &recs);
};


Rectangle merge_all(const Rectangles &recs);


#endif /* GEOMETRY_H */
