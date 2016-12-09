
#pragma once

#include "DefineRoot.h"


class SuccessiveApproximationMethod : public RootDefinitionMethod {
public:
	SuccessiveApproximationMethod(double eps=1e-3);
	~SuccessiveApproximationMethod(void);
	
	double defineRoot(functionType fixedFunc, const LineSegment& isolatedRoot, double q);

private:

	double getFirstApproximation(const LineSegment& isolatedRoot);
	double calcSatisfiedApproximation(double nApproximation,double q);

	functionType fixedFunc;

};

