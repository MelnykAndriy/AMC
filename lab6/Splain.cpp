

#include "Splain.h"
#include <exception>

using namespace std;

Splain::Splain(std::vector<double> xSequence, std::vector<double> ySequence) : splineReps(vector<LineSegmentSplainRep>()) {
	if (xSequence.size() != ySequence.size() ) throw exception("Different sizes for x and y.");

	vector<double> bSequance(xSequence.size(),0);
	vector<double> cSequance(sweepMethod(xSequence,ySequence));
	vector<double> dSequance(xSequence.size(),0);
	vector<double> aSequance(ySequence);
	vector<double> xiSequance(xSequence); 

	for (int i = xSequence.size() - 1; i > 0; i--) {
		double hi = xSequence[i] - xSequence[i - 1];
		dSequance[i] = (cSequance[i] - cSequance[i - 1]) / hi;
		bSequance[i] = hi * (2.0 * cSequance[i] + cSequance[i - 1]) / 6.0 + (ySequence[i] - ySequence[i - 1]) / hi;
	}

	for ( unsigned int i = 0; i < xiSequance.size(); i++) {
		splineReps.push_back(LineSegmentSplainRep(
			aSequance[i],
			bSequance[i],
			cSequance[i],
			dSequance[i],
			xiSequance[i]));
	}

}


Splain::~Splain(void) {
}

std::vector<double> Splain::sweepMethod(std::vector<double> x,std::vector<double> y) {
	vector<double> alpha(x.size() - 1,0);
	vector<double> beta(x.size() - 1,0);
	for (unsigned int i = 1; i < x.size() - 1; ++i) {
		double hi = x[i] - x[i - 1];
		double hi1 = x[i + 1] - x[i];
		double A = hi;
		double C = 2.0 * (hi + hi1);
		double B = hi1;
		double F = 6.0 * ((y[i + 1] - y[i]) / hi1 - (y[i] - y[i - 1]) / hi);
		double z = (A * alpha[i - 1] + C);
		alpha[i] = -B / z;
		beta[i] = (F - A * beta[i - 1]) / z;
	}
	vector<double> solveVector(x.size(),0); 
	for (int i = alpha.size() - 1; i > 0; --i) {
		solveVector[i] = alpha[i] * solveVector[i + 1] + beta[i];
	}
	return solveVector;
}

double Splain::operator()(double x) const {
	LineSegmentSplainRep s;

	if (x <= splineReps[0].xi) 
		s = splineReps[0];
	else if (x >= splineReps[splineReps.size() - 1].xi) 
		s = splineReps[splineReps.size() - 1];
	else {
		int l = 0;
		int r = splineReps.size() - 1;
		while (l + 1 < r) {
			int curr = l + (r - l)/2;
			if (x <= splineReps[curr].xi)
				r = curr;
			else 
				l = curr;
	
		}
		s = splineReps[r];
	}

	return s(x);
}
