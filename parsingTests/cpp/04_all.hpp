class Point {
public:
	Point(double x, double y);
	Point(Point p);

protected:
	double getX();
	void setX(double x);
	void setY(double y);

private:
	double x;
	double y;
};
