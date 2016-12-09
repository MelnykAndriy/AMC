
#include <cmath>
#include "DefineRoot.h"
#include <iostream>

namespace NewtonBundle {

	double m1 = 0.9;
	LineSegment lSeg1(-2,-1);
	double m2 = 0.956696;
	LineSegment lSeg2(0,1);

	double func(double x) {
		return 0.6*x*x*x*x + 3.0*log(x + 3.0)  - 3.7; 
	}



	double firstDerivative(double x) {
		return 2.4*x*x*x + 3/( x +  3);
	}

}

namespace ApproximationBundle {

	double q1 = 0.944444;
	LineSegment lSeg1(-2,-1);

	static double lambda1 = 0.0617283;
	double fixedFunc1(double x) {
		return x + lambda1*NewtonBundle::func(x);
	}


	double q2 = 0.69505492;
	LineSegment lSeg2(0.25,1);

	static double lambda2 = 0.31746032;
	double fixedFunc2(double x) {
		return x - lambda2*NewtonBundle::func(x);
	}

}