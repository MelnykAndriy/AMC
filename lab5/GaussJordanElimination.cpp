
#include "GaussJordanElimination.h"
#include <exception>

using namespace std;


GaussJordanElimination::GaussJordanElimination(void) { }

GaussJordanElimination::~GaussJordanElimination(void) { }

SystemSolution GaussJordanElimination::solve(LinearSystem system) {
	const DoubleMatrix* coefMatrix = system.getCoefficients();
	for ( unsigned int i = 0; i < system.variableCount(); i++  ) {
		if ( (*coefMatrix)[i][i] != 0 ) {
			system.divRow(i, (*coefMatrix)[i][i]);
			excludeCoefUsingRowWithOneCoef(system, i);
		} else {
			throw std::logic_error("Zero occurred on the main diagonal.");
		}
	}

	return system.getConstantTerms();
}

void GaussJordanElimination::excludeCoefUsingRowWithOneCoef(LinearSystem& system, unsigned int mainDiagonalElemNumb) const {
	const DoubleMatrix* coefMatrix = system.getCoefficients();
	for ( unsigned int row = 0; row < system.variableCount(); row++ ) {
		if ( row != mainDiagonalElemNumb ) {
			system.subRow(mainDiagonalElemNumb, row, (*coefMatrix)[row][mainDiagonalElemNumb] );
		} 
	}
}
