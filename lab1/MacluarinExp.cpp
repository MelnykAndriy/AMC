

#include "MacluarinExp.h"
#include <cmath>

const double MacluarinExp::e = std::exp(1);

double MacluarinExp::operator()(double x) {
	int intPart = x;
	double expOfIntPart = calcExpOfIntPart(intPart);

	return expOfIntPart*calcExpOfFractionalPart(x - intPart, eps/expOfIntPart );
}

double MacluarinExp::calcExpOfFractionalPart(double fractionalPart, double realEps) {
	double u = 1;
	double s = u;
	int k = 1;
	
	while ( abs(u) > realEps ) {
		u *= fractionalPart/k;
		k++;
		s += u;
	}
	lastSeriesLength = k;
	lastReminderTerm = abs(u * fractionalPart/((k + 1) * (1 - abs(fractionalPart)/(k + 2)))); 
	return s;
}

double MacluarinExp::calcExpOfIntPart(int intPart) {
	if ( intPart == 0 ) {
		return 1;
	} 
	return (intPart > 0)?( e*calcExpOfIntPart(intPart - 1) ):( calcExpOfIntPart(intPart + 1)/e);
}

double MacluarinExp::getRemainderTerm() const {
	return lastReminderTerm;
}

int MacluarinExp::getSeriesLength() const {
	return lastSeriesLength;
}
