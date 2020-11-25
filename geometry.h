#ifndef GEOMETRY_H
#define GEOMETRY_H


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

		const Position &origin();

		Position &operator=(const Vector &rhs) = delete;

		Position &operator+=(Vector &vector);

		Position operator+(Vector &vector);
};

class Rectangle;


class Vector : public Placeholder {
	public:
		using Placeholder::Placeholder;

		Vector(Position &pos);

		Vector &operator=(const Position &rhs) = delete;

		Vector &operator+=(const Vector &other);

		Vector operator+(const Vector &rhs);

        Rectangle operator+(Rectangle &rec);

		Position operator+(Position &pos);
};

class Rectangle {
    protected :
        int rec_width, rec_height;
        Position rec_pos;

    public :
        Rectangle() = delete;
        Rectangle(const int width, const int height, const Position pos);
        Rectangle(const int width, const int height);

        int width() const;

		int height() const;

        Position pos() const;

        Rectangle reflection();

        int area();

        bool operator==(const Rectangle &other) const;

        Rectangle &operator+=(Vector &vector);

        Rectangle operator+(Vector &vector);
};


#endif /* GEOMETRY_H */
