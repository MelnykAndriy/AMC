




#pragma  once

#include <functional>

typedef std::function < double (double) > FunctionType;

struct LineSegment {

	LineSegment(double a, double b);

	double begin;
	double end;
};

namespace lab4  {

	extern const double M2;
	extern const double M4;
	extern const double from;
	extern const double to;

	double calcStepTrapezium(double eps, LineSegment line, double M);
	double calcStepSimpson(double eps, LineSegment line, double M);

	double func(double x);
	double funcAntiderivative(double x);
	double newtonLeibnizAxiom(FunctionType antiderivative, LineSegment line);	
}