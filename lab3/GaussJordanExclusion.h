
#pragma once


#include "LinearSystems.h"


class GaussJordanExclusion : public LinearSystemSolvingMethod {
public:
	GaussJordanExclusion(void);
	~GaussJordanExclusion(void);

	virtual SystemSolution solve(LinearSystem system);
	
private:
	void excludeCoefUsingRowWithOneCoef(LinearSystem& system, unsigned int rowWithOneCoef) const;

};

