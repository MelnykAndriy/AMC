


#pragma once

#include <vector>

typedef std::vector < std::vector < double > > DoubleMatrix;
typedef std::vector < double > SystemSolution;

class LinearSystem {
public:
	LinearSystem(double** coefficients, double* constantTerms, int systemSize);

	
	const DoubleMatrix* getCoefficients() const;
	const std::vector < double >& getConstantTerms() const;
	unsigned int variableCount() const;

	void multRow(unsigned int rowNumber, double coefficient);
	void divRow(unsigned int rowNumber, double coefficient);
	void addRow(unsigned int fromRow, unsigned int toRow, double multCoef);
	void subRow(unsigned int fromRow, unsigned int toRow, double multCoef);
	
private:
	void checkRowNumber(unsigned int rowNumber);

	unsigned int varCount;
	DoubleMatrix coefficients; 
	std::vector < double > constantTerms;

};



class LinearSystemSolvingMethod {
public:
	LinearSystemSolvingMethod() {} 

	virtual SystemSolution solve(LinearSystem system) = 0; 

};


class IterativeLinearSystemSolvingMethod {
public:
	IterativeLinearSystemSolvingMethod(double eps) : eps(eps) { }

	double getEps() const { return eps; }
	void setEps(double val) { eps = val; }

protected:
	
	double eps;

};