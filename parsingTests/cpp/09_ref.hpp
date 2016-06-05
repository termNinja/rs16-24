class Point {
public:
	Point(double x, double y);
private:
	double x;
	double y;
};

class Rectangle {
public:
	Rectangle(const Point &topLeft, const Point &bottomRight);
	const Point& getTopLeft() const;
	const Point& getBottomRight() const;
private:
	Point m_topLeft;
	Point m_bottomRight;
};
