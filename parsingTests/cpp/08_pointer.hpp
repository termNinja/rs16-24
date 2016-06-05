class Point {
public:
	Point(const double x, const double y);
	double getX() const;
	double getY() const;

	void setX(double x);
	void setY(double y);

	static double euclid(Point a, Point b);

private:
	const double x;
	const double y;
};

// Pointer test
class Bison {
public:
	Bison();
private:
	Point *a;
	Point *b;

	double **a;
	double **b;

	// and just for fun
	int ********a;
	Bison ***********bison;
};
