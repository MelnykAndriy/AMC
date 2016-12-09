

#include <iostream>
#include <cmath>
#include <chrono>
#include <fstream>
#include <ppl.h>
#include <mutex>

#include "LeastSquaresApproximation.h"

using namespace std;
using namespace chrono;
using namespace concurrency;

double func(double x) {
	return x - 1.5*x*x*x*sin(x);
}


void dumpToFile(const LeastSquaresApproximation& s, string filename, double a, double b, double step) {
	ofstream f(filename);
	for (double x = a; x < b; x += step) {
		f << x << ";" << s(x) << endl;
	}
}



LeastSquaresApproximation* findLeastSquaresApproximationParallel(FunctionType func, LineSegment line, double eps ) {
	mutex mtx;
	int currPolynomialDegree = 1;
	LeastSquaresApproximation* foundAppr = nullptr;
	
	auto search_func = [&] () {
		int checkPolynomalDegree;
		mtx.lock();
		cout << "in search func (currPolynomialDegree : " << currPolynomialDegree << ")\n";
		if ( foundAppr == nullptr ) {
			checkPolynomalDegree = currPolynomialDegree;
			currPolynomialDegree++;
			mtx.unlock();
			LeastSquaresApproximation* checkAppr = new LeastSquaresApproximation(func, line, checkPolynomalDegree);
		
			cout << "getLeastSquaresDeviation : "<< checkAppr->getLeastSquaresDeviation()  << endl;
			if ( checkAppr->getLeastSquaresDeviation() < eps ) {
				mtx.lock();
				if ( foundAppr == nullptr ) {
					cout << "found with " << checkPolynomalDegree << endl;
					foundAppr = checkAppr;
				} 
				mtx.unlock();
			} else {
				delete checkAppr;
			}
		} else {
			mtx.unlock();
		}
	};

	while ( foundAppr == nullptr ) {
		parallel_invoke(search_func,search_func,search_func);
	}
 
	return foundAppr;
}

LeastSquaresApproximation* findLeastSquaresApproximationDynamically(FunctionType func, LineSegment line, double eps ) {
	LeastSquaresApproximation* foundAppr = new LeastSquaresApproximation(func, line, 1);

	for ( int currPolynomialDegree = 2; currPolynomialDegree < 50; currPolynomialDegree++ ) {
		if ( foundAppr->getLeastSquaresDeviation() < eps )
			break;
		cout << "in search func (currPolynomialDegree : " << currPolynomialDegree << ")\n";
		auto toDel = foundAppr;
		foundAppr = new LeastSquaresApproximation(*foundAppr, func, line, currPolynomialDegree);
		delete toDel;
		cout << "getLeastSquaresDeviation : "<< foundAppr->getLeastSquaresDeviation()  << endl;
	}
	return foundAppr;
}

int main() {
	
	const double a = 0;
	const double b = 10;
	LineSegment line(a,b); 


	auto start_t = high_resolution_clock::now();
	LeastSquaresApproximation* appr = findLeastSquaresApproximationDynamically(func, line, 1e-2);
	//LeastSquaresApproximation* appr = new LeastSquaresApproximation(func,line,16);
	auto stop_t = high_resolution_clock::now();

	cout << "time elapsed : " << duration_cast<seconds>(stop_t - start_t).count() << endl;

	dumpToFile(*appr,"graph.csv",a,b,(b-a)/500);
	delete appr;
	return 0; 
}