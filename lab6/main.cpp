


#include <iostream>
#include <cmath>
#include <fstream>

#include "Splain.h"

using namespace std;

double func(double x) {
	return x - 1.5*x*x*x*sin(x);
}

void dumpToFile(const Splain& s, string filename, double a, double b, double step) {
	ofstream f(filename);
	for (double x = a; x < b; x += step) {
		f << x << ";" << s(x) << endl;
	}
}

int main() {

	const double a = 0;
	const double b = 12;
	const int numberOfSteps = 100;
	const double step = (b - a)/numberOfSteps;

	auto input = vector<double>();
	auto output = vector<double>();

	for (int i = 0; i < numberOfSteps; i++) 	{
		double x = a + step*i;
		input.push_back(x);
		output.push_back(func(x));
	}

	Splain s(input,output);
	dumpToFile(s,"graph.csv",a,b,step/2);

	s.splines_dump();

	return 0;
}