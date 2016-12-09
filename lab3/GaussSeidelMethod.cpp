

#include "GaussSeidelMethod.h"
#include <stdexcept>
#include <vector>
#include <cmath>

using namespace std;

GaussSeidelMethod::GaussSeidelMethod(double eps) : IterativeLinearSystemSolvingMethod(eps) { }


GaussSeidelMethod::~GaussSeidelMethod(void) { }

SystemSolution GaussSeidelMethod::solve(LinearSystem system) {
	for ( unsigned int i = 0; i < system.variableCount(); i++ ) {
		if ( (*system.getCoefficients())[i][i] != 0 ) {
			system.divRow(i, -(*system.getCoefficients())[i][i] );	
		} else {
			throw std::logic_error("Zero occurred on the main diagonal.");
		}
	}

	q = matrixNormExcludeDiagonal(system);

	if ( !isSuitableSystem() ) 
		throw logic_error("The system is not suitable for iteration.");

	currentApproximation = SystemSolution(system.getConstantTerms());

	do {
		prevApproximation = currentApproximation;
		for ( unsigned int row = 0; row < system.variableCount(); row++) {
			currentApproximation[row] = calcRowApproximation(row, system, currentApproximation);
		}
	} while ( !checkSatisfiedPrecision() ) ;

	return currentApproximation;
}

double GaussSeidelMethod::matrixNormExcludeDiagonal(const LinearSystem& system) {
	double matrixNorm = 0;
	const DoubleMatrix* matrix = system.getCoefficients();
	
	for ( unsigned int row = 0; row < system.variableCount(); row++ ) {
		double rowSum = 0;
		for ( unsigned int column = 0; column < system.variableCount(); column++ ) {
			if ( row != column ) {
				rowSum += abs((*matrix)[row][column]);
			}
		}
		matrixNorm = ( matrixNorm < rowSum )?(rowSum):(matrixNorm);
	}

	return matrixNorm;
}

bool GaussSeidelMethod::isSuitableSystem() const {
	return q < 1;
}

bool GaussSeidelMethod::checkSatisfiedPrecision() const {
	double checkValue = ( 1 - q )*eps/q;

	for ( unsigned int approximation = 0; approximation < currentApproximation.size(); approximation++ ) {
		if ( abs(currentApproximation[approximation] - prevApproximation[approximation]) > checkValue ) {
			return false;
		}
	}
	
	return true;
}

double GaussSeidelMethod::calcRowApproximation(unsigned int row, const LinearSystem& system, const SystemSolution& nApproximations) const {
	double retApproximation = 0;
	const DoubleMatrix* coefMatrix = system.getCoefficients();

	for ( unsigned int column = 0; column < system.variableCount(); column++ ) {
		if ( column != row ) {
			retApproximation += nApproximations[column]*(*coefMatrix)[row][column];
		}
	}
	return retApproximation - system.getConstantTerms()[row];
}

