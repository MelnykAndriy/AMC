


#include <iostream>
#include "integration.h"
#include <iomanip>
#include <vector>
#include "SimpsonMethod.h"

using namespace std;
using namespace lab4;

void outTables() {

	LineSegment line(from,to);
	double newtowLeibnizRes = newtonLeibnizAxiom(funcAntiderivative, line);
	SimpsonMethod integrator;
	vector < double > errors;

	cout << setw(15) << "Eps" << 
		setw(15) << "Step" << 
		setw(15) << "Exact Value" << 
		setw(15) << "Result Error" << endl;
	for ( double eps = 0.1; eps > 0.000001; eps /= 10) {

		double step = calcStepSimpson(eps, line, M4);
		double integralRes = integrator(func, line, step);

		cout << setw(15) << eps << 
			setw(15) << step << 
			setw(15) << integralRes << 
			setw(15) << abs(integralRes - newtowLeibnizRes) << endl;
		errors.push_back(abs(integralRes - newtowLeibnizRes));
	}
	cout << "\n\n";

	cout << setw(20) << "Provided Error" << 
			setw(10) << "Step" << 
			setw(15) << "Result Error" << endl;

	for (auto error = errors.begin(); error != errors.end(); error++ ) {
		integrator.Eps(*error);
		double integralRes = integrator(func,line);
		cout << setw(15) << *error << 
			setw(15) << integrator.getStep() << 
			setw(15) << abs(integralRes - newtowLeibnizRes) << endl;
	}
}

int main() {
	outTables();
	return 0;
}