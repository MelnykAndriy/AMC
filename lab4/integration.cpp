

#include "integration.h"
#include <cmath>
#include <stdexcept>

using namespace std;


LineSegment::LineSegment(double a, double b) : begin(a), end(b) {
	if ( begin > end ) 
		throw std::logic_error("Invalid line segment.");
}

namespace lab4 {

	const double M2 = 15.71209668;
	const double M4 = 1;
	const double from = -1;
	const double to = 16;

	double func(double x) {
		return x*x*x/6 - sin(x) + x;
	}

	double funcAntiderivative(double x) {
		return x*x*x*x/24 + cos(x) + x * x /2;
	}

	double newtonLeibnizAxiom(FunctionType antiderivative, LineSegment line) {
		return antiderivative(line.end) - antiderivative(line.begin);
	}

	double calcStepTrapezium(double eps, LineSegment line, double M) {
		return sqrt(12*eps/((line.end - line.begin)*M));
	}

	double calcStepSimpson(double eps, LineSegment line, double M) {
		return pow(180*eps/(line.end - line.begin)*M, 1.0/4.0);
	}

}

