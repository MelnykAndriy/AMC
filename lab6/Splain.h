

#pragma once

#include <vector>

#include <iostream>


class Splain {
private: 
	class LineSegmentSplainRep {
	public:
		LineSegmentSplainRep()
			: a(0), b(0), c(0), d(0),xi(0) { }
		LineSegmentSplainRep(double a, double b, double c, double d, double xi) 
			: a(a), b(b), c(c), d(d),xi(xi) { }

		double operator()(double x) {
			return a + (x - xi)*(b + c*(x - xi)/2 + d*(x - xi)/6);
		}
		double a;
		double b;
		double c;
		double d;
		double xi;
	};

public:
	Splain(std::vector<double> xSequence, std::vector<double> ySequence);
	~Splain(void);


	double operator()(double x) const;

	void splines_dump() {
		for (int i = 0; i < splineReps.size(); i++)
		{
			std::cout << "a : " << splineReps[i].a << " " <<
				"b : " << splineReps[i].b << " " <<
				"c : " << splineReps[i].c << " " <<
				"d : " << splineReps[i].d <<" " <<
				"xi : " << splineReps[i].xi << std::endl;
		} 
	}


private:

	std::vector<LineSegmentSplainRep> splineReps;


	std::vector<double> sweepMethod(std::vector<double> x,std::vector<double> y);

};

