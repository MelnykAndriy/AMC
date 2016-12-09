


#pragma once
#include "integration.h"


class CompositeTrapeziumMethod {
public:
	CompositeTrapeziumMethod() : lastStepNumber(0), lastStep(0) { }
	~CompositeTrapeziumMethod() { }



	double integrateWithPrecision(FunctionType integratedFunc, LineSegment line, double eps); 
	double integrateWithStep(FunctionType integratedFunc, LineSegment line, double step);
	double integrateWithStepNumber(FunctionType integratedFunc, LineSegment line, int numberOfSteps);
	
	unsigned int getNumberOfSteps() const { return lastStepNumber; }
	double getStep() const { return lastStep; }

private:


	unsigned int lastStepNumber;
	double lastStep;



};

