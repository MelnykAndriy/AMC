
#pragma once

#include <functional>

typedef std::function < double (double) > FunctionType;

struct LineSegment {
	LineSegment(double a, double b);

	double begin;
	double end;
};


class SimpsonMethod {
public:
	SimpsonMethod(double eps);
	~SimpsonMethod(void);

	double Eps() const { return eps; }
	void Eps(double val) { eps = val; }

	double operator()(FunctionType func,const LineSegment& line) const ;

private: 

	double eps;

	double integrateStepNumb(const FunctionType func,int numberOfSteps,const LineSegment& line) const;

};

