// Simple point class
class Point {
public:
	Point(double x, double y);
	Point(Point p);

	double getX();
	double getY();

private:
	double x;
	double y;
};

// Simple rectangle class
class Rectangle {
	Rectangle(Point a, Point b);

	Point getTopLeft();
	Point getBottomRight();

	void setTopLeft(Point p);
	void setBottomRight(Point p);

private:
	Point m_topLeft;
	Point m_bottomRight;
};
