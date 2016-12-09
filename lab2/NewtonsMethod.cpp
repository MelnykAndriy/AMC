

#include "NewtonsMethod.h"
#include <exception>
#include <iostream>

NewtonsMethod::NewtonsMethod(double eps) 
	: RootDefinitionMethod(eps) { }


NewtonsMethod::~NewtonsMethod(void) 
{
}

double NewtonsMethod::defineRoot(functionType func, functionType firstDerivative, const LineSegment& isolatedRoot,double m) {
	this->func = func;
	this->firstDerivative = firstDerivative;
	double firstApproximation = getFirstApproximation(isolatedRoot);
	return calcSatisfiedApproximation(firstApproximation, m);
}

double NewtonsMethod::getFirstApproximation(const LineSegment& isolatedRoot) {
	if ( func(isolatedRoot.start) * firstDerivative(isolatedRoot.start) > 0 ) {
		return isolatedRoot.start;
	} else if ( func(isolatedRoot.end) * firstDerivative(isolatedRoot.end) > 0  ) {
		return isolatedRoot.end;
	} else {
		throw std::exception("Invalid interval."); 
	}
}

double NewtonsMethod::calcSatisfiedApproximation(double firstAproximation, double m) {
	double nApproximation = firstAproximation;
	lastIterNumb = 0;
	precisionCheck = abs(func(nApproximation))/m;
	while ( precisionCheck > eps  ) {
		nApproximation = nApproximation - func(nApproximation) / firstDerivative(nApproximation) ;
		precisionCheck = abs(func(nApproximation))/m;
		lastIterNumb++;
	}
	return nApproximation;
}

