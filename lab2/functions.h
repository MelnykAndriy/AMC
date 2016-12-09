


#pragma once 

#include "DefineRoot.h"

namespace NewtonBundle {

	// 0.6 * x^4 + 3 * ln(x + 3) - 3.7

	extern LineSegment lSeg1;
	extern LineSegment lSeg2;
	extern double m1;
	extern double m2;

	double func(double x);
	double firstDerivative(double x);

}


namespace ApproximationBundle {

	extern LineSegment lSeg1;
	extern LineSegment lSeg2;
	extern double q1;
	extern double q2;

	double fixedFunc1(double x);
	double fixedFunc2(double x);
}

