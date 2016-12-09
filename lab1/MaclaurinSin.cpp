

#include "MaclaurinSin.h"
#include <cmath>
#include <exception>

#define M_PI       3.14159265358979323846
#define M_PI_2     1.57079632679489661923
#define M_PI_4     0.785398163397448309616

double MaclaurinSin::operator()(double x,int maxSeriesLength) {
	if ( maxSeriesLength > 0 ) {
		return calcSin(reduction(x), [&](double u, int k)->bool{ return k != maxSeriesLength; }) * reductionSignFix(x);
	}
	return calcSin(reduction(x), [&](double u, int k)->bool{ return abs(u) >= eps; }) * reductionSignFix(x);
}

#pragma warning (disable : 4244)

double MaclaurinSin::reduction(double x) {
	int PI_part = abs(x/M_PI_2);
	if ( PI_part%2 ) PI_part++;
	return abs(x - ((x < 0)?(-1*PI_part):(PI_part))*M_PI_2);
}

#pragma warning (default : 4244)

double MaclaurinSin::getRemainderTerm()
{
	return abs(remainderTerm);
}

int MaclaurinSin::getSeriesLength()
{
	return lastSeriesLength;
}

double MaclaurinSin::reductionSignFix(double x)
{
	double on2p = x - ((int) (x/(2*M_PI)))*2*M_PI;
	if ( on2p < 0 ) {
		on2p+= 2*M_PI;
	}
	return (on2p < M_PI)?(1.0):(-1.0);
}

double MaclaurinSin::calcSin(double reducedX, std::function<bool(double,int)> continueFunc) {
	double sin = 0.0;
	int k = 1;
	double u;

	if ( 0 <= reducedX && reducedX <= M_PI_4 ) {
		u = reducedX ;
		while ( continueFunc(u,k) ) {
			sin += u;
			u *= - (reducedX*reducedX)/(2*k*(2*k +1));
			k++;
		}
	} else if ( M_PI_4 <= reducedX && reducedX <= M_PI_2 ) {
		double cosX = M_PI_2 - reducedX;
		u = 1 ;

		while ( continueFunc(u,k) ) {
			sin += u;
			u *= - (cosX*cosX)/(2*k*(2*k - 1));
			k++;
		}
	} else {
		throw std::exception("Bad reduction.");
	}
	lastSeriesLength = k;
	remainderTerm = u;
	return sin;
}
