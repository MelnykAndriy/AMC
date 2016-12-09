

#include <iostream>
#include <iomanip>

#include "SuccessiveApproximationMethod.h"
#include "NewtonsMethod.h"

#include "functions.h"


using namespace std;


void approximationTestTabale(double beginEps, double endEps, double step,functionType fixedFunc,LineSegment seg,double q) {
	if ( beginEps < endEps || step < 0 || step > 1) return;

	SuccessiveApproximationMethod approximation;

	cout << setw(15) << "Eps" << setw(15) << "Root" << setw(25) << "Approxination Precision" << endl;
	for ( double stepEps = beginEps; stepEps > endEps; stepEps *= step) {
		approximation.setPrecision(stepEps);
		double root = approximation.defineRoot(fixedFunc,seg,q);
		cout << setw(15) << stepEps << setw(15) 
			 << root 
			 << setw(25) << approximation.getCheckedPrecision() << endl;

	}

}

void newtonsTestTable(double beginEps, double endEps, double step,LineSegment seg,double m) {
	if ( beginEps < endEps || step < 0 || step > 1) return;

	NewtonsMethod newtons;

	cout << setw(15) << "Eps" << setw(15) << "Root" << setw(25) << "Newtons Precision" << endl;
	for ( double stepEps = beginEps; stepEps > endEps; stepEps *= step) {
		newtons.setPrecision(stepEps);
		double root = newtons.defineRoot(NewtonBundle::func,NewtonBundle::firstDerivative,seg,m);
		cout << setw(15) << stepEps << setw(15) 
			<< root
			<< setw(25) << newtons.getCheckedPrecision() << endl;

	}

}



void buildComprasionTable(double beginEps, double endEps, double step) {
	if ( beginEps < endEps || step < 0 || step > 1) return;

	NewtonsMethod newtons;
	SuccessiveApproximationMethod approximation;

	cout << setw(15) << "Eps" << setw(15) << "Approximation" << setw(15) << "Newtons" << endl;
	for ( double stepEps = beginEps; stepEps > endEps; stepEps *= step) {
		newtons.setPrecision(stepEps);
		approximation.setPrecision(stepEps);
		newtons.defineRoot(NewtonBundle::func,NewtonBundle::firstDerivative,NewtonBundle::lSeg1,NewtonBundle::m1);
		approximation.defineRoot(ApproximationBundle::fixedFunc1,ApproximationBundle::lSeg1,ApproximationBundle::q1);
		cout << setw(15) << stepEps 
			 << setw(15) << approximation.getIterNumb()
			 << setw(15) << newtons.getIterNumb() << endl;

	}
}

int main() {

	approximationTestTabale(1.0e-2, 1.0e-14, 1.0e-3, ApproximationBundle::fixedFunc1, ApproximationBundle::lSeg1, ApproximationBundle::q1);
	cout << "\n\n";
	approximationTestTabale(1.0e-2, 1.0e-14, 1.0e-3, ApproximationBundle::fixedFunc2, ApproximationBundle::lSeg2, ApproximationBundle::q2);
	cout << "\n\n";

	newtonsTestTable(1.0e-2, 1.0e-14, 1.0e-3, NewtonBundle::lSeg1, NewtonBundle::m1);
	cout << "\n\n";
	newtonsTestTable(1.0e-2, 1.0e-14, 1.0e-3, NewtonBundle::lSeg2, NewtonBundle::m2);
	cout << "\n\n";

	buildComprasionTable(1.0e-2, 1.0e-14, 1.0e-3);

	return 0;
}