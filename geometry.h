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

		Placeholder reflection();

		Placeholder &operator=(const Placeholder &rhs) = default;

		bool operator==(const Placeholder &other) const;
};


class Vector;


class Position : public Placeholder {
	public:
		using Placeholder::Placeholder;

		Position(Vector &vector);

		Position(Placeholder &&placeholder);

		const Position &origin();

		Position &operator=(const Vector &rhs) = delete;

		Position &operator+=(Vector &vector);

		Position operator+(Vector &vector);
};


class Rectangle;


class Rectangles;


class Vector : public Placeholder {
	public:
		using Placeholder::Placeholder;

		Vector(Position &pos);

		Vector &operator=(const Position &rhs) = delete;

		Vector &operator+=(const Vector &other);

		Vector operator+(const Vector &rhs);

		Position operator+(Position &pos);

        Rectangle operator+(Rectangle &rec);

		Rectangles operator+(Rectangles &recs);
};


class Rectangle {
    protected :
        int recWidth, recHeight;
        Position recPos;

    public :
        Rectangle() = delete;
		
        Rectangle(const int width, const int height, const Position pos);

        Rectangle(const int width, const int height);

        int width() const;

		int height() const;

        Position pos() const;

        Rectangle reflection();

        int area() const;

        bool operator==(const Rectangle &other) const;

		bool operator!=(const Rectangle &other) const;

        Rectangle &operator+=(Vector &vector);

        Rectangle operator+(Vector &vector);

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
	private :
		std::vector<Rectangle> rectangles;

	public :
		Rectangles() = default;

		Rectangles(const Rectangles &) = default;

		Rectangles(Rectangles &&) = default;

		Rectangles(std::initializer_list<Rectangle> rectanglesList);

		Rectangles &operator=(const Rectangles &) = default;

		Rectangles &operator=(Rectangles &&) = default;

		bool operator==(const Rectangles &other) const;

		Rectangles &operator+=(Vector &vector);

		Rectangles operator+(Vector &vector);

		Rectangle &operator[](const int i);

		int size() const;

		friend Rectangle merge_all(const Rectangles &recs);
};


#endif /* GEOMETRY_H */
