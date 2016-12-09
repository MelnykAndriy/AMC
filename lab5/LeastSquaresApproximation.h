

#pragma once

#include <functional>
#include <vector>
#include "SimpsonMethod.h"

class LeastSquaresApproximation {
public:
	LeastSquaresApproximation(FunctionType func, LineSegment line, int polynomalDegree);
	LeastSquaresApproximation(const LeastSquaresApproximation& prev, FunctionType func, LineSegment line, int newPolynomialDegree);
	~LeastSquaresApproximation(void);


	double operator()(double x) const;
	double getLeastSquaresDeviation () const { return LeastSquaresDeviation; }
	int getPolinomialDegree() const { return polynomialDegree; }

private:
	const double integralPrecision;
	double** coefficients;
	double* constantTerms;

	int polynomialDegree;
	double LeastSquaresDeviation;

	std::vector<double> aCoefs;
	std::vector<FunctionType > basicFunctions;

	std::function<double(double)> legandreCoeff(int n);
	void findAcoefs(FunctionType func, LineSegment line, int polynomialDegree);
	void findBasicFunctions(int polynomialDegree);
	double calcLeastSquaresDeviation(FunctionType func, const LineSegment& line);
	void completeAcoefs(const LeastSquaresApproximation& prev, FunctionType func, LineSegment line, int polynomialDegree);
};

