
#pragma once


#include "LinearSystems.h"


class GaussJordanElimination : public LinearSystemSolvingMethod {
public:
	GaussJordanElimination(void);
	~GaussJordanElimination(void);

	virtual SystemSolution solve(LinearSystem system);
	
private:
	void excludeCoefUsingRowWithOneCoef(LinearSystem& system, unsigned int rowWithOneCoef) const;

};

