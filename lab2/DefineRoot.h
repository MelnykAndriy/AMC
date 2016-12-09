

#pragma once
#include <functional>

typedef std::function< double (double) > functionType ;

struct LineSegment {

	LineSegment(double a, double b) : start(a), end(b) { }

	double start;
	double end;
};


class RootDefinitionMethod {
public:
	RootDefinitionMethod(double eps) : eps(eps),lastIterNumb(0),precisionCheck(0) { }


	void setPrecision(double newEps) {
		eps = newEps;
	}

	double getPrecision() {
		return eps;
	}

	int getIterNumb() {
		return lastIterNumb;
	}

	double getCheckedPrecision() {
		return precisionCheck;
	}

protected: 
	double eps;

	int lastIterNumb;
	double precisionCheck;


};