
#include <iostream>
#include "MaclaurinSin.h"
#include <iomanip>
#include <functional>

using namespace std;

double a = -13.55;
double b = 1.33;

void buildDependencyTableSeriesLengthOfEps(double point, double beginEps, double endEps, double step) {

	if ( beginEps < endEps || step < 0 || step > 1) return;

	MaclaurinSin sin;

	cout << setw(15) << "Eps" << setw(15) << "SeriesLength"
		 << setw(15) << "AbsoluteError" << setw(15) << "RemainderTerm" << endl;

	for ( double stepEps = beginEps; stepEps > endEps; stepEps *= step) {
		sin.setEps(stepEps);
		double sinVal = sin(point);
		cout << setw(15) << stepEps << setw(15) << sin.getSeriesLength()
			 << setw(15) << abs(sinVal - std::sin(point)) << setw(15) << sin.getRemainderTerm() << endl;
	}	

}

void buildSecondTable(double a, double b, double step,function<int(void) > seriesLengthFunc) {

	if ( a > b || step < 0 ) return; 

	MaclaurinSin sin;
	int fixedSeriesLength = seriesLengthFunc();

	cout << setw(15) << "x" << setw(15) << "AbsoluteError" << setw(15) << "RemainderTerm" << endl;

	for (double x = a; x <= b; x += step) {
		double sinValue = sin(x,fixedSeriesLength);
		cout << setw(15) << x << setw(15) << abs(sinValue - std::sin(x)) << setw(15) << sin.getRemainderTerm() << endl;

	}

}

int main() {

	buildDependencyTableSeriesLengthOfEps(a, 1.0e-2, 1.0e-14, 1.0e-3);
	cout << "\n\n\n";
	buildSecondTable(a,b,(b-a)/10, []()->int{ 
		MaclaurinSin sin(1e-8);
		sin(a);
		return sin.getSeriesLength();
	} );

	return 0;
}