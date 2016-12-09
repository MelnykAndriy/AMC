
#pragma once

#include <functional>
#include "integration.h"

class SimpsonMethod {
public:
	SimpsonMethod(double eps=1e-3);
	~SimpsonMethod(void);

	double Eps() const { return eps; }
	void Eps(double val) { eps = val; }

	double operator()(FunctionType func,const LineSegment& line) ;
	double operator()(FunctionType func,const LineSegment& line, double step) ;
	double getStep();

private: 

	double eps;
	double lastStepNumb;
	double integrateStepNumb(const FunctionType func,int numberOfSteps,const LineSegment& line) ;
	
};

