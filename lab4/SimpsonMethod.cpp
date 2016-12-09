
#include "SimpsonMethod.h"
#include <stdexcept>
#include <ppl.h>

#define USE_PARALLEL_INTEGRATION

using namespace concurrency;

SimpsonMethod::SimpsonMethod(double eps) : eps(eps) { }


SimpsonMethod::~SimpsonMethod(void) { }

double SimpsonMethod::operator()(FunctionType func,const LineSegment& line) {
	int n = (int)((line.end - line.begin) / (pow(eps, 0.25)));
	if (n % 2 != 0) n++;

#ifdef USE_PARALLEL_INTEGRATION
	double In, i2N;

	parallel_invoke([&]() { In = integrateStepNumb(func, n, line); },
					[&]() { i2N = integrateStepNumb(func, 2 * n, line); }
	);
#else 
	double In = integrateStepNumb(func, n, line);
	double i2N = integrateStepNumb(func, 2 * n, line);
#endif

	while ( abs((In - i2N)) > 15*eps ) {
		n *= 2;
#ifdef USE_PARALLEL_INTEGRATION
		parallel_invoke([&]() { In = integrateStepNumb(func, n, line); },
						[&]() { i2N = integrateStepNumb(func, 2 * n, line); }
		);
#else 
		In = integrateStepNumb(func, n,  line);
		i2N = integrateStepNumb(func, 2 * n, line);
#endif
	}
	return i2N;
}
#pragma warning (disable : 4244)
double SimpsonMethod::operator()(FunctionType func,const LineSegment& line, double step)  {
	if ( step <= 0) 
		throw std::logic_error("Step should be greater than zero.");

	int numberOfSteps = ((line.end - line.begin)/step + 1.0);
	if ( numberOfSteps%2 != 0 ) numberOfSteps++;
	return integrateStepNumb(func,numberOfSteps,line);
}
#pragma warning (default : 4244)

double SimpsonMethod::integrateStepNumb(const FunctionType f,int numberOfSteps,const LineSegment& line) {
	double step = this->lastStepNumb = (line.end - line.begin)/numberOfSteps;
	double sigma1 = 0;
	double sigma2 = 0;
	double x = line.begin;
	for (int i = 0; i < numberOfSteps - 1; i++) {
		x += step;
		if (i % 2 == 0)
			sigma1 += f(x);
		else
			sigma2 += f(x);
	}

	return (step / 3) * (f(line.begin) + f(line.end) + 4 * sigma1 + 2 * sigma2);
}

double SimpsonMethod::getStep() {
	return lastStepNumb;
}
