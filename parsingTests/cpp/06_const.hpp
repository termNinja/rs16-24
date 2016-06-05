class Point {
public:
	// Basic constructor
	Point(double x, double y);

	// Method that is const
	double getX() const;
private:
	// member variables that are const
	const double x;
	const double y;
};
