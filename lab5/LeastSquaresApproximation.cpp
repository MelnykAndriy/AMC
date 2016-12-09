

#include <stdexcept>

#include "LeastSquaresApproximation.h"
#include "SimpsonMethod.h"
#include "GaussJordanElimination.h"
#include <ppl.h>

#define USE_COLUMN_PARALLEL_FILLING
#define USE_ROW_PARALLEL_FILLING

using namespace std;
using namespace concurrency;

LeastSquaresApproximation::LeastSquaresApproximation(FunctionType func, LineSegment line, int polynomialDegree)
	: polynomialDegree(polynomialDegree),integralPrecision(1e-5), coefficients(nullptr),constantTerms(nullptr) 
{
	if ( polynomialDegree <= 0 ) 
		throw logic_error("Polynomial degree should be greater than zero.");
	findBasicFunctions(polynomialDegree);
	findAcoefs(func, line, polynomialDegree);
	LeastSquaresDeviation = calcLeastSquaresDeviation(func, line);
}

LeastSquaresApproximation::LeastSquaresApproximation(const LeastSquaresApproximation& prev, 
													 FunctionType func, 
													 LineSegment line, 
													 int newPolynomialDegree)
	: polynomialDegree(newPolynomialDegree),integralPrecision(1e-5), coefficients(nullptr),constantTerms(nullptr)
{
	if ( polynomialDegree < prev.polynomialDegree )
		throw logic_error("New polynomial degree should be greater or equal than previous."); 

	this->basicFunctions = prev.basicFunctions;
	for (int i = prev.polynomialDegree + 1; i <= polynomialDegree; i++ ) {
		this->basicFunctions.push_back(legandreCoeff(i));
	} 
	completeAcoefs(prev, func, line, polynomialDegree);
	LeastSquaresDeviation = calcLeastSquaresDeviation(func, line);
}


LeastSquaresApproximation::~LeastSquaresApproximation(void) {
	delete constantTerms;
	if ( coefficients != nullptr )
		for ( int i = 0; i <= polynomialDegree; i++ )
			delete coefficients[i];
	delete coefficients;
}

std::function<double(double)> LeastSquaresApproximation::legandreCoeff(int n) {
	switch (n) {
	case 0:
		return [](double x)->double { return 1.0; };
	case 1:
		return [](double x)->double { return x; };
	}

	auto prevFunc = legandreCoeff(n - 1);
	auto prevPrevFunc = legandreCoeff(n - 2);
	return [=](double x)->double {
		return ((2 * n - 1.0) / (n + 1.0)) * x * prevFunc(x) - (n / (n + 1.0)) * prevPrevFunc(x);
	};
}

double LeastSquaresApproximation::operator()(double x) const {
	double res = 0.0;
	for (unsigned int i = 0; i < aCoefs.size(); i++ ) {
		res += aCoefs[i]*basicFunctions[i](x);
	}
	return res;
}

void LeastSquaresApproximation::findAcoefs(FunctionType func, LineSegment line, int polynomialDegree) {
	SimpsonMethod integrator(integralPrecision);
	GaussJordanElimination systemSolver;
	coefficients = new double*[polynomialDegree + 1];
	constantTerms = new double[polynomialDegree + 1];

#ifdef USE_ROW_PARALLEL_FILLING
	parallel_for(0,polynomialDegree + 1,
	[&](int i)->void {
#else 
	for ( int i = 0; i <= polynomialDegree; i++ ) {
#endif
		coefficients[i] = new double[polynomialDegree + 1];
		constantTerms[i] = integrator([=](double x)->double { return basicFunctions[i](x)*func(x); }, line);
#ifdef USE_COLUMN_PARALLEL_FILLING
		parallel_for(0,polynomialDegree + 1,
		[&](int j)->void {
#else
		for (int j = 0; j <= polynomialDegree; j++ ) {
#endif
			coefficients[i][j] = integrator([=](double x)->double { 
												return basicFunctions[i](x)*basicFunctions[j](x); 
											}, line);
		}
#ifdef USE_COLUMN_PARALLEL_FILLING
		);
#endif
	}
#ifdef USE_ROW_PARALLEL_FILLING 
	);
#endif

	aCoefs = systemSolver.solve(LinearSystem(coefficients, constantTerms, polynomialDegree + 1));
}

void LeastSquaresApproximation::findBasicFunctions(int polynomialDegree) {
	for (int i = 0; i <= polynomialDegree; i++ ) {
		basicFunctions.push_back(legandreCoeff(i));
	}
}

double LeastSquaresApproximation::calcLeastSquaresDeviation(FunctionType func, const LineSegment& line) {
	SimpsonMethod integrator(integralPrecision);
	return integrator([=](double x)->double {
							double sub = func(x) - (*this)(x);
							return sub*sub;
						}, line);
}

#include <iostream>
#include <iomanip>

void LeastSquaresApproximation::completeAcoefs(const LeastSquaresApproximation& prev, FunctionType func, LineSegment line, int polynomialDegree) {
	SimpsonMethod integrator(integralPrecision);
	GaussJordanElimination systemSolver;
	coefficients = new double*[polynomialDegree + 1];
	for ( int i = 0; i <= polynomialDegree; i++ ) {
		coefficients[i] = new double[polynomialDegree + 1];
	}
	constantTerms = new double[polynomialDegree + 1];

	for (int i = 0; i <= prev.polynomialDegree; i++ ) {
		this->constantTerms[i] = prev.constantTerms[i];
		for (int j = 0; j <= prev.polynomialDegree; j++ ) {
			this->coefficients[i][j] = prev.coefficients[i][j];
		}
	}

#ifdef USE_ROW_PARALLEL_FILLING
	parallel_for(0,polynomialDegree + 1,
		[&](int i)->void {
#else 
	for ( int i = 0; i <= polynomialDegree; i++ ) {
#endif
		if ( i > prev.polynomialDegree ) {
			constantTerms[i] = integrator([=](double x)->double { return basicFunctions[i](x)*func(x); }, line);
		}
#ifdef USE_COLUMN_PARALLEL_FILLING
		parallel_for(0,polynomialDegree + 1,
			[&](int j)->void {
#else
		for (int j = 0; j <= polynomialDegree; j++ ) {
#endif
			if ( i > prev.polynomialDegree || j > prev.polynomialDegree ) {
				coefficients[i][j] = integrator([=](double x)->double { 
					return basicFunctions[i](x)*basicFunctions[j](x); 
				}, line);
			}
		}
#ifdef USE_COLUMN_PARALLEL_FILLING
		);
#endif
	}
#ifdef USE_ROW_PARALLEL_FILLING 
	);
#endif

	aCoefs = systemSolver.solve(LinearSystem(coefficients, constantTerms, polynomialDegree + 1));
}
