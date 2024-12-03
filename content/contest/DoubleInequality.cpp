// EPS | Double Inequality
const double eps = 1e-9;
bool isEqual(double a, double b) {return abs(a-b) <= eps;} // a == b
bool isSmaller(double a, double b) {return a+eps < b;} // a < b
bool isGreater(double a, double b) {return a > b+eps;} // a > b