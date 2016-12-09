

#pragma once

class MacluarinExp {
public:
	MacluarinExp(double eps = 1e-3) : eps(eps) { }
	~MacluarinExp() { }

	double getEps() const { return eps; }
	void setEps(double val) { eps = val; }


	double operator() (double x);
	int getSeriesLength() const;
	double getRemainderTerm() const;

private:

	static const double e;

	double eps;
	int lastSeriesLength;
	double lastReminderTerm;
	double calcExpOfFractionalPart(double fractionalPart, double realExp);
	double calcExpOfIntPart(int intPart);

};

