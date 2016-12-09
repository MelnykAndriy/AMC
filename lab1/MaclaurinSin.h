

#pragma once

#include <functional>

class MaclaurinSin {
public:
	MaclaurinSin(double eps=1e-3) : eps(eps) { 	}

	double getEps() {
		return eps;
	}

	void setEps(double eps) {
		this->eps = eps;
	}


	double operator()(double x, int maxSeriesLength = -1);
	double getRemainderTerm();
	int getSeriesLength();

private:
	double reduction(double x);
	double reductionSignFix(double x);
	double calcSin(double x, std::function<bool(double,int)> continueFunc); 

	double eps;
	double remainderTerm;
	int lastSeriesLength;
};
