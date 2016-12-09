
#include "SuccessiveApproximationMethod.h"
#include <iostream>

SuccessiveApproximationMethod::SuccessiveApproximationMethod( double eps) 
	: RootDefinitionMethod(eps) { }


SuccessiveApproximationMethod::~SuccessiveApproximationMethod(void) {

}

double SuccessiveApproximationMethod::getFirstApproximation(const LineSegment& isolatedRoot) {
	return isolatedRoot.start;
}

double SuccessiveApproximationMethod::calcSatisfiedApproximation(double firstApproximation,double q) {
	double prevApproximation = firstApproximation;
	double nApproximation = fixedFunc(firstApproximation);
	lastIterNumb = 1;
	precisionCheck = abs(nApproximation - prevApproximation)*q/(1.0-q);
	while ( precisionCheck > eps ) {
		prevApproximation = nApproximation;
		nApproximation = fixedFunc(nApproximation);
		precisionCheck = abs(nApproximation - prevApproximation)*q/(1.0-q);
		lastIterNumb++;
	}
	return nApproximation;
}

double SuccessiveApproximationMethod::defineRoot(functionType fixedFunc, const LineSegment& isolatedRoot,double q) {
	this->fixedFunc = fixedFunc;
	double firstApproximation = getFirstApproximation(isolatedRoot);
	return calcSatisfiedApproximation(firstApproximation,q);
}

