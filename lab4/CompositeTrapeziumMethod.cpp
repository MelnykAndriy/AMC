

#include "CompositeTrapeziumMethod.h"
#include <cmath>
#include <iostream>

#pragma warning (disable : 4244)

double CompositeTrapeziumMethod::integrateWithPrecision(FunctionType integratedFunc, LineSegment line, double eps) {
	int n = 1/sqrt(eps) + 1;
	double N_integral = 0;
	double N2_integral = integrateWithStepNumber(integratedFunc, line, n);

	do {
		n *= 2;
		N_integral = N2_integral;
		N2_integral = integrateWithStepNumber(integratedFunc, line, n);
	} while ( !((1.0/3.0)*abs(N_integral - N2_integral)  <= eps) ) ;
	return N2_integral;
}

double CompositeTrapeziumMethod::integrateWithStep(FunctionType integratedFunc, LineSegment line, double step) {
	int n = (line.end - line.begin)/step + 1;
	return integrateWithStepNumber(integratedFunc, line, n);

}

double CompositeTrapeziumMethod::integrateWithStepNumber(FunctionType integratedFunc, LineSegment line, int numberOfSteps) {
	this->lastStepNumber = numberOfSteps;
	double step = this->lastStep = (line.end - line.begin)/numberOfSteps;
	double integral = (integratedFunc(line.begin) + integratedFunc(line.end))/2 ;
	double currentX = line.begin + step;
	while ( currentX < line.end ) {
		integral += integratedFunc(currentX);
		currentX += step;
	}
	return integral * step;

}

#pragma warning (default : 4244)
