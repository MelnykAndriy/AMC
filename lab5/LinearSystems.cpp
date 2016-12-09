

#include "LinearSystems.h"
#include <exception>
#include <stdexcept>

using namespace std;


LinearSystem::LinearSystem(double** coefficients, double* constantTerms, int systemSize) : varCount(systemSize),coefficients(systemSize) {
	if ( systemSize < 1 ) 
		throw logic_error("System size should higher than 1.");
	if ( coefficients == nullptr || constantTerms == nullptr )
		throw logic_error("NULL was provided as formal parameter.");


	for ( int i = 0; i < systemSize; i++ ) {
		this->constantTerms.push_back(constantTerms[i]);
		for ( int j = 0; j < systemSize; j++ ) {
			this->coefficients[i].push_back(coefficients[i][j]);
		}
	}
}

const vector < double >& LinearSystem::getConstantTerms() const {
	return constantTerms;
}

const DoubleMatrix* LinearSystem::getCoefficients() const
{
	return &coefficients;
}

unsigned int LinearSystem::variableCount() const
{
	return varCount;
}

void LinearSystem::multRow(unsigned int rowNumber, double coefficient) {
	checkRowNumber(rowNumber);
	for ( auto column = coefficients[rowNumber].begin(); column != coefficients[rowNumber].end(); column++ ) {
		(*column) *= coefficient; 
	}
	constantTerms[rowNumber] *= coefficient;
}

void LinearSystem::divRow(unsigned int rowNumber, double coefficient) {
	if ( coefficient == 0 )
		throw logic_error("Division by zero is not allowed.");
	multRow(rowNumber, 1/coefficient);
}

void LinearSystem::addRow(unsigned int fromRow, unsigned int toRow, double multCoef) {
	checkRowNumber(fromRow);
	checkRowNumber(toRow);
	for( unsigned int column = 0; column < varCount; column++ ) {
		coefficients[toRow][column] += coefficients[fromRow][column]*multCoef;
	} 
	constantTerms[toRow] += constantTerms[fromRow]*multCoef;
}

void LinearSystem::subRow(unsigned int fromRow, unsigned int toRow, double multCoef) {
	checkRowNumber(fromRow);
	checkRowNumber(toRow);
	for( unsigned int column = 0; column < varCount; column++ ) {
		coefficients[toRow][column] -= coefficients[fromRow][column]*multCoef;
	}
	constantTerms[toRow] -= constantTerms[fromRow]*multCoef;
}

void LinearSystem::checkRowNumber(unsigned int rowNumber) {
	if ( rowNumber > varCount - 1 ) 
		throw out_of_range("Was provided invalid row number.");
}

