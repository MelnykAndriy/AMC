


#pragma once

#include "LinearSystems.h"

class GaussSeidelMethod : public IterativeLinearSystemSolvingMethod {
public:
	GaussSeidelMethod(double eps);
	~GaussSeidelMethod(void);

	virtual SystemSolution solve(LinearSystem system);

private:
	bool isSuitableSystem() const;
	bool checkSatisfiedPrecision() const;
	double calcRowApproximation(unsigned int row, const LinearSystem& system, const SystemSolution& nApproximations) const;
	double matrixNormExcludeDiagonal(const LinearSystem& system);

	SystemSolution currentApproximation;
	SystemSolution prevApproximation;
	double q;

};

