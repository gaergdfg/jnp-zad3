#ifndef GEOMETRY_H
#define GEOMETRY_H


class Placeholder {
	protected:
		int posX, posY;
	
	public:
		Placeholder() = delete;
		Placeholder(const int x, const int y);

		int x();
		int y();

		Placeholder reflection();

		bool operator==(const Placeholder &other) const;
};


class Vector;


class Position : public Placeholder {
	// private:
		// int posX, posY;

	public:
		using Placeholder::Placeholder;
		// Position() = delete;
		// Position(const int x, const int y);
		Position(Vector &vector);

		// int x();
		// int y();

		// Position reflection();

		const Position &origin();

		// bool operator==(Position &other) const;

		Position &operator+=(Vector &vector);

		Position operator+(Vector &vector);
};


class Vector : public Placeholder {
	// private:
		// int posX, posY;

	public:
		using Placeholder::Placeholder;
		// Vector() = delete;
		// Vector(const int x, const int y);
		Vector(Position &pos);

		// int x();
		// int y();

		// Vector reflection();

		// bool operator==(Vector &other) const;

		Vector &operator+=(const Vector &other);

		Position operator+(Position &pos);
};


#endif /* GEOMETRY_H */