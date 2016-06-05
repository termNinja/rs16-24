class Point {
public:
	Point(double x, const double y);

	// static function
	static double euclidDistance(Point a, Point b);

private:
	// static variable
	static int counter;
};
