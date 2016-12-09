


#pragma once

#include "DefineRoot.h"



class NewtonsMethod : public RootDefinitionMethod {
public:
	NewtonsMethod(double eps=1e-3);
	~NewtonsMethod(void);

	virtual double defineRoot(functionType func, functionType firstDerivative, const LineSegment& isolatedRoot,double m);

private: 

	double getFirstApproximation(const LineSegment& isolatedRoot);
	double calcSatisfiedApproximation(double firstApproximation, double m);

	functionType func;
	functionType firstDerivative;
};

